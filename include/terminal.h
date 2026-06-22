#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

extern struct termios og_terminal;
extern int resize_flag;

void disable_raw_mode();
void get_winsize(int* cols, int* rows);
void winch_handle(int sig);
void enable_raw_mode();

#endif
