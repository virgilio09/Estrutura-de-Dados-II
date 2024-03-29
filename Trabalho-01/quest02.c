#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
		if(p->info < (*raiz)->info){
			int fb;
			inseriu = insereAVL(&(*raiz)->esq, p);
			if(inseriu){
				fb = fator_balanceamento(*raiz);
				if(fb >= 2){

					if(p->info < (*raiz)->esq->info)
						rotacaoDir(raiz);
					else
						rotacaoEsqDir(raiz);
				}
			}
		}
		else if(p->info > (*raiz)->info){
				int fb;
				inseriu = insereAVL(&(*raiz)->dir, p);

				if(inseriu){
					fb = fator_balanceamento(*raiz);

					if(fb <= -2){
						if(p->info > (*raiz)->dir->info)
							rotacaoEsq(raiz);
						else
							rotacaoDirEsq(raiz);
					}
				}
			}

		else
			inseriu = 0;
	(*raiz)->altura = maior(altura((*raiz)->esq), altura((*raiz)->dir)) + 1;
	}
	
	return inseriu;
}


void imprime(No *a){
    if(a != NULL){
        printf(" %d = %d\n", a->info, a->altura);
        imprime(a->esq);
        imprime(a->dir);
    }
}

// bucar por um elemento na arvore, e mostra o caminho percorrido
int buscarArv(No *raiz, int elem, int i){ 
    int encontrei = 0;

    if(raiz != NULL){
        if(elem < raiz->info){
            printf("Passo %d: %d\n",i, raiz->info);
	        encontrei = buscarArv(raiz->esq, elem, i+1);
        }else if(elem > raiz->info){
            printf("Passo %d: %d\n",i, raiz->info);
		    encontrei = buscarArv(raiz->dir, elem, i+1);
        }else{
            encontrei = 1;
        }
   }
	
    return(encontrei);	
}

//  busca por elementos destintos na arvores 
void bucar_elementos(No *raiz, int qtd_buscas){

    int achou;
    clock_t ti, tf; // tempo inicia e  final
    
    if(raiz != NULL){
        while(qtd_buscas != 0){

            int valor = rand()%100;
            printf("Caminho percorrido para encontrar %d\n",valor);
            
            ti = clock();
            achou = buscarArv(raiz,valor, 0);
            tf = clock();
            
            if(achou)
                printf("Elemento encontrado\n");
            else
                printf("Elemento nao existe\n");


            printf("\nTempo de execusão em nanosegundos: %ld\n", (tf-ti)*1000000);

            qtd_buscas--;
        }
    }

}

// cria uma arvore com base na altura
void criar_arvore(No **raiz, int alt){

    No *a;
    int num;
    
    num = 1 + rand() % 1000000;
    a = aloca_arv(num);
    insereAVL(&(*raiz), a);

    if((*raiz)->altura != alt)
        criar_arvore(&(*raiz), alt);
}

// cria arvore com base na quantidade de elementos
void criar_arvoreElem(No **raiz, int qtd){

    No *a;
    int num;
    clock_t ti, tf;

    for(int i = 0; i < qtd; i++){
        num = 1 + rand() % 100;
        a = aloca_arv(num);
        ti = clock();
        insereAVL(&(*raiz), a);
        tf = clock();

        printf("%ld\n", (tf-ti)*1000000);

    }

}

int main(){
    No *raiz;

    raiz = NULL;

    srand((unsigned) time(NULL));

    // primeira tesete
    // criar_arvore(&raiz, 15);

    // bucar_elementos(raiz, 10);

    criar_arvoreElem(&raiz, 300);
    
}