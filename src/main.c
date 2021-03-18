#include <stdlib.h>
#include <stdio.h>
#include "card.h"
#include "linkedlist.h"

void initialize(void);		// get .txt files from disk into memory and fill pointers

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

List_node ToDo;
List_node Doing;

int main(int argc, char* argv[]){
	initialize();
	int opt;
	while(opt=get_option()){	//opt == 0 to quit
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
			default:
				(err)? : putError(err);
		}
	}
	err = quit();
	return err;
}


void intialize(){
	return;
}

int get_option(void){
	int opt=9;
	while(opt){
		if(opt==9){
			printf("**************MENU**************\n
				1 - Inserir tarefa em 'To Do'\n
				2 - Mover cartão de 'To Do' para 'Doing'\n
				3 - Alterar pessoas responsável\n
				4 - Fechar tarefa\n
				5 - Reabrir tarefa\n
				6 - Visualizar o quadro\n
				7 - Visualizar tarefas de uma pessoa\n
				8 - Visualizar tarefas por ordem de criação\n
				0 - Sair\n
				********************************\n
				Insira a opção pretendida: ");
		}
		
		scanf("%d",&opt);
		if(!ferror(stdin) && opt>=0 && opt<=8){
			return opt;
		} else {
			printf("Tem que escolher uma opção válida!\n
				9-Para ver menu novamente");
			opt=10;
		}

	}
	return -1;
}


