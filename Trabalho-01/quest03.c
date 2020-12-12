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


// quebra a linha em palvras e adicionas na avores 
void add_str(No **raiz, char *linha){

	No *a;
	char *sub;
	sub = strtok(linha, " ,.");

	while(sub != NULL){
		a = aloca_arv(sub);
		insere_arv(&(*raiz), a);
		sub = strtok(NULL," ,.");
	}
}

// Leitura do arquivo
void add_arquivo_arv(No **raiz){
	FILE *arq;
  	char linha[250];
  	char *result;
  	int i = 1;

  	arq = fopen("texto.txt", "rt");
  	if (arq == NULL){
    	printf("Problemas na abertura do arquivo\n");
     	return;
  	}
  	
  	while (!feof(arq)){
      	result = fgets(linha, 250, arq); 
      	if (result){
      		linha[strcspn(linha, "\n")] = 0; //remove o /n
      		add_str(&(*raiz), linha);
      		i++;
      	}
  	}
  	fclose(arq);

}

int main(){
	No *raiz;
	raiz = NULL;


	add_arquivo_arv(&raiz);
	imprime_arv(raiz);

	return 0;
}
