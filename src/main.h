#include <stdlib.h>
#include <stdio.h>
#include "card.h"

#define TODO 1
#define DOING 2
#define DONE 3

#define BYALL 1
#define BYAUTHOR 2
#define BYCREATION 3

#ifndef MAIN_HEADER_INLCUDED
#define MAIN_HEADER_INCLUDED

int initialize(void);			// get .txt files from disk into memory and fill pointers
//DONE

int get_option(void); 			// get input option from user (1. insert,  2. open task...)
//DONE

int putTask(card *newTask); 		// get new task and make card in TODO column

card* getInsertion();			// get text for description, priority and due date
					// get creation date using time.h

card* getCard(void);			// get card reference from id (text position in file)

int openTask(card *reference);		// move task from TODO to DOING
					// get and set author, get and set due date

int closeTask(card *reference);		// move task from DOING to DONE
					// set conclusion date with time.h

int reopenTask(card *reference);	// move task from DONE to TODO
					// get and reset priority

int changeAuthor(card *reference);	// change Author

int fullView(void);			// view from the organized linked list (
					//					TODO by priority then creation,
					//					DOING by author,
					//					DONE by conclusion )

int viewByCreation(void);		// view all by creation date

int viewByAuthor(long int author);	// view all by Author (only DOING and DONE)

long int getAuthor(void);		// read Author from input

int putError(int err);			// print error message to stderr

int quit(void);				// save state and quit

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

#endif // MAIN_HEADER_INCLUDED
