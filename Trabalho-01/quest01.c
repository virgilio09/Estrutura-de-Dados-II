#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct arvAVL{

    int info;
    int altura;
    struct arvAVL *esq, *dir;
    
        
}No;

No *aloca_arv(int valor){

    No *nova;
    
    nova = (No*)malloc(sizeof(No));
    
    nova->info = valor;
    nova->altura = 0;
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;

}


// calcula a altura da arvore 
int altura(No *raiz){
    int alt = -1;

    if(raiz != NULL)
        alt = raiz->altura;

    return alt;

}


int maior(int x, int y){
    int m;

    if(x > y)
        m = x;
    else
        m = y;

    return m;
}

// aloca e insere, retorna a nova arvare 
void insere(No **raiz, No *a){

    if(*raiz == NULL)
        *raiz = a;

    else{
        if(a->info < (*raiz)->info)
            insere(&(*raiz)->esq, a);

        else
            insere(&(*raiz)->dir, a);

    (*raiz)->altura = maior(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
    } 
       
}

// imprime a arvore em in-ordem
void inordem(No *a){
    if(a != NULL){
        printf(" %d = %d\n", a->info, a->altura);
        inordem(a->esq);
        inordem(a->dir);
    }
}

// bucar por um elemento na arvore, e mostra o caminho percorrido
int buscarArvBB(No *raiz, int elem){ 
    int encontrei = 0;

    if(raiz != NULL){
        if(elem < raiz->info){
            printf("%d\n",raiz->info);
	        encontrei = buscarArvBB(raiz->esq, elem);
        }else if(elem > raiz->info){
            printf("%d\n",raiz->info);
		    encontrei = buscarArvBB(raiz->dir, elem);
        }else{
            encontrei = 1;
        }
   }
	
    return(encontrei);	
}


//  busca por elementos destintos na arvores 
void bucar_elementos(No *raiz, int qtd_buscas){

    int achou;
    
    if(raiz != NULL){
        while(qtd_buscas != 0){

            int valor = rand()%100;
            printf("Caminho percorrido para encontrar %d\n",valor);
            achou = buscarArvBB(raiz,valor);

            if(achou)
                printf("Elemento encontrado\n");
            else
                printf("Elemento nao existe\n");

            qtd_buscas--;
        }
    }

}


// cria uma arvore com base na altura
void criar_arvore(No **raiz, int alt){

    No *a;
    int num;
    
    num = 1 + rand() % 99;
    a = aloca_arv(num);
    insere(&(*raiz), a);

    if((*raiz)->altura != alt)
        criar_arvore(&(*raiz), alt);

}


int main(){
    No *raiz;

    raiz = NULL;

    srand((unsigned) time(NULL));

    clock_t ti, tf; // tempo inicia e  final
    

    // primeira tesete
    criar_arvore(&raiz, 50);

    ti = clock();
    bucar_elementos(raiz, 1);
    tf = clock();

    printf("\nTempo de execusão em nanosegundos: %ld\n", (tf-ti)*1000000);


}