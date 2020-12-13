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

void insere_lst(Lista **l, int i){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = i;
	novo->prox = *l;
	
	*l = novo;
}


No *aloca_arv(char *palavra, int id_linha){

    No *nova;

    nova = (No*)malloc(sizeof(No));

    strncpy(nova->palavra, palavra, strlen(palavra));    
    insere_lst(&nova->linha, id_linha);
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

        else
        	insere_lst(&(*raiz)->linha, a->linha->info);
    }        
}


void imprime_lst(Lista* l){
	
	Lista* p;
	p = l;
	if(p != NULL){
		printf("%d, ", p->info);
		imprime_lst(p->prox);
	}
}

// em ordem 
void imprime_arv(No *raiz){
	if(raiz != NULL){
		imprime_arv(raiz->esq);
		imprime_lst(raiz->linha);
		printf("%s\n",raiz->palavra);
		imprime_arv(raiz->dir);
	}
}

int buscarArvBB(No *raiz, char *elem, int i){ 
    int encontrei = 0;

    if(raiz != NULL){
        if(strcmp(elem, raiz->palavra) < 0){
            // printf("Passo %d: %s\n",i, raiz->palavra);
	        encontrei = buscarArvBB(raiz->esq, elem, i+1);
        }else if(strcmp(elem, raiz->palavra) > 0){
            // printf("Passo %d: %s\n",i, raiz->palavra);
		    encontrei = buscarArvBB(raiz->dir, elem, i+1);
        }else{
            encontrei = 1;
            printf("Palavra encontrada na linha: ");
            imprime_lst(raiz->linha);
            printf("\nNumero de passos: %d\n", i);
         
        }
   }
	
    return(encontrei);	
}


// quebra a linha em palvras e adicionas na avores 
void add_str(No **raiz, char *linha, int id_linha){

	No *a;
	char *sub;
	linha[strcspn(linha, "\n")] = 0; //remove o "/n" do final da linha
	sub = strtok(linha, " ,.");

	while(sub != NULL){
		a = aloca_arv(sub, id_linha);
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
      		add_str(&(*raiz), linha, i);
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
	char nome[10] = "certo";
	buscarArvBB(raiz, nome, 0);	

	return 0;
}