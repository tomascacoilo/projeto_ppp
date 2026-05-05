#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* nome;
    data nasc;
    char* curso;
    int ano;
    int numero;
    float saldo;
}person;


int valida(person pessoa){
    if(pessoa.nasc.ano >= pessoa.ano  || pessoa.numero <0  || pessoa.saldo<0) return 0;
        
  
    
}