#include "terminal.h"


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
