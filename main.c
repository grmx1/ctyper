#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <termios.h>

struct termios og_terminal;
int resize_flag;

void disable_raw_mode(){

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_terminal);
}

void get_winsize(int* cols, int* rows){

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	
	*cols = w.ws_col;
	*rows = w.ws_row;

	resize_flag = 0;
}

void winch_handle(int sig){

	if(sig == SIGWINCH){

		resize_flag = 1;
	}
}


void enable_raw_mode(){

	tcgetattr(STDIN_FILENO, &og_terminal);
	atexit(disable_raw_mode);

	struct termios terminal = og_terminal;

	terminal.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
}

char* parse_file(char* filename, size_t* bsize, int* wcount){

	int c;
	int bufsize = 100;
	int word_count = 0;
	int in_word = 0;

	char* buffer = malloc(bufsize);

	FILE* file;

	file = fopen(filename, "r");

	if(file == NULL){

		perror("COULDNT OPEN FILE!\n");
		return NULL;
	}

	int counter = 0;
	while((c = fgetc(file)) != EOF){

		if(in_word == 0 && isalpha(c)){

			in_word = 1;
			word_count++;
		}
		else if(in_word > 0 && (c == ' ' || c == '\n')){

			in_word = 0;
		}

		if(counter + 10 >= bufsize){

			bufsize *= 2;
			char* temp_buffer = realloc(buffer, bufsize);

			if(temp_buffer != NULL){

				buffer = temp_buffer;
			}
			else{
				perror("REALLOC FAILED\n");
				return NULL;
			}
		}

		buffer[counter] = c;

		counter++;
	}

	buffer[counter + 1] = '\0';
	fclose(file);

	*bsize = counter;
	*wcount = word_count;

	return buffer;

}

void display_text(char* text, size_t bsize, int idx, int cols, int rows){

	//can optimize this here to not send the print statement on every iteration
	for(int i = 0; i < bsize; i++){

		if(i < idx){

			printf("\033[32m");
			fflush(stdout);
		}
		else if(i == idx){

			printf("\033[30;47m");
			fflush(stdout);
		}

		putchar(text[i]);
		printf("\033[0m");
		fflush(stdout);
	}
}

int main(int argc, char* argv[]){


	if(argc < 2){

		printf("No path for text file provided\n");
		return 0;
	}

	char* filename = argv[1];

	size_t bsize;
	int word_count;

	char* text = parse_file(filename, &bsize, &word_count);

	printf("\033[2J\033[H\033[?25l");

	int cols;
	int rows;

	get_winsize(&cols, &rows);
	enable_raw_mode();

	struct timespec start, end;

	int i = 0;
	int c;

	do{

		signal(SIGWINCH, winch_handle);

		if(resize_flag == 1){

			get_winsize(&cols, &rows);
		}

		display_text(text, bsize, i, cols, rows);
		//printf("%s\n\033[H", text + i);

		c = 0;

		read(STDIN_FILENO, &c, 1);

		if(i == 0){


			clock_gettime(CLOCK_MONOTONIC, &start);
		}

		if(c == text[i]){

			i++;
		}

		printf("\033[2J\033[H");

	}while(i + 1 < bsize);

	clock_gettime(CLOCK_MONOTONIC, &end);

	double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	double wpm = (bsize / 5) / (time_taken / 60.00);


	printf("Time: %fs\n", time_taken);
	printf("WPM = %f\n", wpm);

	printf("\033[?25h");


}
