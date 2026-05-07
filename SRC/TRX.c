#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATA.h"

typedef struct {
    int valor;
    char* info;
    data date;
} trans;

typedef struct noTrans {
    trans trx;
    struct noTrans* next;
} node_trans;

void efetuar_despesa(node_trans** lista, int valor, char* info, data dt){

    node_trans* novo = (node_trans*) malloc(sizeof(node_trans));
    if (novo == NULL) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    novo->trx.valor = valor;

    novo->trx.info = (char*) malloc(strlen(info) + 1); // strlen lê td à exceçãp do \0 ----- +1 para incluir o \0
    strcpy(novo->trx.info, info);
    
    novo->trx.date = dt;

}


// NOTA: CADA ALUNO DEVERÁ TER UMA LISTA PROPRIA COM AS SUAS DESPESAS