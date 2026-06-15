#include <stdio.h>
#include <stdlib.h>
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

char* parse_file(char* filename, size_t* bsize){

	int c;
	int bufsize = 100;

	char* buffer = malloc(bufsize);

	FILE* file;

	file = fopen(filename, "r");

	if(file == NULL){

		perror("COULDNT OPEN FILE!\n");
		return NULL;
	}

	int counter = 0;
	while((c = fgetc(file)) != EOF){

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

	return buffer;

}

int main(int argc, char* argv[]){


	if(argc < 2){

		printf("No path for text file provided\n");
		return 0;
	}

	char* filename = argv[1];

	size_t tsize;
	char* text = parse_file(filename, &tsize);

	printf("\033[2J\033[H");
	enable_raw_mode();

	int i = 0;
	int c;

	do{
		c = 0;
		printf("%s\n\033[H", text + i);
		fflush(stdout);
		read(STDIN_FILENO, &c, 1);

		if(c == text[i]){

			i++;
		}

		printf("\033[2J\033[H");

	}while(i + 1 < tsize);

	printf("DONE\n");


}
