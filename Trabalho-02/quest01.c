#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_ing{
	char info[50];
	struct lista_ing *prox;
}Lista_ing;


typedef struct arv_dircionario{
    char infoPort[50];
    Lista_ing *lista_ing;
    struct arv_dircionario *esq, *dir;
}No;

typedef struct unidades{
    int unidade;
    No *info;
    struct unidades *prox;

}Unidades;

void insere_lst_ing(Lista_ing **l, char *str_ing){
  
    Lista_ing *nova = (Lista_ing*)malloc(sizeof(Lista_ing));
    strncpy(nova->info, str_ing, strlen(str_ing));    
    nova->prox = *l;
    *l = nova;
  
}

void insere_unidade(Unidades **l, No *raiz, int uni){

    Unidades *nova = (Unidades*)malloc(sizeof(Unidades));
    nova->info = raiz;
    nova->unidade = uni;
    nova->prox = *l;
    *l = nova;

}

No *aloca_arv(char *str_port, char *str_ing ){

    No *nova;

    nova = (No*)malloc(sizeof(No));

    strncpy(nova->infoPort, str_port, strlen(str_port));    
    insere_lst_ing(&nova->lista_ing, str_ing);
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
        	insere_lst_ing(&(*raiz)->lista_ing, a->lista_ing->info);
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
void add_arq_arv(No **raiz, Unidades **lst_uni){

    FILE *arq;
  	char linha[100];
  	char *result;
    int unidade = 0;

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
            
            else{
                if(unidade != 0)
                    insere_unidade(&(*lst_uni), *raiz, unidade);

                *raiz = NULL;
                unidade++;
            }
            
               

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

void imprime_unidades(Unidades* l){
	
	Unidades* p;
	p = l;
	if(p != NULL){
        printf("Unidade %d", p->unidade);
        imprime_arv(p->info);
		imprime_unidades(p->prox);
	}
}



int main(){

    No *raiz;
    Unidades *list_unidades;
    raiz = NULL;
    list_unidades = NULL;

    add_arq_arv(&raiz, &list_unidades);

    imprime_arv(raiz);

    printf("\n");

    imprime_unidades(list_unidades);

    return 0;
}