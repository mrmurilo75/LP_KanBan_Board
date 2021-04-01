#include "card.h"
#include "list.h"

#ifndef LIST_C_INCLUDED
#define  LIST_C_INCLUDED

void createCleanLists(){
	byAll = (CardList) malloc(sizeof(cardNode));
	byAuthor = (CardList) malloc(sizeof(cardNode));
	byCreation = (CardList) malloc(sizeof(cardNode));
	
	byAll->value = NULL;
	byAuthor->value = NULL;
	byCreation->value = NULL;
}

/*
 * possible better way of implementing:
 * 	when going thru byAll check the other in the now and see if we would be bellow, if so, save cardNode* variable so when going byAuthor and byCreation we dont have to start at the beggining 
 * 		also if cardNode* saved != NULL se if its further or closer to where our position shoulb be to see if it is advantageous to overwrite
 */

int putInListing(card* next){
	cardNode* input = (cardNode*) malloc(sizeof(cardNode));
	input->value = next;

	int err=0;
	if( (err = putByAll(input, byAll, NULL)) )
		return err;
	if( (err = putByAuthor(input, byAuthor, NULL)) )
		return err;
	if( (err = putByCreation(input, byCreation, NULL)) )
		return err;

	return err;
}

int putByAll(cardNode* input, cardNode* now, cardNode* prev){
	if( now->value == NULL)		// list is empty or we've reached the end
		return putIn(BYALL, input, prev, now);

	if(input->value->column < now->value->column){		// when ordering by all follow TODO -> DOING -> DONE
		return putIn(BYALL, input, prev, now);
	}

	if(input->value->column == TODO){
		if(input->value->priority > now->value->priority || (input->value->priority == now->value->priority && input->value->creation <= now->value->creation))
			return putIn(BYALL, input, prev, now);
		return putByAll(input, now->nextByAll, now);
	}

	if(input->value->column == DOING){
		if(input->value->author <= now->value->author)
			return putIn(BYALL, input, prev, now);
		return putByAll(input, now->nextByAll, now);
	}

	// if(input->value->column == DONE){
		if(input->value->author >= now->value->author)
			return putIn(BYALL, input, prev, now);
		return putByAll(input, now->nextByAll, now);
	//}

	return -1;

}

int putByAuthor(cardNode* input, cardNode* now, cardNode* prev){
	if(input->value->column == TODO)
		return 0;			// TODO's don't have author assigned
	if(now->value == NULL)		// list is empty or we've reached the end
		return putIn(BYAUTHOR, input, prev, now);

	if(input->value->author <= now->value->author)
		return putIn(BYAUTHOR, input, prev, now);
	return putByAuthor(input, now->nextByAuthor, now);

	return -1;
}

int putByCreation(cardNode* input, cardNode* now, cardNode* prev){
	if(now->value == NULL)		// list is empty or we've reached the end
		return putIn(BYCREATION, input, prev, now);

	if(input->value->creation <= now->value->creation)
		return putIn(BYCREATION, input, prev, now);
	return putByCreation(input, now->nextByCreation, now);

	return -1;
}

int putIn(byte list, cardNode* now, cardNode* prev, cardNode* next){
	if(prev == NULL)		// now is the first node
		switch(list){
			case BYALL: 
				byAll = now;
				break;
			case BYAUTHOR:
				byAuthor = now;
				break;
			case BYCREATION: 
				byCreation = now;
				break;
			default:
				return -1;
		}
	else
		switch(list){
			case BYALL: 
				prev->nextByAll = now;
				break;
			case BYAUTHOR:
				prev->nextByAuthor = now;
				break;
			case BYCREATION: 
				prev->nextByCreation = now;
				break;
			default:
				return -1;
		}
	if(now != NULL)
		switch(list){
			case BYALL: 
				now->nextByAll = next;
				break;
			case BYAUTHOR:
				now->nextByAuthor = next;
				break;
			case BYCREATION: 
				now->nextByCreation = next;
				break;
			default:
				return -1;
		}
	else
		return -1;

	return 0;
}

cardNode* getCard(long int id){
				// get card reference from id (text position in file)

	if(id < 0) return NULL;

	for(CardList now = byCreation; now->value != NULL; now = now->nextByCreation){
		if(now->value->text == id)
			return now;
	}

	return NULL;
}

int updateInListing(long int id, card *newC){
						// update an card from id, using non-negative values from newC

	return -1;

}

#endif 		// LIST_C_INCLUDED
