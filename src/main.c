#include <string.h>
#include <stdio.h>
#include "main.h"
#include "card.c"
#include "list.c"

int main(int argc, char* argv[]){
	int err=initialize(), opt;
	while( (opt=get_option()) && !err){	//opt == 0 to quit
		switch(opt){
/*			case 0:
				err = quit();
				break;
*/			case 1:
				err = putTask(getInsertion());
				break;
/*			case 2:
				err = openTask((getCardId()));
				break;
			case 3:
				err = changeAuthor(getCardId()));
				break;
			case 4:
				err = closeTask(getCardId()));
				break;
			case 5:
				err = reopenTask(getCardId()));
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

int putTask(card *reference){
			// get new task from user and put it in memory
	putInListing(reference);
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
		long int value = getPositiveDecimal();
		if(value >= 1 && value <= 10)
			return (byte) value;
		if(value == 0){
			quit();
			return 0;
		}
		printf("\nPlease enter a valid input!\n\n");
	}

	return (byte) -1;
}

long int getPositiveDecimal() {
				// get (long int) positive decimal from stdin
				// other values or errors return negative

	int c, cur = 0;
	while( (c =getchar()) >= '0' && c <='9'){
		cur *=10;
		cur += (c - '0');
	}
	if(c != '\n'){
		while(getchar() != '\n');
		return -1;
	}
	
	return cur;
}

long int getCardId(){
			// get a card id from user
			// NULL should return back to menu

	printf("\nPlease enter the id for the task:\n"
		"(an invalid value returns to main menu)\n");
	long int maxValue = fgetSize(ftext);
	int cur = getPositiveDecimal();
	if(cur < maxValue)		// maxValue is supposed to be '\0'
		return cur;

	printf("Invalid input ! Return to menu...");
	return -1;
}

long int fgetSize(FILE *file){
				// get file size

	long int old_pos = ftell(file);
	fseek(file, 0, SEEK_END);
	long int res = ftell(file);
	fseek(file, old_pos, SEEK_SET);

	return res;
}

void putError(int err){
			// print error message to stderr

	fprintf(stderr, "There was an error");
	exit(0);
}

int quit(){
	exit(0);
}
