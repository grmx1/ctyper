#include "ui.h"

void display_text(char* text, size_t bsize, int idx, int cols, int rows){

	int i = 0;

	if(idx > 0){

		i = (idx / (cols)) * cols;
	}

	int topl = i + 200 + cols;

	int shalf = 0;

	printf("\033[32m");
	fflush(stdout);

	//can optimize this here to not send the print statement on every iteration
	for(i; i < bsize && i < topl; i++){

		if(i == idx){

			printf("\033[30;47m");
			fflush(stdout);
		}
		else if(i > idx && shalf == 0){

			printf("\033[0m");
			fflush(stdout);
		}

		putchar(text[i]);
	}
}
