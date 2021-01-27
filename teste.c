#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaIng{
	char info[50];
	struct listaIng *prox;
}ListaIng;

typedef struct chaveDic{
    char infoPort[30];
    ListaIng *listaIng;
}ChaveDic;

typedef struct arv_dircionario{
    ChaveDic *chaveEsq, *chaveDir;
    int nChaves;
    struct arv_dircionario *esq, *centro, *dir;
}No;


void insereLstIng(ListaIng **l, char *str_ing);

ChaveDic *alocaChaveDic(char *infoPort, char *infoIng);

No *criaNO(ChaveDic *info, No *noEsq, No *noCentro);

void imprimirArv23(No *raiz);

void imprimeLst(ListaIng* l);

ListaIng *copyList(ListaIng **listaDir, ListaIng *listaEsq);

No *adicionaNo(No *raiz, ChaveDic *info, No *novo);

int folha(No *raiz);

No *quebraNo(No **raiz, No *novoNo, ChaveDic *info, ChaveDic *infoMeio);

No *insere23(No **pai, No **raiz, char *infoPort, char *infoIng, ChaveDic  *infoMeio);

void add_str(char *linha, No **raiz);

void add_arq_arv(No **raiz);



int main(){
    No *raiz = NULL;
    ChaveDic *infoMeio = = (ChaveDic*)malloc(sizeof(ChaveDic));

    // add_arq_arv(&raiz);


    insere23(NULL, &raiz, "vermelho", " red", infoMeio);
   
    insere23(NULL, &raiz, "garoto","boy", infoMeio);
   
    insere23(NULL, &raiz, "menino", "boy", infoMeio);
 
    // insere23(NULL, &raiz, "casa", "house", infoMeio);
    // insere23(NULL, &raiz, "maca", "apple",infoMeio);
    // insere23(NULL, &raiz, "casa", "home", infoMeio);

    //  insere23(NULL, &raiz, "coputador", "pc", infoMeio);
    // insere23(NULL, &raiz, "lar", "home", infoMeio);

    // imprimirArv23(raiz);
    // mostrar(raiz);


    printf("%s", raiz->chaveEsq->infoPort);
    // imprimeLst(raiz->chaveDir->listaIng);

    printf("\n");


    return 0;
}

void insereLstIng(ListaIng **l, char *str_ing){
  
    ListaIng *nova = (ListaIng*)malloc(sizeof(ListaIng));
    strcpy(nova->info, str_ing);   
    nova->prox = *l;
    *l = nova;
  
}

ChaveDic *alocaChaveDic(char *infoPort, char *infoIng){
    ChaveDic *chave = (ChaveDic*) malloc(sizeof(ChaveDic));

    strcpy(chave->infoPort, infoPort);
    insereLstIng(&chave->listaIng, infoIng);

    return chave;
    
}

No *criaNO(ChaveDic *info, No *noEsq, No *noCentro){
    No *no = (No*) malloc(sizeof(No));

    no->chaveEsq = (ChaveDic*) malloc(sizeof(ChaveDic));
    no->chaveDir = (ChaveDic*) malloc(sizeof(ChaveDic));

    strcpy(no->chaveEsq->infoPort, info->infoPort);
    copyList(&no->chaveEsq->listaIng, info->listaIng);

    strcpy(no->chaveDir->infoPort, "#");
    no->chaveDir->listaIng = NULL;

    no->nChaves = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;

    return no;
}

void imprimirArv23(No *raiz){
    if(raiz != NULL){

        imprimirArv23(raiz->esq);

        printf("\n%s: ",raiz->chaveEsq->infoPort);
        // imprimeLst(raiz->chaveEsq->listaIng);
        printf("\n%s: ",raiz->chaveDir->infoPort);
        // imprimeLst(raiz->chaveDir->listaIng);

        imprimirArv23(raiz->centro);
       
        imprimirArv23(raiz->dir);
       
    }
}


void imprimeLst(ListaIng *l){
    
    ListaIng* p;
    p = l;
    if(p != NULL){
        printf("%s, ", p->info);
        imprimeLst(p->prox);
    }
}

ListaIng *copyList(ListaIng **listaDir, ListaIng *listaEsq) {
    ListaIng *aux;
    aux = listaEsq; 
    *listaDir = NULL;

    while(aux != NULL){
        insereLstIng(&(*listaDir), aux->info);
        aux = aux->prox;  ;
    
    }
}

No *adicionaNo(No *raiz, ChaveDic *info, No *novo){
    // comparar string
    int tam = strcmp(info->infoPort, raiz->chaveEsq->infoPort);


    if(tam > 0){
        strcpy(raiz->chaveDir->infoPort, info->infoPort);
        copyList(&raiz->chaveDir->listaIng, info->listaIng);
        raiz->dir = novo;        
    }
    else if(tam < 0){
        strcpy(raiz->chaveDir->infoPort, (*raiz).chaveEsq->infoPort);
        strcpy(raiz->chaveEsq->infoPort, info->infoPort);
        copyList(&raiz->chaveDir->listaIng, raiz->chaveEsq->listaIng);
        
        raiz->chaveEsq->listaIng = NULL;
        copyList(&raiz->chaveEsq->listaIng, info->listaIng);
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

No *quebraNo(No **raiz, No *novoNo, ChaveDic *info, ChaveDic *infoMeio){

    No *novo;

    if(strcmp(info->infoPort, (**raiz).chaveDir->infoPort) > 0){
        strcpy(infoMeio->infoPort, (**raiz).chaveDir->infoPort);
        copyList(&infoMeio->listaIng, (**raiz).chaveDir->listaIng);
        
        ChaveDic *info1 = (ChaveDic*) malloc(sizeof(ChaveDic));
        strcpy(info1->infoPort, info->infoPort);
        info1->listaIng = NULL;
        copyList(&info1->listaIng, info->listaIng);
        
        novo = criaNO(info1, (**raiz).dir, novoNo);
    }
    else if(strcmp(info->infoPort, (**raiz).chaveEsq->infoPort) < 0){
        strcpy(infoMeio->infoPort, (**raiz).chaveEsq->infoPort);
        copyList(&infoMeio->listaIng, (**raiz).chaveEsq->listaIng);
        
        ChaveDic *info1 = (ChaveDic*) malloc(sizeof(ChaveDic));
        strcpy(info1->infoPort, (**raiz).chaveDir->infoPort);
    
        novo = criaNO(info1, (**raiz).centro, (**raiz).dir);

        strcpy((**raiz).chaveEsq->infoPort, info->infoPort);
        copyList(&(**raiz).chaveEsq->listaIng, info->listaIng);
        (**raiz).centro = novoNo;
    }
    else{
        strcpy(infoMeio->infoPort, info->infoPort);
        copyList(&infoMeio->listaIng, info->listaIng);

        ChaveDic *info = (ChaveDic*) malloc(sizeof(ChaveDic));
        strcpy(info->infoPort, (**raiz).chaveDir->infoPort); 
        info->listaIng = NULL;
        copyList(&info->listaIng, (**raiz).chaveDir->listaIng);
    }

    strcpy((**raiz).chaveDir->infoPort, "#");
    (**raiz).chaveDir->listaIng = NULL;
    (**raiz).nChaves = 1;
    (**raiz).dir = NULL; 

    return novo; 
}

No *insere23(No **pai, No **raiz, char *infoPort, char *infoIng, ChaveDic *infoMeio){
    No *novo;

    if(*raiz == NULL){
        printf("ok 1\n");
        ChaveDic *info = alocaChaveDic(infoPort, infoIng); 
        *raiz = criaNO(info, NULL, NULL);
    }
    else{

        if(strcmp(infoPort, (**raiz).chaveEsq->infoPort) == 0){
            insereLstIng(&(**raiz).chaveEsq->listaIng, infoIng);
            novo = NULL;
        }
       
        else if(strcmp(infoPort, (**raiz).chaveDir->infoPort) == 0){
            insereLstIng(&(**raiz).chaveDir->listaIng, infoIng);
            novo = NULL;
        }
        else{
            if(folha(*raiz)){

                if((**raiz).nChaves == 1){
                    printf("ok 2\n");
                    ChaveDic *info = alocaChaveDic(infoPort, infoIng); 
                    *raiz = adicionaNo(*raiz, info, NULL);
                    novo = NULL;
                }
                else{
                    ChaveDic *info = alocaChaveDic(infoPort, infoIng); 
                    
                    novo = quebraNo(raiz, NULL, info, infoMeio);
                    
                    if(pai == NULL) {
                        *raiz = criaNO(infoMeio, *raiz, novo);
                        novo = NULL; 
                    }
                }
            }
            else{
                if(strcmp(infoPort, (*raiz)->chaveEsq->infoPort) < 0)
                    novo = insere23(raiz, &(**raiz).esq, infoPort, infoIng, infoMeio);
                
                else if(strcmp(infoPort, (*raiz)->chaveDir->infoPort) < 0 || (**raiz).nChaves == 1)
                    novo = insere23(raiz, &(**raiz).centro, infoPort, infoIng, infoMeio);
                else 
                    novo = insere23(raiz, &(**raiz).dir, infoPort, infoIng, infoMeio);
            
                if(novo != NULL){
                    if((**raiz).nChaves == 1){
                        *raiz = adicionaNo(*raiz, infoMeio, novo);
                        novo = NULL;
                    }else{
                        ChaveDic *info = (ChaveDic*) malloc(sizeof(ChaveDic));
                        strcpy(info->infoPort, infoMeio->infoPort); 
                        info->listaIng = NULL;
                        copyList(&info->listaIng, infoMeio->listaIng);
                            
                        novo = quebraNo(raiz, novo, info, infoMeio);
                        
                        if (*pai == NULL){
                            *raiz = criaNO(infoMeio, *raiz, novo);
                            novo = NULL; 
                        }
                    }
                }
            }
        }
    }
        return novo;
}

// quebra a linha em palvras e adicionas na avores 
void add_str(char *linha, No **raiz){

    No *a;
    // ChaveDic *infoMeio;

    char *str_ing, *str_pt, copy_linha[100];
    int cont = 0; // pular a palavra
    
    linha[strcspn(linha, "\n")] = 0; //remove o "/n" do final da linha
    strncpy(copy_linha, linha, strlen(linha));  

    str_ing = strtok(copy_linha, ":");
    str_pt = strtok(linha, " :,");

    while(str_pt != NULL){

        if(cont != 0){
        
            ChaveDic *infoMeio = (ChaveDic*) malloc(sizeof(ChaveDic));
            strcpy((*infoMeio).infoPort, "#");
            (*infoMeio).listaIng = NULL;
        
            insere23(NULL, &(*raiz), str_pt, str_ing, infoMeio);
            printf("%s %s\n", str_pt, str_ing);
            // printf("Inserido\n");
                
           
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