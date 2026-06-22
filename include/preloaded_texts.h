#ifndef PRELOADED_TEXTS_H
#define PRELOADED_TEXTS_H

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define TEXTS_SIZE 10

extern char* texts[TEXTS_SIZE];

char* get_random_text(size_t* bsize);

#endif
