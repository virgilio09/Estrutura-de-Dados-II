#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Lista;

typedef struct arv{
	Lista *linha;
	char palavra[50];
	struct arv *esq, *dir;
}No;

Lista *insere_lst(Lista *l, int i){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = l;
	return novo;
}


No *aloca_arv(char *palavra){

    No *nova;

    nova = (No*)malloc(sizeof(No));

    strncpy(nova->palavra, palavra, strlen(palavra));    
    nova->linha = NULL;
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;

}


void insere_arv(No **raiz, No *a){

    if(*raiz == NULL)
        *raiz = a;

    else{
    	if(strcmp(a->palavra, (*raiz)->palavra) < 0)
            insere_arv(&(*raiz)->esq, a);

        else if(strcmp(a->palavra, (*raiz)->palavra) > 0)
            insere_arv(&(*raiz)->dir, a);
    } 
       
}



void imprime_arv(No *raiz){
	if(raiz != NULL){
		imprime_arv(raiz->esq);
		printf("%s\n",raiz->palavra);
		imprime_arv(raiz->dir);
	}
}

void imprime_lst(Lista* l){
	
	Lista* p;
	p = l;
	if(p != NULL){
		printf("info = %d\n", p->info);
		imprime_lst(p->prox);

	}
}

int main(){
	No *raiz, *a;
	raiz = NULL;
	
	a = aloca_arv("joaoo");
	insere_arv(&raiz, a);

	a = aloca_arv("Ana");
	insere_arv(&raiz, a);

	imprime_arv(raiz);




	return 0;
}
