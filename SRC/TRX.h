#ifndef TRX_H
#define TRX_H
#include "DATA.h"

typedef struct {
    float valor;
    char* info;
    data date;
} trans;
typedef struct noTrans {
    trans trx;
    struct noTrans* next;
} node_trans;


node_trans* create();
int check_empty (node_trans* list_trx);
node_trans* clean(node_trans* list_trx);
void efetuar_despesa(node_trans* lista, int valor, char* info, data dt);

#endif