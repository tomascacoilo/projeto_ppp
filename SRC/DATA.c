#include <stdio.h>
#include <stdlib.h>

typedef struct data_estrutura{
    int dia;
    int mes;
    int ano;
} data;

int valida_data(data* d){
    if( d->dia<0 || d->dia>31){ // verifica dia
        return 0;
    }

    if (d->mes<0 || d->mes>12){ // verifica dia
        return 0;
    }

    if (d->ano>2026){ // verifica dia
        return 0;
    } 

    if (d->mes == 2){ // verifica feveiro (dia<29)
        if(d->dia > 29) return 0;
    }

    return 1;
}