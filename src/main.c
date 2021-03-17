#include <stdlib.h>
#include <stdio.h>
#include "card.h"

void initialize(void);

int get_option(void);

int putTask(card *newTask);
card* getInsertion();

card* getCard(void);

int openTask(card *reference);
int closeTask(card *reference);
int reopenTask(card *reference);

int changeAuthor(card *reference);

int fullView(void);
int viewByCreation(void);
int viewByAuthor(long int author);

long int getAuthor(void);

void putError(int err);

void quit(void);

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

