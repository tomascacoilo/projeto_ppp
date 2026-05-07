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