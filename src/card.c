#include "card.h"

card* freadCard(FILE * stream){
	if(stream != NULL){
		card *Card = (card *) malloc(sizeof(card));
		if(fread(Card, sizeof(card), 1, stream) == 1)
			return Card;
	}

	return NULL;
}
