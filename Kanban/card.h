#include <stdio.h>

#define TODO 1
#define DOING 2
#define DONE 3

typedef char byte;

typedef struct {
	long int text, author; //for use with ftell/fseek and for easier sorting
	unsigned long int creation, due, conclusion;
	short int priority;
	byte column;

	//fpos_t text, author; //for use with fgetpos/fsetpos if necessary
} card;
