#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Lista;

typedef struct arvAVL{
	Lista *linha;
	char palavra[50];
	int altura;
	struct arvAVL *esq, *dir;
}No;

void insere_lst(Lista **l, int i){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = *l;
	
	*l = novo;
}

int altura (No *raiz){
    int alt = -1;

    if(raiz != NULL)
    	alt = raiz->altura;

    return alt;
}


int fator_balanceamento(No *raiz){
	return altura(raiz->esq) - altura(raiz->dir);
}

int maior(int x, int y){
	int m;

	if(x > y)
		m = x;
	else
		m = y;

	return m;
}

// rotação simples a direita
void rotacaoDir(No **raiz){

	No *aux;

	aux = (*raiz)->esq;
	(*raiz)->esq = aux->dir;
	aux->dir = *raiz;
	(*raiz)->altura = maior(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
	aux->altura = maior(altura(aux->esq),altura(aux->dir)) + 1; 
	
	*raiz = aux;  
}


void rotacaoEsq(No **raiz){

	No *aux;

	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux->esq = *raiz;
	(*raiz)->altura = maior(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
	aux->altura = maior(altura(aux->esq),altura(aux->dir)) + 1; 
	
	*raiz = aux;
}


void rotacaoDirEsq(No **raiz){ 
 	rotacaoDir(&(*raiz)->dir);
  	rotacaoEsq(raiz);
}

void rotacaoEsqDir(No **raiz){ 
	rotacaoEsq(&(*raiz)->esq);
	rotacaoDir(raiz);
}


No *aloca_arvAVL(char *palavra, int id_linha){

    No *nova;

    nova = (No*)malloc(sizeof(No));

    strncpy(nova->palavra, palavra, strlen(palavra));    
    insere_lst(&nova->linha, id_linha);
    nova->altura = 0;
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}



void insereAVL(No **raiz, No a){

}

int main(){

	return 0;
}