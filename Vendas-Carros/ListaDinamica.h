#pragma once

#ifndef LISTDIN_H
#define LISTDIN_H

typedef struct produto tipo;
typedef struct Lista LISTA;


int criaL(LISTA ** temp);
int liberaL(LISTA *temp);
int tamanhoL(LISTA *temp);
int vaziaL(LISTA *temp);
int cheiaL(LISTA *temp);
int insereInicioL(LISTA *temp,tipo dado);
int insereFimL(LISTA *temp,tipo dado);
int inserePosL(LISTA *temp,tipo dado,int pos);
int removeInicioL(LISTA *temp,tipo *dado);
int removeFimL(LISTA *temp,tipo *dado);
int removePosL(LISTA *temp,tipo *dado,int pos);
int consultaL(LISTA *temp,tipo *dado,int pos);


#endif