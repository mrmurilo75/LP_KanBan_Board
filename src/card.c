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
	card* updated = newCard();

	if(newC->text >= 0)
		updated->text = newC->text;
	if(newC->author >= 0)
		updated->author = newC->author;
	if(newC->creation >= 0)
		updated->creation = newC->creation;
	if(newC->due >= 0)
		updated->due = newC->due;
	if(newC->conclusion >= 0)
		updated->conclusion = newC->conclusion;
	if(newC->priority >= 0)
		updated->priority = newC->priority;
	if(newC->column >= 0)
		updated->column = newC->column;

	return updated;
}

#endif 		// CARD_C_INCLUDED
