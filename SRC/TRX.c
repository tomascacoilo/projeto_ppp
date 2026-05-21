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

//____________________________LISTA_E_AS_SUAS_FUNÇÕES________________________________

node_trans* create(){
    node_trans* aux;
    trans trx = {0, NULL, {0,0,0}};
    aux = (node_trans*) malloc(sizeof(node_trans));
    if(aux != NULL){
        aux->trx = trx;
        aux->next=NULL;
    }

    return aux;
}

int check_empty (node_trans* list_trx) { 
    return list_trx->next == NULL; //1 se tiver vazia, 0 se não tiver
}

node_trans* clean(node_trans* list_trx) {
    while (list_trx != NULL) {
        node_trans* temp_ptr = list_trx;
        list_trx = list_trx->next;

        if (temp_ptr->trx.info != NULL) { //liberta tbm a memoria da string trx.info
                free(temp_ptr->trx.info);
            }
        
        free(temp_ptr);
    }
  return NULL;
}

void efetuar_despesa(node_trans* lista, int valor, char* info, data dt){
    if (lista==NULL) return;

    node_trans* novo = (node_trans*) malloc(sizeof(node_trans));
    if (novo == NULL) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    novo->trx.valor = valor;
    novo->trx.info = (char*) malloc(strlen(info) + 1); // strlen lê td à exceçãp do \0 ----- +1 para incluir o \0
    strcpy(novo->trx.info, info);
    novo->trx.date = dt;

    node_trans* atual = lista; // = ao header

    
    while (atual->next != NULL && data_maior(dt, atual->next->trx.date)) {
        atual = atual->next; //avança de um em um
    }

    
    novo->next = atual->next;
    atual->next = novo;
}


// NOTA: CADA ALUNO DEVERÁ TER UMA LISTA PROPRIA COM AS SUAS DESPESAS