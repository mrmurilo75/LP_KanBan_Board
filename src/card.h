#include <stdio.h>

#ifndef BYTE_DEFINED
typedef char byte;
#endif	// BYTE_DEFINED

#ifndef CARD_H_INCLUDED

#define TODO 1
#define DOING 2
#define DONE 3

#define CARD_H_INCLUDED

typedef struct {
	long int text, author; //for use with ftell/fseek and for easier sorting
	unsigned long int creation, due, conclusion;
	byte priority;
	byte column;

	//fpos_t text, author; //for use with fgetpos/fsetpos if necessary 
} card;

typedef struct card_node* CardList;

typedef struct card_node{
        card* value;
        CardList nextByAll;
        CardList nextByAuthor;
        CardList nextByCreation;
} cardNode;
        


card* fnewCard(FILE* stream);	// malloc space for a card and fill from stream

#endif	//CARD_H_INCLUDED
