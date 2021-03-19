#include <stdlib.h>
#include <stdio.h>
#include "card.c"
#include "linkedlist.c"
#include "SortedList.c"

#define TODO 1
#define DOING 2
#define DONE 3

#define BYALL 1
#define BYAUTHOR 2
#define BYCREATOR 3

int initialize(void);		// get .txt files from disk into memory and fill pointers

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

int putError(int err);		// print error message to stderr

int quit(void);		// save state and quit


int main(int argc, char* argv[]){
	int err=initialize(), opt;
	while( (opt=get_option()) && !err){	//opt == 0 to quit
		switch(opt){
			case 0:
				err = quit();
				break;
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
				(err)? putError(err) : 0;
		}
	}
	if(err)
		return putError(err);
	return 0;
}

int numberOfCards=0;

CardList byAll;
CardList byAuthor;
CardList byCreation;

void createCleanLists(void);
int putInListing(card* next);

int initialize(void){
		// get .txt files from disk into memory and fill pointers
	int err=0;
	FILE *fcards = fopen("cards.bin", "r+b");
	if(fcards == NULL){
		fcards = fopen("cards.bin", "w+b");
		return 0;
	}
	createCleanLists();
	for(card* next=fnewCard(fcards); fnewCards!=NULL; next=fnewCard(fcards))
		if( (err = putInListing(next)) ) {
			putError(err);
			return err;
		}

	return	0;
}

void createCleanLists(){
	byAll = (CardList) malloc(sizeof(cardNode));
	byAuthor = (CardList) malloc(sizeof(cardNode));
	byCreation = (CardList) malloc(sizeof(cardNode));
	
	byAll->value = NULL;
	byAuthor->value = NULL;
	byCreation->value = NULL;
}

int putByAll(cardNode* input, cardNode* now, cardNode* prev);
int putByAuthor(cardNode* input, cardNode* now, cardNode* prev);
int putByCreator(cardNode* input, cardNode* now, cardNode* prev);

int putInListing(card* next){
	cardNode* input = (cardNode*) malloc(sizeof(cardNode));
	input->value = next;

	int err=0;
	if( (err = putByAll(input, byAll, NULL)) )
		return err;
	if( (err = putByAuthor(input, byAuthor, NULL)) )
		return err;
	if( (err = putByCreator(input, byCreator, NULL)) )
		return err;

	return err;
}


int putIn(byte list, cardNode* now, cardNode* prev, cardNode* next);

cardNode* byAllLastToDo = NULL;

int putByAll(cardNode* input, cardNode* now, cardNode* prev){
	if(now->value == NULL)		// list is empty or we've reached the end
		return putIn(BYALL, input, prev, now);

	if(input->value->column < now->value->column){		// when ordering by all follow TODO -> DOING -> DONE
		if(now->value->column == DOING)
			byAllLastToDo = input;
		return putIn(BYALL, input, prev, now);
	}

	if(input->value->column == TODO){
		if(input->value->priority > now->value->priority || (input->value->priority == now->value->priority && input->value->creation <= now->value->creation))
			return putIn(BYALL, input, prev, now);
		return putByAll(input, now->nextByAll, now);
	}

	if(input->value->column == DOING){
/*
		if(now->nextByAuthor == NULL && byAllLastToDo != NULL)
			return putByAll(input, byAuthor, byAllLastToDo);	// the byAuthor list first element coincides with the first DOING element in byAll
* doesnt work bc we are putting everything in all lists in parallel (would work if we filled byAll first)
*/
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
	
	return -1;
}

int putByCreator(cardNode* input, cardNode* now, cardNode* prev){
	// IMPLEMENT 
	// similar to putByAll
	return -1;
}

int putIn(byte list, cardNode* now, cardNode* prev, cardNode* next){
	if(prev == NULL)		// now is the first node
		switch(list){
			case BYALL: 
				byAll = input;
				break;
			case BYAUTHOR:
				byAuthor = input;
				break;
			case BYCREATOR: 
				byCreator = input;
				break;
			default:
				return -1;
		}
	else
		switch(list){
			case BYALL: 
				prev->nextByAll = input;
				break;
			case BYAUTHOR:
				prev->nextByAuthor = input;
				break;
			case BYCREATOR: 
				prev->nextByCreator = input;
				break;
			default:
				return -1;
		}
	if(now != NULL)
		switch(list){
			case BYALL: 
				input->nextByAll = now;
				break;
			case BYAUTHOR:
				input->nextByAuthor = now;
				break;
			case BYCREATOR: 
				input->nextByCreator = now;
				break;
			default:
				return -1;
		}

	return 0;
}

int get_option(void){
	int opt=9;
	while(opt){
		if(opt==9){
			printf("**************MENU**************\
				1 - Inserir tarefa em 'To Do'\
				2 - Mover cartão de 'To Do' para 'Doing'\
				3 - Alterar pessoas responsável\
				4 - Fechar tarefa\
				5 - Reabrir tarefa\
				6 - Visualizar o quadro\
				7 - Visualizar tarefas de uma pessoa\
				8 - Visualizar tarefas por ordem de criação\
				0 - Sair\
				********************************\
				Insira a opção pretendida: ");
		}
		
		scanf("%d",&opt);
		if(!ferror(stdin) && opt>=0 && opt<=8){
			return opt;
		} else {
			printf("Tem que escolher uma opção válida!\
				9-Para ver menu novamente");
			opt=10;
		}

	}
	return -1;
}
