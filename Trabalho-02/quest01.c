#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_ing{
	char info[50];
	struct lista_ing *prox;
}Lista_ing;

typedef struct arv_Vocabulario{
    char infoPort[50];
    Lista_ing *lista_ing;
    struct arv_Vocabulario *esq, *dir;
}No;

void insere_lst(Lista_ing **l, char *str_ing){
  
    Lista_ing *nova = (Lista_ing*)malloc(sizeof(Lista_ing));
    strncpy(nova->info, str_ing, strlen(str_ing));    
    nova->prox = *l;
    *l = nova;
  
}

No *aloca_arv(char *str_port, char *str_ing ){

    No *nova;

    nova = (No*)malloc(sizeof(No));

    strncpy(nova->infoPort, str_port, strlen(str_port));    
    insere_lst(&nova->lista_ing, str_ing);
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}

void insere_arv(No **raiz, No *a){

    if(*raiz == NULL)
        *raiz = a;

    else{
    	if(strcmp(a->infoPort, (*raiz)->infoPort) < 0)
            insere_arv(&(*raiz)->esq, a);

        else if(strcmp(a->infoPort, (*raiz)->infoPort) > 0)
            insere_arv(&(*raiz)->dir, a);

        else
        	insere_lst(&(*raiz)->lista_ing, a->lista_ing->info);
    }        
}

// quebra a linha em palvras e adicionas na avores 
void add_str(char *linha, No **raiz){

    No *a;

    char *str_ing, *str_pt, copy_linha[100];
    int cont = 0; // pular a palavra
    
    linha[strcspn(linha, "\n")] = 0; //remove o "/n" do final da linha
    strncpy(copy_linha, linha, strlen(linha));  

	str_ing = strtok(copy_linha, ":");
    str_pt = strtok(linha, " :,");

    while(str_pt != NULL){

        if(cont != 0){
            a = aloca_arv(str_pt, str_ing);
	    	insere_arv(&(*raiz), a);

        }

        str_pt = strtok(NULL, " :,");
        cont++;
    }
}

// ler arquivo e add na arvore
void add_arq_arv(No **raiz){

    FILE *arq;
  	char linha[100];
  	char *result;

  	arq = fopen("vocabulario.txt", "rt");
  	if (arq == NULL){
    	printf("Problemas na abertura do arquivo\n");
     	return;
  	}
  	
  	while (!feof(arq)){
      	result = fgets(linha, 250, arq); 
      	if (result){
            if(linha[0] != '%')
                add_str(linha, &(*raiz));            

      	}
  	}
  	fclose(arq);

}


void imprime_lst(Lista_ing* l){
	
	Lista_ing* p;
	p = l;
	if(p != NULL){
		printf("%s, ", p->info);
		imprime_lst(p->prox);
	}
}

// em ordem 
void imprime_arv(No *raiz){
	if(raiz != NULL){
		imprime_arv(raiz->esq);
        printf("\n%s: ",raiz->infoPort);
        imprime_lst(raiz->lista_ing);
		imprime_arv(raiz->dir);
	}
}


int main(){

    No *raiz;
    raiz = NULL;

    add_arq_arv(&raiz);
    
    imprime_arv(raiz);

    printf("\n");

    return 0;
}