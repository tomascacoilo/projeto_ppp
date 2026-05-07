#ifndef DATA_H
#define DATA_H

typedef struct data_estrutura{
    int dia;
    int mes;
    int ano;
} data;

int valida_data(data* d);

#endif