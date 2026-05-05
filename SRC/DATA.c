#include <stdio.h>
#include <stdlib.h>

typedef struct data_estrutura{
    int dia;
    int mes;
    int ano;
} data;

int valida_data(data data){
    if( data.dia<0 || data.dia>31){
        return 0;
    }

    if (data.mes<0 || data.mes>12){
        return 0;
    }

    if (data.ano>2026){
        return 0;
    } 

    if (data.mes == 2){
        if(data.dia > 29) return 0;
    }

    return 1
}