#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "ListaDinamica.h"

struct produto {
	char modelo[20];
	int quant;
	char cor[20];
	int ano;
	float valor;
};

typedef struct itens {
	tipo dados;
	struct itens * prox;
}item;

struct Lista {
	item * inicio;
};

int criaL(LISTA ** temp) {
	(*temp) = (LISTA*) malloc(sizeof(LISTA));
	if ((*temp) == NULL)
		return 0;
	else {
		(*temp)->inicio = NULL;
		return 1;
	}
}

int liberaL(LISTA * temp) {
	free(temp);
	return 0;
}

int tamanhoL(LISTA *temp) {
	if (temp == NULL)
		return -1;
	int tam = 0;
	item *no = temp->inicio;

	while (no != NULL) {
		tam++;
		no = no->prox;
	}
	return tam;
}

int cheiaL(LISTA *temp) {
	if (temp == NULL)
		return -1;
	return 0;
}

int vaziaL(LISTA *temp) {
	if (temp == NULL)
		return -1;
	if (temp->inicio == NULL)
		return 1;
	else
		return 0;
}

int insereInicioL(LISTA *temp,tipo dado) {
	if (temp == NULL)
		return 0;
	if (cheiaL(temp))
		return 0;
	item * no;
	no = (item *) malloc(sizeof(item));
	if (no == NULL)
		return 0;
	no->dados = dado;
	no->prox = temp->inicio;

	temp->inicio = no;

	return 1;
}

int insereFimL(LISTA *temp,tipo dado) {
	if (temp == NULL)
		return 0;
	if (cheiaL(temp))
		return 0;
	item * no;
	no = (item *) malloc(sizeof(item));
	if (no == NULL)
		return 0;
	no->dados = dado;
	no->prox = NULL;

	if (temp->inicio == NULL) {
		temp->inicio = no;
		return 1;
	}

	item *aux = temp->inicio;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = no;
	return 1;
}

int inserePosL(LISTA *temp,tipo dado,int pos) {
	pos--;
	if (temp == NULL)
		return 0;
	if (cheiaL(temp))
		return 0;
	if (pos < 0 || tamanhoL(temp) < pos)
		return 0;


	item * no;
	no = (item *) malloc(sizeof(item));
	if (no == NULL)
		return 0;

	no->dados = dado;
	no->prox = NULL;

	if (pos == 0) {
		no->prox = temp->inicio;
		temp->inicio = no;
		return 1;
	}

	int tam = 1;
	item *aux = temp->inicio;

	while (pos != tam) {
		tam++;
		aux = aux->prox;
	}
	no->prox = aux->prox;
	aux->prox = no;

	return 1;
}

int removeInicioL(LISTA *temp,tipo *dado) {
	if (temp == NULL)
		return 0;
	if (vaziaL(temp))
		return 0;

	item * no = temp->inicio;
	*dado = no->dados;
	temp->inicio = no->prox;

	free(no);
	return 1;
}

int removeFimL(LISTA *temp,tipo *dado) {
	if (temp == NULL)
		return 0;
	if (vaziaL(temp))
		return 0;

	item * aux = NULL;
	item * no = temp->inicio;

	while (no->prox != NULL) {
		aux = no;
		no = no->prox;
	}
	if (tamanhoL(temp) == 1)
		temp->inicio = NULL;
	else
		aux->prox = NULL;
	*dado = no->dados;
	free(no);

	return 1;
}

int removePosL(LISTA *temp,tipo *dado,int pos) {
	pos--;
	if (temp == NULL)
		return 0;
	if (vaziaL(temp))
		return 0;
	if (pos < 0 || tamanhoL(temp) < pos)
		return 0;

	int tam = 0;
	item * aux = NULL;
	item * no = temp->inicio;

	while (pos != tam) {
		tam++;
		aux = no;
		no = no->prox;
	}

	if (pos == 0)
		temp->inicio = no->prox;
	else
		aux->prox = no->prox;
	*dado = no->dados;
	free(no);

	return 1;
}

int consultaL(LISTA *temp,tipo *dado,int pos) {
	pos--;
	if (temp == NULL)
		return 0;
	if (vaziaL(temp))
		return 0;
	if (pos < 0 || tamanhoL(temp) < pos)
		return 0;

	int tam = 0;
	item * no = temp->inicio;

	while (pos != tam) {
		tam++;
		no = no->prox;
	}
	*dado = no->dados;

	return 1;
}