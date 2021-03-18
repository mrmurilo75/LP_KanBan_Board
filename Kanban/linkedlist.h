#include <stdlib.h>

typedef struct lnode* List;
typedef struct lnode {
	int info;
	List next;
} List_node;

int lista_vazia(List lista);
int lista_cheia(List lista);
List cria_lista(void);
List destroi_lista(List lista);
void procura_lista(List lista, int chave, List *ant, List *atual);
void elimina_lista(List lista, int it);
void insere_lista(List lista, int it);
List pesquisa_lista(List lista, int it);
void imprime_lista(List lista);

