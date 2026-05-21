#include <stdio.h>
#include <stdlib.h>
#include "DATA.h"
#include "TRX.h"


typedef struct {
    char* nome;
    data nasc;
    int curso;
    int ano;
    int numero;
    float saldo;
    node_trans* despesas;
}person;


int valida_pessoa(person* pessoa){
    if(pessoa->nasc.ano >= pessoa->ano){  //valida se a pessoa está na universidade antes de nascer
        return 0;
    } 

    if(pessoa->numero <0){  //verifica que não existem números negativos
        return 0;
    }  

    if(pessoa->saldo<0) { //verifica que o saldo não é um número negativo
        return 0;
    }

    if(pessoa->curso <1 || pessoa->curso>5){  //vê se o "curso" inserido está válido
        return 0;
    }

    return 1;  
}


typedef struct noLista{  //criar o no
    person pessoaLista;
    struct noLista* prox;
}noLista;

typedef noLista* pLista; 

//criar a lista

pLista cria(){
    pLista aux;   //vai ser um ponteiro para um nó
    person p1={NULL,{0,0,0},0,0,0,0.0,NULL}; //header
    aux=(pLista)malloc(sizeof(noLista));
    if(aux!= NULL){
        aux->pessoaLista=p1;
        aux->prox=NULL;
    }

    return aux;
}

// ver se a lista está vazia
int vazia(pLista lista){
    if(lista->prox==NULL){
        return 1;
    }
    return 0;
}

//procurar um elemento
void procura(pLista lista, int chave,pLista *ant,pLista *atual){ //procuramos pelo numero do estudante, ou seja, chave é um número
    *ant=lista;  //aponta para um no
    *atual=lista->prox;  //e este aponta para o próximo 
    while((*atual)!=NULL && (*atual)->pessoaLista.numero< chave){
        *ant=*atual;
        *atual=(*atual)->prox;
    }
    if((*atual)!=NULL && (*atual)->pessoaLista.numero !=chave){
        *atual=NULL; //se não encontrarmos o elemento 
    }
}

//inserir um novo aluno
void insere(pLista lista, person p1){
    pLista no,ant,inutil;
    no=(pLista)malloc(sizeof(noLista));
    if(no!=NULL){
        no->pessoaLista=p1;
        procura(lista,p1.numero,&ant,&inutil);
        if (p1.despesas == NULL) {
            no->pessoaLista.despesas = create();
        }
        no->prox=ant->prox;
        ant->prox=no;
    } 
}


//destruir a lista
pLista destroi(pLista lista){
    pLista temp_str;
    
    while (lista != NULL){
        temp_str = lista; //ponteiro temporário para um nó da lista
        lista=lista->prox;

        if (temp_str->pessoaLista.despesas != NULL) {
            clean(temp_str->pessoaLista.despesas);
        }

        if (temp_str->pessoaLista.nome != NULL) {
            free(temp_str->pessoaLista.nome);
        }

        free(temp_str);
    }

    return NULL;
}



//eliminar um elemento 
void elimina(pLista lista, int chave){
    pLista ant,atual; //vao ser um ponteiro para um nó
    procura(lista,chave,&ant,&atual);
    if(atual != NULL){
        ant->prox=atual->prox;
        free(atual->pessoaLista.nome);
        free(atual);
    }
}


void carrega(float valor,pLista lista,int chave){
    pLista ant,atual;  //ponteiros para nos 
    if (valor <0){
        return 0;
    }
    
    procura(lista,chave,&ant,&atual); //atual aponta para a pessoa que queremos 
    if (atual != NULL){
        atual->pessoaLista.saldo+=valor;
    }
    else {
        printf("Erro: Chave %d não encontrada na lista.\n", chave);
    }
}

int valida_nome(char* nome) {
    if (nome == NULL || strlen(nome) == 0) {
        return 0; 
    }

    int estado = 0;

    for (int i = 0; nome[i] != '\0'; i++) {
        char c = nome[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            estado = 1;
        } else if (c == ' ' || c == '\n' || c == '\t') {
            continue; //ignora espaços
        } else {
            return 0;
        }
    }
    return estado;
}