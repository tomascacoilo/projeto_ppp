#ifndef user_h
#define user_h
#include "DATA.h"
#include "TRX.h"

typedef struct {
    char* nome;
    data nasc;
    int curso;
    int ano;
    int numero;
    float saldo;
    //acrescentar lista despesas
}person;


typedef struct noLista{  //criar o no
    person pessoaLista;
    struct noLista* prox;
}noLista;

typedef noLista* pLista; 


int valida_pessoa(person* pessoa);
pLista cria();
int vazia(pLista lista);
void insere(pLista lista, person p1);
pLista destroi(pLista lista);
void procura(pLista lista, int chave,pLista *ant,pLista *atual);
void elimina(pLista lista, int chave);
void carrega(float valor,pLista lista,int chave);


#endif
