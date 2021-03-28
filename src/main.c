#include <string.h>
#include <stdio.h>
#include "main.h"
#include "card.c"

int main(int argc, char* argv[]){
	int err=initialize(), opt;
	while( (opt=get_option()) && !err){	//opt == 0 to quit
		switch(opt){
/*			case 0:
				err = quit();
				break;
*/			case 1:
				err = putInListing(getInsertion());
				break;
/*			case 2:
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
*/			default:
				(err)? putError(err) : 0;
		}
	}
	if(err)
		putError(err);
	return 0;
}

FILE* fcards = NULL;
FILE* ftext = NULL;
FILE* fauthor = NULL;

CardList byAll = NULL;
CardList byAuthor = NULL;
CardList byCreation = NULL;

int initialize(void){
		// get .txt files from disk into memory and fill pointers
	if(fcards == NULL) fcards = fopen("cards.bin", "r+b");
	if(ftext == NULL) ftext = fopen("text.txt", "a+");
	if(fauthor == NULL) fauthor = fopen("author.txt", "r");

	createCleanLists();

	int err=0;
	if(fcards == NULL){		// check if file was really open/exists
		fcards = fopen("cards.bin", "w+b");
		return 0;
	}
	for(card* next=freadCard(fcards); next!=NULL; next=freadCard(fcards))
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
	return putByAll(input, now->nextByAuthor, now);

	return -1;
}

int putByCreation(cardNode* input, cardNode* now, cardNode* prev){
	if(now->value == NULL)		// list is empty or we've reached the end
		return putIn(BYCREATION, input, prev, now);

	if(input->value->creation <= now->value->creation)
		return putIn(BYCREATION, input, prev, now);
	return putByAll(input, now->nextByCreation, now);

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

int get_option(void){
	int opt=9;
	while(opt){
		printf(	"**************MENU**************\n"
			"1 - Inserir tarefa em 'To Do'\n"
			"2 - Mover cartão de 'To Do' para 'Doing'\n"
			"3 - Alterar pessoas responsável\n"
			"4 - Fechar tarefa\n"
			"5 - Reabrir tarefa\n"
			"6 - Visualizar o quadro\n"
			"7 - Visualizar tarefas de uma pessoa\n"
			"8 - Visualizar tarefas por ordem de criação\n"
			"0 - Sair\n"
			"********************************\n"
			"Insira a opção pretendida: ");

		opt = getchar();
		int c;
		if( (c=getchar()) == '\n' && (opt-='0') >= 0 && opt <= 8 )
			return opt;
		else{
			if(c != '\n') 
				while(getchar() != '\n');
			printf("\nTem que escolher uma opção válida!\n\n");
			opt=10;
			continue;
		}

	}
	return -1;
}

card* getInsertion(){
			// get text for text (description), priority and creation date
			// get creation date using time.h

	card *newCard = (card*) malloc(sizeof(card));
	
		// fill information that matters
	newCard->column = TODO;
	if( ( newCard->text = writeText(getText()) ) < 0) return NULL;
	if( ( newCard->priority = getPriority() ) < 0) return NULL;
	if( ( time( &(newCard->creation)) ) < 0) return NULL;

		// fill other spaces with null or equivalent
	newCard->due = newCard->conclusion = newCard->author = -1;

	return newCard;
}

long int writeText(char* text){		// ! non-portable
			// write text to file and return (long) position pointer

	if(ftext == NULL)
		if( (ftext = fopen("text.txt", "w+")) == NULL) return -1L;

	fseek(ftext, 0, SEEK_END);
	long int pos = ftell(ftext);

	if( fputs(text, ftext) < 0) return -1;		// writes to file whats in text argument (without null character)
	if( fputc('\0', ftext) < 0) return -1;		// writes terminating null character

	return pos;
}

char* getText(){	// ! non-portable
			// get text from input
	printf("\nPlease enter the description for the task:\n\
		( ! End text with Ctrl + G then Enter)\n\n");
	const int size = 128; 		// size as 128 bytes block
	int cur_size;
	char* text = (char*) malloc( (cur_size = size*sizeof(char)) );
	if(text == NULL) return NULL;

	int i=0, c;
	while( (c=getchar()) != 0x07){
		if(i > cur_size-1)
			text = (char*) realloc(text, cur_size + size);
		text[i++] = c;
	}
	if( getchar() != '\n') putError(0);
	text[i++] = '\0';
	text = (char*) realloc(text, i); 	// trim

	return text;
}

byte getPriority(){
			// get priority from input

	for(;;){
		printf("\nPlease enter the priority for the task:\n"
			"(from 1 to 10 | 0 to return to main menu)\n\t");
		int value = getchar(), c=getchar();
		if( (value >='0' && value <= '9') ){
			if(c =='\n'){
				if(value == '0')
					quit();
				return (byte) (value-'0');
			}
			if(c =='0' && getchar()=='\n')
				return (byte) 10;
		}
		if(c != '\n') 
			while(getchar() != '\n');
		printf("\nTem que colocar um valor válido!\n\n");
	}

	return (byte) -1;
}





void putError(int err){
			// print error message to stderr

	fprintf(stderr, "There was an error");
	exit(0);
}

int quit(){
	exit(0);
}
