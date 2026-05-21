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

void carregar_dados(pLista lista, const char* nome_ficheiro) {

    FILE* fp = fopen(nome_ficheiro, "r");
    if (fp == NULL) {
        return;
    } else {
        char linha[256];

        while(fgets(linha, sizeof(linha), fp)){
            char nome_tmp[100];
            person p;


            fscanf(fp, "%[^;];%d;%d;%d;%d;%d;%d;%f", nome_tmp, &p.nasc, &p.curso, &p.ano, &p.numero, &p.saldo);
            p.nome = (char*) malloc(strlen(nome_tmp)+1);
            p.despesas = NULL;

            insere(lista, p);
        }
        fclose(fp);
    }

    FILE* fd = fopen(nome_ficheiro, "r");
    if (fd == NULL) {
        return;
    } else {
        char linha[256];

        while(fgets(linha, sizeof(linha), fd)){
            char info_tmp[100];
            int num_aluno;
            float saldo;
            data d;


            fscanf(fd, "%d;%f;%[^;];%d;%d;%d", &num_aluno, &saldo, &info_tmp, &d.dia, &d.mes, &d.ano);
            
            pLista ant;
            pLista atual;
            procura(lista, num_aluno, &ant, &atual);
            //devolve atual=NULL caso não encontre o aluno

            //caso encontre o aluno, coloca a despesa na sua lista de despesas;
            if (atual != NULL && atual->pessoaLista.despesas != NULL) {
                efetuar_despesa(atual->pessoaLista.despesas, saldo, info_tmp, d);
            }
        }
        fclose(fp);
    }
}