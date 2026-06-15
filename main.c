#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>

struct termios og_terminal;

void disable_raw_mode(){

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_terminal);
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

int main(int argc, char* argv[]){


	if(argc < 2){

		printf("No path for text file provided\n");
		return 0;
	}

	char* filename = argv[1];

	size_t bsize;
	int word_count;

	char* text = parse_file(filename, &bsize, &word_count);

	printf("\033[2J\033[H");
	enable_raw_mode();

	struct timespec start, end;


	int i = 0;
	int c;

	do{
		c = 0;
		printf("%s\n\033[H", text + i);
		fflush(stdout);
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

}
