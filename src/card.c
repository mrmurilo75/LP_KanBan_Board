#include "card.h"

#ifndef CARD_C_INCLUDED
#define CARD_C_INCLUDED

card* newCard(void){
	
	card* newC = (card*) malloc(sizeof(card));

	newC->text = newC->author  = newC->creation = newC->due = newC->conclusion  = newC->priority  = newC->column = -1;

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

#endif 		// CARD_C_INCLUDED
