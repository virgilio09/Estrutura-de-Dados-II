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

int busca_lista(Lista *l, int x){

    int achou = 0;

    if(l != NULL){

        if(l->info == x)
            achou = 1;

        else  
           achou = busca_lista(l->prox, x);

    }

    return achou;
}

void insere_lst(Lista **l, int i){
    
    int insere = busca_lista(*l, i); 
    
    if(insere)
        return;
    
    else{
        Lista* novo = (Lista*) malloc(sizeof(Lista));
        novo->info = i;
        novo->prox = *l;
        *l = novo;

    }    

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



int insereAVL(No **raiz, No *p){
	int inseriu = 1;

	if(*raiz == NULL)
		*raiz = p;

	else{ 	
		if(strcmp(p->palavra, (*raiz)->palavra) < 0){
			int fb;
			inseriu = insereAVL(&(*raiz)->esq, p);
			if(inseriu){
				fb = fator_balanceamento(*raiz);
				if(fb >= 2){

					if(strcmp(p->palavra, (*raiz)->esq->palavra) < 0)
						rotacaoDir(raiz);
					else
						rotacaoEsqDir(raiz);
				}
			}
		}
		else if(strcmp(p->palavra, (*raiz)->palavra) > 0){
				int fb;
				inseriu = insereAVL(&(*raiz)->dir, p);

				if(inseriu){
					fb = fator_balanceamento(*raiz);

					if(fb <= -2){
						if(strcmp(p->palavra, (*raiz)->dir->palavra) > 0)
							rotacaoEsq(raiz);
						else
							rotacaoDirEsq(raiz);
					}
				}
			}

		else{
			inseriu = 0;
			insere_lst(&(*raiz)->linha, p->linha->info);
		}
	(*raiz)->altura = maior(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
	}
	
	return inseriu;
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


// quebra a linha em palvras e adicionas na avores 
void add_str(No **raiz, char *linha, int id_linha){

	No *a;
	char *sub;
	linha[strcspn(linha, "\n")] = 0; //remove o "/n" do final da linha
	sub = strtok(linha, " ,.");

	while(sub != NULL){
		a = aloca_arvAVL(sub, id_linha);
		insereAVL(&(*raiz), a);
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

int buscarArv(No *raiz, char *elem){ 
    int passo = 0;

    if(raiz != NULL){
        if(strcmp(elem, raiz->palavra) < 0){
            passo = 1 + buscarArv(raiz->esq, elem);
        }else if(strcmp(elem, raiz->palavra) > 0){
            passo = 1 + buscarArv(raiz->dir, elem);
        }else{
            // printf("Palavra encontrada na linha: ");
            // imprime_lst(raiz->linha);
         
        }
   }
    
    return passo;  
}

void busca_arq(No *raiz){

    FILE *arq;
    char palavra[50];
    char *result;

    arq = fopen("texto_busca.txt", "rt");
    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    
    while (!feof(arq)){
        result = fgets(palavra, 50, arq); 
        if (result){
            palavra[strcspn(palavra, "\n")] = 0;
            printf("%d\n",buscarArv(raiz, palavra));
        }
        
    }
    fclose(arq);

}

int main(){
	No *raiz;
	raiz = NULL;

	add_arquivo_arv(&raiz);
	// imprime_arv(raiz);

    busca_arq(raiz);
    
    printf("\nAlturo: %d\n\n\n",raiz->altura);

	return 0;
}
