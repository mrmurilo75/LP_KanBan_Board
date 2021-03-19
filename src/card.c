#include "card.h"

int fnewCard(FILE * stream){
	if(stream == NULL)
		return -1;

	card *newCard = (card *) malloc(sizeof(card));
	return (fread(newCard, sizeof(card), 1, stream) - 1);
}
