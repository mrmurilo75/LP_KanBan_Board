#include <stdio.h>

#define TODO 1
#define DOING 2
#define DONE 3

typedef char byte;

typedef struct { 
	unsigned long int id, creation, conclusion, due;
	short int priority;
	byte column;
	fpos_t author, text; // use fgetpos/fsetpos for security reasons
} card;
