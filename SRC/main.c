#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATA.h"
#include "TRX.h"
#include "user.h"

void guardar_dados_separados(pLista lista, const char* f_alunos, const char* f_despesas) {
    FILE* fp = fopen(f_alunos, "w");
    FILE* fd = fopen(f_despesas, "w");
    
    if (fp == NULL || fd == NULL) {
        if (fp) fclose(fp);
        if (fd) fclose(fd);
        return;
    }
    
    pLista tmp = lista->prox; // Passa do header para o 1.º aluno
    while (tmp != NULL) {
        person p = tmp->pessoaLista;
        
        //guarda o aluno no ficheiro de alunos (separando tudo por ;)
        fprintf(fp, "%s;%d;%d;%d;%d;%d;%d;%.2f\n", p.nome, p.nasc.dia, p.nasc.mes, p.nasc.ano, p.curso, p.ano, p.numero, p.saldo);
        
        // Se o aluno tiver despesas, guarda-as no ficheiro de despesas
        if (p.despesas != NULL) {
            node_trans* atual_d = p.despesas->next; // Salta o nó sentinela da despesa
            while (atual_d != NULL) {
                //Guardamos o NUMERO do estudante no inicio da linha da despesa para servir de ligação
                fprintf(fd, "%d;%.2f;%s;%d;%d;%d\n", p.numero, 
                        atual_d->trx.valor, 
                        atual_d->trx.info, 
                        atual_d->trx.date.dia, 
                        atual_d->trx.date.mes, 
                        atual_d->trx.date.ano);
                atual_d = atual_d->next;
            }
        }
        tmp = tmp->prox;
    }
    
    fclose(fp);
    fclose(fd);
}

void carregar_dados(pLista lista, const char* f_alunos, const char* f_despesas) {
    FILE* fp = fopen(f_alunos, "r");

    if (fp == NULL) {
        return;
    } else {
        char nome_tmp[100];
        person p;

        while(fscanf(fp, "%[^;];%d;%d;%d;%d;%d;%d;%f\n", nome_tmp, &p.nasc.dia, &p.nasc.mes, &p.nasc.ano, &p.curso, &p.ano, &p.numero, &p.saldo) == 8){

            p.nome = (char*) malloc(strlen(nome_tmp)+1);
            strcpy(p.nome, nome_tmp);
            p.despesas = create();

            insere(lista, p);
        }
        fclose(fp);
    }

    FILE* fd = fopen(f_despesas, "r");
    if (fd == NULL) {
        return;
    } else {
        char info_tmp[100];
        int num_aluno;
        float valor_d;
        data d;

        while(fscanf(fd, "%d;%f;%[^;];%d;%d;%d\n", &num_aluno, &valor_d, info_tmp, &d.dia, &d.mes, &d.ano) == 6){
            
            pLista ant;
            pLista atual;
            procura(lista, num_aluno, &ant, &atual);
            //devolve atual=NULL caso não encontre o aluno

            //caso encontre o aluno, coloca a despesa na sua lista de despesas;
            if (atual != NULL && atual->pessoaLista.despesas != NULL) {
                efetuar_despesa(atual->pessoaLista.despesas, valor_d, info_tmp, d);
            }
        }
        fclose(fd);
    }
}