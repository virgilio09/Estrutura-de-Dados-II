#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct lista_ing{
	char info[50];
	struct lista_ing *prox;
}Lista_ing;


typedef struct arv_dircionario{
    char infoPort[50];
    Lista_ing *lista_ing;
    int altura;
    struct arv_dircionario *esq, *dir;
}No;

void insere_lst_ing(Lista_ing **l, char *str_ing);

No *aloca_arv(char *str_port, char *str_ing );

int altura(No *raiz);

int fator_balanceamento(No *raiz);

int maior(int x, int y);

void rotacaoDir(No **raiz);

void rotacaoEsq(No **raiz);

void rotacaoDirEsq(No **raiz);

void rotacaoEsqDir(No **raiz);

int insereAVL(No **raiz, No *p);

void add_str(char *linha, No **raiz);

void add_arq_arv(No **raiz);

void imprime_lst(Lista_ing* l);

void imprime_arv(No *raiz);

int qtd_filhos(No *raiz);

No *menorfilho(No **raiz);

int excluirAVL(No **raiz, char *palavra);

int busca(No *raiz, char *palvra);


int main(){
	No *raiz;
    raiz = NULL;

    char palavra[30];

    add_arq_arv(&raiz);

       int op;

    do{
       printf("\n1 - Buscar\n");
       printf("2 - Imprimir\n");
       printf("3 - Excluir\n");
       printf("4 - Sair\n-> ");
       scanf("%d",&op);

       switch (op){
            case 1:
                printf("Informe uma palavra: ");
                scanf("%s",palavra);

                if(busca(raiz, palavra)){}
    
                else
                    printf("Palavara nao encontrada!\n");
                break;
            case 2:
                imprime_arv(raiz);
                break;
            case 3:
                printf("Informe uma palavra: ");
                scanf("%s",palavra);

                if(excluirAVL(&raiz, palavra))
                    printf("Palavara excluida com sucesso!\n");
                else
                    printf("Palavara nao encontrada!\n");

            case 4:
                break;
            
            default:
                printf("Opcao invalida\n");
                break;
       }
    }while (op != 4);




   

	return 0;
}

void insere_lst_ing(Lista_ing **l, char *str_ing){
  
    Lista_ing *nova = (Lista_ing*)malloc(sizeof(Lista_ing));
    strncpy(nova->info, str_ing, strlen(str_ing));    
    nova->prox = *l;
    *l = nova;
  
}

No *aloca_arv(char *str_port, char *str_ing ){

    No *nova;

    nova = (No*)malloc(sizeof(No));

    strcpy(nova->infoPort, str_port);    
    insere_lst_ing(&nova->lista_ing, str_ing);
    nova->altura = 0;
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
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

int insereAVL(No **raiz, No *p){
	int inseriu = 1;

	if(*raiz == NULL)
		*raiz = p;

	else{ 	
		 if(strcmp(p->infoPort, (*raiz)->infoPort) < 0){
			int fb;
			inseriu = insereAVL(&(*raiz)->esq, p);
			if(inseriu){
				fb = fator_balanceamento(*raiz);
				if(fb >= 2){

					if(strcmp(p->infoPort, (*raiz)->esq->infoPort) < 0)
						rotacaoDir(raiz);
					else
						rotacaoEsqDir(raiz);
				}
			}
		}
		else if(strcmp(p->infoPort, (*raiz)->infoPort) > 0){
				int fb;
				inseriu = insereAVL(&(*raiz)->dir, p);

				if(inseriu){
					fb = fator_balanceamento(*raiz);

					if(fb <= -2){
						if(strcmp(p->infoPort, (*raiz)->dir->infoPort) > 0)
							rotacaoEsq(raiz);
						else
							rotacaoDirEsq(raiz);
					}
				}
			}

		else{
			inseriu = 0;
			insere_lst_ing(&(*raiz)->lista_ing, p->lista_ing->info);
		}
	(*raiz)->altura = maior(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
	}
	
	return inseriu;
}

// quebra a linha em palvras e adicionas na avores 
void add_str(char *linha, No **raiz){

    No *a;
    // clock_t ti, tf;

    char *str_ing, *str_pt, copy_linha[100];
    int cont = 0; // pular a palavra
    
    linha[strcspn(linha, "\n")] = 0; //remove o "/n" do final da linha
    strncpy(copy_linha, linha, strlen(linha));  

    str_ing = strtok(copy_linha, ":");
    str_pt = strtok(linha, " :,");

    while(str_pt != NULL){

        if(cont != 0){
            a = aloca_arv(str_pt, str_ing);
            // ti = clock();
            insereAVL(&(*raiz), a);
            // tf = clock();
            // printf("%ld\n", (tf-ti)*1000000);


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
    int unidade = 1;

    arq = fopen("vocabulario.txt", "rt");
    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    
    while(!feof(arq)){
        result = fgets(linha, 100, arq); 
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

int qtd_filhos(No*raiz){

    int filho = 0; //é folha

    if (raiz->esq != NULL && raiz->dir != NULL) 
        filho = 1; // dois filhos
    if (raiz->esq != NULL)
        filho = 2; //filho direita
    else 
        filho = 3; //filho da esq


    return filho;
}

No *menorfilho(No **raiz) {
    No *menor;

    if((**raiz).esq != NULL)
        menor = menorfilho(&(**raiz).esq);
    else 
        menor = *raiz;
    
    return menor;
}


int excluirAVL(No **raiz, char *palavra){

	int removeu = 0;

    if(*raiz != NULL){

		if(strcmp(palavra, (**raiz).infoPort) < 0){
			int fb;
			removeu = excluirAVL(&(*raiz)->esq, palavra);
			if(removeu){
				fb = fator_balanceamento(*raiz);
				if(fb >= 2){
					
					if(strcmp(palavra, (**raiz).infoPort) < 0)
						rotacaoDir(raiz);
					else
						rotacaoEsqDir(raiz);
				}
			}
		}
		else if(strcmp(palavra, (**raiz).infoPort) > 0){
                removeu = 1;
				int fb;
				removeu = excluirAVL(&(*raiz)->dir, palavra);

				if(removeu){
					fb = fator_balanceamento(*raiz);

					if(fb <= -2){
						if(strcmp(palavra, (**raiz).infoPort) > 0)
							rotacaoEsq(raiz);
						else
							rotacaoDirEsq(raiz);
					}
				}
			}

		else{
            removeu = 1;
			No *aux;
            aux = *raiz;

            if(qtd_filhos(*raiz) == 0)
                *raiz = NULL;

            else if(qtd_filhos(*raiz) == 2) 
                *raiz = (**raiz).esq;

            else if(qtd_filhos(*raiz) == 3) 
                *raiz = (**raiz).dir;

            else if(qtd_filhos(*raiz) == 1){
            	No *menor;
                menor = menorfilho(&(**raiz).dir);
                menor->esq = (**raiz).esq;
                *raiz = (**raiz).dir;
                int fb;
                fb = fator_balanceamento(*raiz);
				if(fb >= 2){
					
					if(strcmp(palavra, (**raiz).infoPort) < 0)
						rotacaoDir(raiz);
					else
						rotacaoEsqDir(raiz);
				}


            }

            free(aux);

		}

    }

    return removeu;
}


int busca(No *raiz, char *palavra){

    int encontrou = 0;

     if(raiz != NULL){

        if(strcmp(palavra, raiz->infoPort) < 0)
           encontrou = busca(raiz->esq, palavra);

        else if(strcmp(palavra, raiz->infoPort) > 0)
            encontrou = busca(raiz->dir, palavra);

        else{
            encontrou = 1; 
            printf("%s: ", raiz->infoPort);
            imprime_lst(raiz->lista_ing);
        }
    }    

    return encontrou;    
}