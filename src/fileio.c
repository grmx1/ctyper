#include "fileio.h"

char* parse_file(char* filename, size_t* bsize){

	int c;
	int bufsize = 100;
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
