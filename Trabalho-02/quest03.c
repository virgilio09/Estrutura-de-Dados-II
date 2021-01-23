#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_ing{
	char info[50];
	struct lista_ing *prox;
}Lista_ing;

typedef struct arv_dircionario{
    char chave_esq[50], chave_dir[50];
    int nChaves;
    Lista_ing *lista_ing;
    struct arv_dircionario *esq, *centro, *dir;
}No;

No *criaNO(char *info, No *noEsq, No *noCentro);

No *adicionaNo(No *raiz, char *info, No *novo);

int folha(No *raiz);

No *quebraNo(No **raiz, No *novoNo, char *info, char *infoMeio);

No *insere23(No *pai, No **raiz, char *info, char *infoMeio);

void imprimirArv23(No *raiz);

int main(){
    No *raiz = NULL;
    char infoMeio[30];

    insere23(NULL, &raiz, "baa", infoMeio);
    insere23(NULL, &raiz, "abb", infoMeio);
    insere23(NULL, &raiz, "cbb", infoMeio);
    // insere23(NULL, &raiz, "dff", infoMeio);

    imprimirArv23(raiz);

    return 0;
}

No *criaNO(char *info, No *noEsq, No *noCentro){
    No *no = (No*) malloc(sizeof(No));

    strncpy(no->chave_esq, info, strlen(info));
    strncpy(no->chave_dir, "#", 1);
    no->nChaves = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;

    return no;
}

No *adicionaNo(No *raiz, char *info, No *novo){

    if(strcmp(info, raiz->chave_esq) > 0){
        strncpy(raiz->chave_dir, info, strlen(info));
        raiz->dir = novo;        
    }else{
        strncpy(raiz->chave_dir, raiz->chave_esq, strlen(raiz->chave_esq));
        strncpy(raiz->chave_esq, info, strlen(info));
        raiz->dir = raiz->centro;
        raiz->centro = novo;
    }

    raiz->nChaves = 2;

    return raiz;

}

int folha(No *raiz) {
    int folha = 0;

    if (raiz->esq == NULL && raiz->centro == NULL && raiz->dir == NULL)
        folha = 1;
    
    return folha;
}

No *quebraNo(No **raiz, No *novoNo, char *info, char *infoMeio){

    No *novo;

    if(strcmp(info, (**raiz).chave_dir) > 0){
        strncpy(infoMeio, (**raiz).chave_dir, strlen((**raiz).chave_dir));
        novo = criaNO(info, (**raiz).dir, novoNo);
    }
    else if(strcmp(info, (**raiz).chave_esq) < 0){
        strncpy(infoMeio, (**raiz).chave_esq, strlen((**raiz).chave_esq));  
        novo = criaNO((**raiz).chave_dir, (**raiz).centro, (**raiz).dir);
        
        strncpy((**raiz).chave_esq, info, strlen(info));
        (**raiz).centro = novoNo;
    }
    else{
        strncpy(infoMeio, info, strlen(info));
        novo = criaNO((**raiz).chave_dir, novoNo, (**raiz).dir);  
    }

    strncpy((**raiz).chave_dir, "#", 1);
    (**raiz).nChaves = 1;
    (**raiz).dir = NULL;

    return novo; 
}

No *insere23(No *pai, No **raiz, char *info, char *infoMeio){
    No *novo;

    if(*raiz == NULL){
        *raiz = criaNO(info, NULL, NULL);
    }
    else{
        if(folha){
            if((**raiz).nChaves == 1){
                *raiz = adicionaNo(*raiz, info, NULL);
                novo = NULL;
            }
            else{
                novo = quebraNo(raiz, NULL, info, infoMeio);
                
                if(pai == NULL) {
                    *raiz = criaNO(infoMeio, *raiz, novo);
                    novo = NULL; 
			    }
            }
        }
        else{
            if(strcmp(info, (*raiz)->chave_esq) < 0)
                novo = insere23(*raiz, &(**raiz).esq, info, infoMeio);
            
            else if((**raiz).nChaves == 1) 
                novo = insere23(*raiz, &(**raiz).centro, info, infoMeio);

            else if(strcmp(info, (*raiz)->chave_dir) < 0)
                novo = insere23(*raiz, &(**raiz).centro, info, infoMeio);
            
            else 
                novo = insere23(*raiz, &(**raiz).dir, info, infoMeio);

            if(novo != NULL){
                if((**raiz).nChaves == 1) {
                    *raiz = adicionaNo(*raiz, infoMeio, novo);
                    novo = NULL;
                }else{
                    novo = quebraNo(raiz, novo, infoMeio, infoMeio);
                
                    if (pai == NULL) {
                        *raiz = criaNO(infoMeio, *raiz, novo);
                        novo = NULL; 
                    }
                }
            }

        }
    }
    return novo;
}

void imprimirArv23(No *raiz){
    if(raiz != NULL){
        printf("%s %s %d\n", raiz->chave_esq, raiz->chave_dir, raiz->nChaves);
        imprimirArv23(raiz->esq);
        imprimirArv23(raiz->centro);
        imprimirArv23(raiz->dir);
    }
}