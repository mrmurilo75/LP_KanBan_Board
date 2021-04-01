#include "card.h"

#define BYALL 1
#define BYAUTHOR 2
#define BYCREATION 3

#ifndef LIST_HEADER_INLCUDED
#define LIST_HEADER_INLCUDED

CardList byAll = NULL;
CardList byAuthor = NULL;
CardList byCreation = NULL;

void createCleanLists(void);		//create clean list for byAll, byAuthor, byCreator linked lists
//DONE

int putInListing(card* next);		// put card in all list in corret sorted position
//DONE

int putByAll(cardNode* input, cardNode* now, cardNode* prev);
//DONE					// puts cards in byAll list

int putByAuthor(cardNode* input, cardNode* now, cardNode* prev);
//DONE					// puts cards in byAuthor list

int putByCreation(cardNode* input, cardNode* now, cardNode* prev);
//DONE					// puts cards in byCreation list

int putIn(byte list, cardNode* now, cardNode* prev, cardNode* next);
//DONE					// effectively puts the given card 'now' between 'prev' and 'next'

cardNode* getCard(long int id);		// get card reference from id (text position in file)
//DONE

int updateInListing(long int id, card *newC);	// update an card from id, using non-negative values from newC

#endif  // LIST_HEADER_INCLUDED
