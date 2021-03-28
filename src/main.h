#include <stdlib.h>
#include <stdio.h>
#include "card.h"

#define TODO 1
#define DOING 2
#define DONE 3

#ifndef MAIN_HEADER_INLCUDED
#define MAIN_HEADER_INCLUDED

int initialize(void);			// get .txt files from disk into memory and fill pointers
//DONE

int get_option(void); 			// get input option from user (1. insert,  2. open task...)
//DONE

card* getInsertion();			// get text for description, priority and creation date
//					// get creation date using time.h
	long writeText(char* text);
	//DONE				// write text to file and return (long) position pointer

	char* getText();
	//DONE				// get text from input

	byte getPriority();
	//DONE				// get priority from input
//
//DONE

long int getCardId(void);			// get a card id from user
//DONE					// NULL should return back to menu

long int getPositiveDecimal(void);	// get (long int) positive decimal from stdin
//DONE					// other values or errors return negative

long int fgetSize(FILE *file);		// get file size
//DONE

int putTask(card *reference);		// get card reference and put it in memory
//DONE

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

void putError(int err);			// print error message to stderr
// NOT DONE (temporarily defined)

int quit(void);				// save state and quit
// NOT DONE (temporarily defined)

#endif // MAIN_HEADER_INCLUDED
