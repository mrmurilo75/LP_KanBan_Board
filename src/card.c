#include "card.h"

#ifndef CARD_C_INCLUDED
#define CARD_C_INCLUDED

card* newCard(void){
	
	card* newC = (card*) malloc(sizeof(card));

	newC->id = newC->text = newC->author  = newC->creation = newC->due = newC->conclusion  = newC->priority  = newC->column = -1;

	return newC;

}

card* freadCard(FILE * stream){
	if(stream != NULL){
		card *Card = (card *) malloc(sizeof(card));
		if(fread(Card, sizeof(card), 1, stream) == 1)
			return Card;
	}

	return NULL;
}

card* updateCard(card* newC, card* oldC){

	if(newC == NULL || oldC == NULL)
		return NULL;

	if(newC->text >= 0)
		oldC->text = newC->text;
	if(newC->author >= 0)
		oldC->author = newC->author;
	if(newC->creation >= 0)
		oldC->creation = newC->creation;
	if(newC->due >= 0)
		oldC->due = newC->due;
	if(newC->conclusion >= 0)
		oldC->conclusion = newC->conclusion;
	if(newC->priority >= 0)
		oldC->priority = newC->priority;
	if(newC->column >= 0)
		oldC->column = newC->column;

	return oldC;
}

void printCard(card* cc){
				// print card
	printf("Id = \t%ld\n"
		"Text pos =\t%ld\n"
		"Author pos =\t%ld\n"
		"Creation = \t%ld\n"
		"Due = \t%ld\n"
		"Concl. = \t%ld\n"
		"Priority = \t%d\n"
		"Column = \t%d\n"
		, cc->id, cc->text, cc->author, cc->creation, cc->due, cc->conclusion, cc->priority, cc->column);
}

#endif 		// CARD_C_INCLUDED
