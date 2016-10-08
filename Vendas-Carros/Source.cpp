#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "ListaDinamica.h"

typedef struct produto {
	char modelo[20];
	int quant;
	char cor[20];
	int ano;
	float valor;
}produtos;

char MainMenu(void);
char MenuProduto(void);

int main() {

	do {

		switch (MainMenu()) {
			case '1':



			break;
			case '4':
			return 0;
			break;
		}

	} while (true);

	system("pause");
}

char MainMenu(void) {

	char opcao;

	system("cls");
	printf("Chora no cavaco maluco vendas autoesportivas\n\n");
	do {

		printf("1 - Cadastro dos produtos.\n");
		printf("2 - Menu de venda dos produtos.\n");
		printf("3 - Menu de entrega.\n");
		printf("4 - Sair do programa.\n");
		rewind(stdin);
		opcao = _getch();
		if (opcao >= '1' && opcao <= '4') {

			return opcao;

		} else {
			system("cls");
			printf("Chora no cavaco maluco vendas autoesportivas\n\n");
			printf("Selecione uma opção valida\n");
		}

	} while (true);
}

char  MenuProduto(void) {

	char opcao;
	system("cls");
	printf("Menu\n\n");
	do {
		printf("1 - Novo item\n");
		printf("2 - Remove item\n");
		printf("3 - Edita item\n");
		printf("4 - Busca item\n");
		printf("5 - Lista itens\n");
		printf("6 - Sair\n");
		rewind(stdin);
		opcao = _getch();
		if (opcao >= '1' && opcao <= '6') {
			return opcao;
		} else {
			system("cls");
			printf("Menu\n\n");
			printf("Valor inválido\n");
		}

	} while (true);
}

int cadastraP() {
	LISTA * reg = NULL;

	criaL(&reg);
	carrega_arq(reg);
	do {
		switch (MenuProduto()) {
			case '1':
			cadastra(reg);
			break;
			case '2':
			remove(reg);
			break;
			case '3':
			edita(reg);
			break;
			case '4':
			busca(reg);
			break;
			case '5':
			lista(reg);
			break;
			case '6':
			salva_arq(reg);
			return 0;
			break;
		}
		printf("\n\n");
		_getch();
	} while (true);
}

int cadastra(LISTA * temp) {
	produtos aux;
	leitura(&aux);
	insereFimL(temp,aux);
	printf("Item cadastrado\n");
	return 0;
}

int leitura(produtos * aux) {
	int erro;
	do {
		printf("Digite nome do Prod: ");
		rewind(stdin);
		fgets(aux->modelo,20,stdin);
	} while (aux->modelo[0] == '\0');

	do {
		printf("Digite quantidade: ");
		rewind(stdin);
		erro = scanf_s("%d",&aux->quant);
	} while (erro == 0);

	do {
		printf("Digite cor do Prod: ");
		rewind(stdin);
		fgets(aux->cor,20,stdin);
	} while (aux->cor[0] == '\0');

	do {
		printf("Digite o ano: ");
		rewind(stdin);
		erro = scanf_s("%i",&aux->ano);
	} while (erro == 0);
	do {
		printf("Digite o preco: ");
		rewind(stdin);
		erro = scanf_s("%f",&aux->valor);
	} while (erro == 0);
	return 1;
}

int carrega_arq(LISTA * temp) {
	unsigned int tam;
	FILE * arq;
	fopen_s(&arq,"Save.bob","r");
	if (arq == NULL) {
		system("cls");
		printf("Nenhum arquivo encontrado\n");
		printf("\n\nAperte ENTER\n");
		_getch();
		return 0;
	} else {
		fscanf_s(arq,"%u",&tam);
		produtos aux;
		for (unsigned int i = 0; i < tam; i++) {
			char lixo[30],a;
			fscanf_s(arq,"%s",lixo,30);
			a = fgetc(arq);
			fgets(aux.modelo,20,arq);
			fscanf_s(arq,"%d",&aux.quant);
			a = fgetc(arq);
			fscanf_s(arq,"%f",&aux.valor);
			a = fgetc(arq);
			insereFimL(temp,aux);
		}
		printf("Carregando arquivo ");
		for (int i = 0; i < 20; i++) {
			printf("*");
			Sleep(100);
		}
		printf("\n");
		fclose(arq);
		return 1;
	}
}

int edita(LISTA * temp) {
	if (!vaziaL(temp)) {
		char busca[20],item[20];
		char np = '0',op;
		int quant = tamanhoL(temp);

		printf("Digite nome do Prod para busca: ");
		scanf_s("%s",busca,20);
		_strupr_s(busca,20);
		for (int i = 1; i <= quant; i++) {
			produtos aux;
			consultaL(temp,&aux,i);
			strcpy_s(item,aux.modelo);
			_strupr_s(item,20);
			if (strstr(item,busca) != NULL) {
				np = '1';
				do {
					printf("%d - %s",i + 1,aux.modelo);
					printf("Q: %d - R$%.2f\n",aux.quant,aux.valor);

					printf("Deseja alterar esse registro? \nS-Sim \nN-Não\n");
					op = _getch();
					if (op == 'S' || op == 's') {
						removePosL(temp,&aux,i);
						leitura(&aux);
						inserePosL(temp,aux,i);
						return 1;
					}
				} while (!(op == 'N' || op == 'n'));
			}
		}
		if (np == '0') {
			printf("Nenhum registro encontrado\n");
			return 0;
		}
	} else {
		printf("Não há cadastros\n");
		return 0;
	}
	return 1;
}

int busca(LISTA * temp) {
	if (!vaziaL(temp)) {
		char busca[20],item[20];
		char np = '0';
		int quant = tamanhoL(temp);

		printf("Digite nome do Prod para busca: ");
		scanf_s("%s",busca,20);
		_strupr_s(busca,20);
		for (int i = 1; i <= quant; i++) {
			produtos aux;
			consultaL(temp,&aux,i);
			strcpy_s(item,aux.modelo);
			_strupr_s(item,20);
			if (strstr(item,busca) != NULL) {
				np = '1';
				printf("%d - %s",i,aux.modelo);
				printf("Q: %d - R$%.2f\n",aux.quant,aux.valor);
			}
		}
		if (np == '0') {
			printf("Nenhum registro encontrado\n");
			return 0;
		}
	} else {
		printf("Não há cadastros\n");
		return 0;
	}
	return 1;
}

int salva_arq(LISTA * temp) {
	FILE * arq;
	fopen_s(&arq,"Save.bob","w");

	if (arq == NULL) {
		printf("Nem salvou\n");
		return 0;
	} else {
		int quant = tamanhoL(temp);
		fprintf(arq,"%u",quant);
		produtos aux;
		for (int i = 0; i < quant; i++) {
			removeInicioL(temp,&aux);
			fprintf(arq,"Nome: %s%d\n%f\n",aux.modelo,aux.quant,aux.cor,aux.ano,aux.valor);
		}
		fclose(arq);
		liberaL(temp);
		printf("Salvando arquivo ");
		for (int i = 0; i < 20; i++) {
			printf("*");
			Sleep(100);
		}
		printf("\n");
		return 1;
	}
}

int lista(LISTA * temp) {
	system("cls");
	if (vaziaL(temp)) {
		printf("\tNenhum item cadastrado \n");
		return 0;
	} else {
		produtos aux;
		printf("\tLista de Cadastros \n");
		for (int i = 1; i <= tamanhoL(temp); i++) {
			consultaL(temp,&aux,i);
			printf("%d - %s",i,aux.modelo);
		}
		return 1;
	}
}

int remove(LISTA * temp) {
	if (!vaziaL(temp)) {
		char busca[20],item[20];
		char np = '0',op;
		int quant = tamanhoL(temp);

		printf("Digite nome do Prod para busca: ");
		scanf_s("%s",busca,20);
		_strupr_s(busca,20);
		for (int i = 1; i <= quant; i++) {
			produtos aux;
			consultaL(temp,&aux,i);
			strcpy_s(item,aux.modelo);
			_strupr_s(item,20);
			if (strstr(item,busca) != NULL) {
				np = '1';
				do {
					printf("%d - %s",i + 1,aux.modelo);
					printf("Q: %d - R$%.2f\n",aux.quant,aux.valor);

					printf("Deseja alterar esse registro? \nS-Sim \nN-Não\n");
					op = _getch();
					if (op == 'S' || op == 's') {
						removePosL(temp,&aux,i);
						return 1;
					}
				} while (!(op == 'N' || op == 'n'));
			}
		}
		if (np == '0') {
			printf("Nenhum registro encontrado\n");
			return 0;
		}
	} else {
		printf("Não há cadastros\n");
		return 0;
	}
	return 1;
}