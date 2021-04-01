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
				break;*/
			case 7:
				err = viewByAuthor();
				break;
			/*case 8:
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
			// get card reference and put write it to memory and files

	int err = putInListing(reference);
	if(!err) 
		err = writeCard(reference);

	if(!err) 
		printf("Card added successfully.\n");
	else
		printf("We're sorry, but there was an error !\n");
	printf("Returning to menu...\n\n");

	return err;

}

int writeCard(card* reference){		// ! non-portable
				// write card to file and return error or 0

	if(fcards == NULL)
		if( (fcards = fopen("cards.bin", "wb+")) == NULL) return -1;

	fseek(fcards, 0, SEEK_END);

	if( fwrite(reference, sizeof(card), 1, fcards) != 1) return -1;

	return 0;
}


card* getInsertion(){
			// get text for text (description), priority and creation date
			// get creation date using time.h

	card *newC = newCard();
	
		// fill information that matters
	newC->column = TODO;
	if( ( newC->text = writeText(getText()) ) < 0) return NULL;
	if( ( newC->priority = getPriority() ) < 0) return NULL;
	if( ( time( &(newC->creation)) ) < 0) return NULL;

	return newC;
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
	printf("\nPlease enter the description for the task:\n"
		"( ! End text with Ctrl + G then Enter)\n\n");
	char *text = readInput(0x07);
	if( getchar() != '\n') putError(0);	// read \n after ^G
	return text;
}

char* readInput(const char control){
							// reads text from input

	const int size = 64; 		// size as 128 bytes block
	int cur_size;
	char* text = (char*) malloc( (cur_size = size)*sizeof(char) );
	if(text == NULL) return NULL;

	int i=0, c;
	while( (c=getchar()) != control){
		if(i >= cur_size)
			text = (char*) realloc(text, (cur_size*=2) *sizeof(char));	// doubles buffer size whenever nedded
		text[i++] = c;
	}
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

int openTask(long int id){
				// move task from TODO to DOING
				// get and set author, get and set due date

	card* newC = newCard();

	newC->column = DOING;
	newC->author = writeAuthor(getAuthor());
	newC->due = getDueDate();

	int err = updateInListing(id, newC);

	return err;
}

char* getAuthor(){
			// reads author from stdin

	printf("\nPlease enter the author for the task:\n");
	return readInput('\n');
}

long int writeAuthor(char* newAuthor){
					// write author to file and return (long int) position

	return -1;
}

long int getDueDate(){
			// get due date from stdin

	return -1;
}

int viewByAuthor() {
	cardNode* now = byAuthor;


	while (now->value != NULL) {
		printf("Autor do card: ");
		fseek(fauthor,now->value->author, SEEK_SET);
		char c;
		while((c=fgetc(fauthor)) != '\0') {
			putchar(c);	
		}
		printf("\n");
		printf("Descrição da tarefa: ");
		fseek(ftext,now->value->text, SEEK_SET);
		c = '.';
		while((c=fgetc(ftext)) != '\0') {
			putchar(c);	
		}
		printf ("Prioridade da Tarefa = %c\n", now->value->priority);
		printf ("Tarefa da Coluna: %c\n", now->value->column);
		printf ("Data de Criação: %s", ctime (&now->value->creation));
		printf ("Prazo Maximo de Conclusao: %s", ctime (&now->value->due));
		now = now->nextByAuthor;
	}
	
	return 0;
}

void putError(int err){
			// print error message to stderr

	fprintf(stderr, "There was an error");
	exit(0);
}

int quit(){
	exit(0);
}

