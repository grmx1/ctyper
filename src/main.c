#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "terminal.h"
#include "preloaded_texts.h"
#include "fileio.h"
#include "ui.h"

int main(int argc, char* argv[]){

	char* text = NULL;
	size_t bsize;

	if(argc < 2){

		text = get_random_text(&bsize);
	}
	else{

		char* filename = argv[1];

		text = parse_file(filename, &bsize);
	}
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
