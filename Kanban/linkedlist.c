#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

int lista_vazia(List lista) {
	return (lista->next == NULL ? 1:0);
}

int lista_cheia(List lista) {
	return 0;
}

List cria_lista(void) {
	List aux;
	aux = (List) malloc(sizeof(List_node));
	if (aux != NULL) {
		aux->info=0;
		aux->next=NULL;
	}
	return aux;
}

List destroi_lista(List lista){
	List temp_ptr;
	while (lista_vazia(lista)==0) {
		temp_ptr = lista;
		lista = lista->next;
		free (temp_ptr);
	}
	free(lista);
	return NULL;
}

void procura_lista(List lista, int chave, List *ant, List *atual) {
	*ant = lista;
	*atual = lista -> next;
	while ((*atual) != NULL && (*atual)->info<chave) {
		*ant = *atual;
		*atual = (*atual)->next;
	}
	if((*atual) != NULL && (*atual)->info != chave)
		*atual = NULL;
}

void elimina_lista(List lista, int it){
	List ant1;
	List atual1;
	procura_lista(lista,it,&ant1,&atual1);
	if (atual1 != NULL){
		ant1->next = atual1->next;
		free(atual1);
	}
}

void insere_lista(List lista, int it) {
	List no;
	List ant, inutil;
	no = (List) malloc (sizeof(List_node));
	if (no != NULL) {
		no ->info = it;
		procura_lista(lista,it,&ant,&inutil);
		no->next = ant->next;
		ant->next = no;
	}
}

List pesquisa_lista(List lista, int it) {
	List ant;
	List atual;
	procura_lista(lista,it,&ant,&atual);
	return (atual);
}

void imprime_lista(List lista) {
	List I = lista->next;
	printf("{");
	while (I) {
		printf("%d, ", I->info);
		I = I->next;
	}
	printf("}\n");
}

