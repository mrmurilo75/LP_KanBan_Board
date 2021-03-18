#include <stdlib.h>

typedef struct lnode* List;
typedef struct lnode{
	int info;
	List next;
}List_node;


int empty_list(List list){
	return(list->next == NULL ? 1:0);
}

int full_list(List list){
	return 0;
}

List new_list(void){
	List aux;
	aux= (List) malloc(sizeof(List_node));
	if(aux!=NULL){
		aux->info=0;
		aux->next=NULL;
	}
	return aux;
}

List kill_list(List list){
	List temp_ptr;
	while(empty_list(list)==0){
		temp_ptr=list;
		list=list->next;
		free(temp_ptr);
	}
	free(list);
	return NULL;
}

void found_list(List list, int key, List *ant, List *cur){
	*ant=list;
	*cur=list->next;
	while((*cur)!=NULL && (*cur)->info<key){
		*ant=*cur;
		*cur=(*cur)->next;
	}
	if((*cur)!=NULL && (*cur)->info!=key)
		*cur=NULL;
}

void delete_list(List list, int it){
	List ant1,cur1;
	found_list(list,it,&ant1,&cur1);
	if(cur1!=NULL){
		ant1->next=cur1->next;
		free(cur1);
	}
}

void insert_list(List list, int it){
	List no, ant, useless;
	no=(List)malloc(sizeof(List_node));
	if(no!=NULL){
		no->info=it;
		found_list(list,it,&ant,&useless);
		no->next=ant->next;
		ant->next=no;
	}
}

List search_list(List list, int it){
	List ant,cur;
	found_list(list,it,&ant,&cur);
	return(cur);
}

void print_list(List list){
	List I=list->next;
	printf("{");
	while(I){
		printf("%d, ",I->info);
		I=I->next;
	}
	printf("}\n");
}







