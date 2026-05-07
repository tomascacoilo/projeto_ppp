#include <stdio.h>
#include <stdlib.h>
#include "DATA.h"


typedef struct {
    char* nome;
    data nasc;
    int curso;
    int ano;
    int numero;
    float saldo;
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
    pLista aux;   //vai ser um ponteiro para um nó´
    person p1={"",{0,0,0},0,0,0,0.0}; //header
    aux=(pLista)malloc(sizeof(noLista));
    if(aux!= NULL){
        aux->pessoaLista=p1;
        aux->prox=NULL;
    }

    return aux;
}

// ver se a lista está vazia
//...

//eliminar um elemento 
pLista elimina(){
    pLista temp_ptr;
}