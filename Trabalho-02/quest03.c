#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_ing{
	char info[50];
	struct lista_ing *prox;
}Lista_ing;

typedef struct chave_dic{
    char info[30];
    Lista_ing *lista_ing;
}Chave_dic;

typedef struct arv_dircionario{
    Chave_dic *chaveEsq, *chaveDir;
    int nChaves;
    struct arv_dircionario *esq, *centro, *dir;
}No;


void insere_lst_ing(Lista_ing **l, char *str_ing);

void alocaChaveDic(Chave_dic **chave);

No *criaNO(char *infoPort, char *infoIng, No *noEsq, No *noCentro);

void imprimirArv23(No *raiz);

void imprime_lst(Lista_ing* l);

No *adicionaNo(No *raiz, char *infoPort, char *infoIng, No *novo);

int folha(No *raiz);

No *quebraNo(No **raiz, No *novoNo, char *infoPort, char *infoIng, char *infoMeio);

No *insere23(No **pai, No **raiz, char *infoPort, char *infoIng, char *infoMeio);

int main(){
    No *raiz = NULL;
    char infoMeio[30];

    insere23(NULL, &raiz, "banana","teste2 - 2", infoMeio);
    insere23(NULL, &raiz, "abacaxi", "teste2 - 1", infoMeio);
    insere23(NULL, &raiz, "dabacaxi", "teste2 - 3", infoMeio);
  
  
 
    // insere23(NULL, &raiz, "caja", infoMeio);
    // insere23(NULL, &raiz, "doce", infoMeio);
    // insere23(NULL, &raiz, "feijao", infoMeio);

    imprimirArv23(raiz);

    // imprime_lst(raiz->chaveEsq->lista_ing);

    printf("\n");


    return 0;
}

void insere_lst_ing(Lista_ing **l, char *str_ing){
  
    Lista_ing *nova = (Lista_ing*)malloc(sizeof(Lista_ing));
    strcpy(nova->info, str_ing);    
    nova->prox = *l;
    *l = nova;
  
}

void alocaChaveDic(Chave_dic **chave){
    *chave = (Chave_dic*) malloc(sizeof(Chave_dic));
}

No *criaNO(char *infoPort, char *infoIng, No *noEsq, No *noCentro){
    No *no = (No*) malloc(sizeof(No));

    alocaChaveDic(&no->chaveEsq);
    no->chaveDir = NULL;

    strcpy(no->chaveEsq->info, infoPort);
    insere_lst_ing(&no->chaveEsq->lista_ing, infoIng);
    no->chaveDir = NULL;
    no->nChaves = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;

    return no;
}

void imprimirArv23(No *raiz){
    if(raiz != NULL){
        printf("%s %s %d\n", raiz->chaveEsq->info, raiz->chaveDir->info, raiz->nChaves);
        // imprime_lst(raiz->chaveEsq->lista_ing);
        // if(raiz->chaveDir != NULL)
        //     imprime_lst(raiz->chaveDir->lista_ing);
        imprimirArv23(raiz->esq);
        imprimirArv23(raiz->centro);
        imprimirArv23(raiz->dir);
    }
}


void imprime_lst(Lista_ing *l){
    
    Lista_ing* p;
    p = l;
    if(p != NULL){
        printf("%s, ", p->info);
        imprime_lst(p->prox);
    }
}


No *adicionaNo(No *raiz, char *infoPort, char *infoIng, No *novo){
    //comparar string
    int tam = strcmp(infoPort, raiz->chaveEsq->info);
    int adicionou = 1;

    if(tam > 0){
        alocaChaveDic(&raiz->chaveDir);
        strcpy(raiz->chaveDir->info, infoPort);
        insere_lst_ing(&raiz->chaveDir->lista_ing, infoIng);
        raiz->dir = novo;        
    }
    else if(tam < 0){
        alocaChaveDic(&raiz->chaveDir);
        raiz->chaveDir = raiz->chaveEsq;
        raiz->chaveEsq = NULL;
        alocaChaveDic(&raiz->chaveEsq);
        
        strcpy(raiz->chaveEsq->info, infoPort);
        insere_lst_ing(&raiz->chaveEsq->lista_ing, infoIng);
        raiz->dir = raiz->centro;
        raiz->centro = novo;

    }else{
         insere_lst_ing(&raiz->chaveEsq->lista_ing, infoIng);
         adicionou = 0;
    }

    if(adicionou)
        raiz->nChaves = 2;

    return raiz;

}

int folha(No *raiz) {
    int folha = 0;

    if (raiz->esq == NULL && raiz->centro == NULL && raiz->dir == NULL)
        folha = 1;
    
    return folha;
}

No *quebraNo(No **raiz, No *novoNo, char *infoPort, char *infoIng, char *infoMeio){

    No *novo;

    if(strcmp(infoPort, (**raiz).chaveDir->info) > 0){
        strcpy(infoMeio, (**raiz).chaveDir->info);
        novo = criaNO(infoPort, infoIng, (**raiz).dir, novoNo);
    }
//     else if(strcmp(info, (**raiz).chave_esq) < 0){
//         strncpy(infoMeio, (**raiz).chave_esq, strlen((**raiz).chave_esq));  
//         novo = criaNO((**raiz).chave_dir, (**raiz).centro, (**raiz).dir);
        
//         strncpy((**raiz).chave_esq, info, strlen(info));
//         (**raiz).centro = novoNo;
//     }
//     else{
//         strncpy(infoMeio, info, strlen(info));
//         novo = criaNO((**raiz).chave_dir, novoNo, (**raiz).dir);  
//     }

//     strncpy((**raiz).chave_dir, "#", 1);
//     (**raiz).nChaves = 1;
//     (**raiz).dir = NULL;

    return novo; 
}

No *insere23(No **pai, No **raiz, char *infoPort, char *infoIng, char *infoMeio){
    No *novo;

    if(*raiz == NULL){
        *raiz = criaNO(infoPort, infoIng, NULL, NULL);
    }
    else{
        if(folha(*raiz)){
           
            if((**raiz).nChaves == 1){
                *raiz = adicionaNo(*raiz, infoPort, infoIng, NULL);
                novo = NULL;
            }
            else{
                novo = quebraNo(raiz, NULL, infoPort, infoIng, infoMeio);
                
                if(pai == NULL) {
                    *raiz = criaNO(infoMeio, infoIng, *raiz, novo);
                    novo = NULL; 
			    }
            }
        }
    //     else{
    //         if(strcmp(info, (*raiz)->chave_esq) < 0)
    //             novo = insere23(raiz, &(**raiz).esq, info, infoMeio);
            
    //         else if(strcmp(info, (*raiz)->chave_dir) < 0 || (**raiz).nChaves == 1)
    //             novo = insere23(raiz, &(**raiz).centro, info, infoMeio);
            
    //         else 
    //             novo = insere23(raiz, &(**raiz).dir, info, infoMeio);

    //         if(novo != NULL){
    //             if((**raiz).nChaves == 1) {
    //                 *raiz = adicionaNo(*raiz, infoMeio, novo);
    //                 novo = NULL;
    //             }else{
    //                 char auxMeio[30];
    //                 strcpy(auxMeio, infoMeio);
    //                 novo = quebraNo(raiz, novo, auxMeio, infoMeio);
                
    //                 if (pai == NULL) {
    //                     *raiz = criaNO(infoMeio, *raiz, novo);
    //                     novo = NULL; 
    //                 }
    //             }
    //         }

    //     }
    }
    return novo;
}
