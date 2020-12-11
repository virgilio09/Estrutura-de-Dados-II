#include <stdio.h>
#include <stdio.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Lista;

typedef struct arv{
	Lista *linha;
	char palavra[50];
	struct arv *esq, *dir;
}No;




