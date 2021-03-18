#include <stdlib.h>
#include <stdio.h>
#include "card.h"

void initialize(void);

int get_option(void); 		// get input option from user (1. insert,  2. open task...)

int putTask(card *newTask); 	// get new task and make card in TODO column

card* getInsertion();		// get text for description, priority and due date
				// get creation date using time.h

card* getCard(void);		// get card reference from id (text position in file)

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

void putError(int err);		// print error message to stderr

void quit(void);		// save state and quit

int main(int argc, char* argv[]){
	initialize();
	int opt;
	while(opt=get_option()){
		switch(opt){
				int err=0;
			case 1:
				err = putTask(getInsertion());
				break;
			case 2:
				err = openTask(getCard());
				break;
			case 3:
				err = changeAuthor(getCard());
				break;
			case 4:
				err = closeTask(getCard());
				break;
			case 5:
				err = reopenTask(getCard());
				break;
			case 6:
				err = fullView();
				break;
			case 7:
				err = viewByAuthor(getAuthor());
				break;
			case 8:
				err = viewByCreation();
				break;
			case 9:
				quit();
				break;
			default:
				(err)? : putError(err);
		}

}


void intialize(){
	//fill array with card structures
	return;
}

int get_option(void){
	//podemos implementar primeiramente um option por opcoes (1, 2, 3...)
	//e depois se tivermos tempo por comandos ("insert", "doing", "done"...)
	
	//implement input protection
	return 0;
}

