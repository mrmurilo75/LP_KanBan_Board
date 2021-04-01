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

	char* readInput(const char control);
	//DONE				// read text from input until a control character

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

int writeCard(card* reference);		// write card to file and return error or 0
//DONE

int putTask(card *reference);		// get card reference and put it in memory
//DONE

int openTask(long int id);		// move task from TODO to DOING
//					// get and set author, get and set due date
//
	char* getAuthor(void);
					// reads author from stdin

	long int writeAuthor(char* newAuthor);
					// write author to file and return (long int) position

	long int getDueDate();
					// get due date from stdin
//

int closeTask(long int id);		// move task from DOING to DONE
					// set conclusion date with time.h

int reopenTask(long int id);	// move task from DONE to TODO
					// get and reset priority

int changeAuthor(long int id);	// change Author

int fullView(void);			// view from the organized linked list (
					//					TODO by priority then creation,
					//					DOING by author,
					//					DONE by conclusion )

int viewByCreation(void);		// view all by creation date

int viewByAuthor();	// view all by Author (only DOING and DONE)

void putError(int err);			// print error message to stderr
// NOT DONE (temporarily defined)

int quit(void);				// save state and quit
// NOT DONE (temporarily defined)

#endif // MAIN_HEADER_INCLUDED
