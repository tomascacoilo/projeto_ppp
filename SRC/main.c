#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATA.h"
#include "TRX.h"
#include "user.h"
#define MAX 100

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
                fprintf(fd, "%d;%.2f;%s;%d;%d;%d\n", p.numero, atual_d->trx.valor, atual_d->trx.info, atual_d->trx.date.dia, atual_d->trx.date.mes, atual_d->trx.date.ano);
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


void ui_corre(pLista lista) {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n1) Inserir aluno\n2) Eliminar aluno\n3) Listar alunos\n4) Registar despesa\n5) Carregar saldo\n0) Sair\n> ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n') {
            }
            continue;
        }

        if (opcao == 1) { //inserir aluno

            person p;

            char temp_nome[MAX];
            int x;
            int loop = 1;
            while (loop){
                printf("Nome: \n");
                fgets(temp_nome,MAX,stdin);
                x=valida_nome(temp_nome);
                if(x==0){
                    printf("Nome inválido.");
                } else {
                    loop=0;
                }
                
            }
            //remover o /n do nome
            for (int i = 0; temp_nome[i] != '\0'; i++) {
                if (temp_nome[i] == '\n') {
                temp_nome[i] = '\0';
                break;
                }
            }

            p.nome=malloc(strlen(temp_nome)+1); // +1 para o /0
            //nao esquecer de dar free
            strcpy(p.nome,temp_nome);
            
            
            //data de nascimento
            data temp_data;
            loop = 1; 

            while(loop){
               
                printf("Ano de nascimento: \n");
                scanf("%d",&temp_data.ano);

                printf("Mes de nascimento: \n");
                scanf("%d",&temp_data.mes);

                printf("Dia de nascimento: \n");
                scanf("%d",&temp_data.dia);

                if(valida_data(&temp_data)==0){
                    printf("Data inválida.  \n");
                } else {
                    loop=0;
                }
                 
            }
            p.nasc = temp_data;

            //curso

            int temp_curso;
            loop = 1; 

            while(loop){
                printf("\n1) Engenharia Informática\n2) Design e Multimedia\n3) Ciencia de Dados\n> ");
    
                
                if (scanf("%d", &temp_curso) != 1) {
                    printf("Por favor, insira um número válido.\n");
                    
                    while (getchar() != '\n'); 
                    continue;
                }

                if(temp_curso < 1 || temp_curso > 3){
                    printf("Curso inválido. Tente novamente.\n");
                } else {
                    p.curso = temp_curso; 
                    loop = 0; // Sai do ciclo
                }
            }

            insere(lista, p);

            //verificar ano

            int temp_ano;
            loop=1;

            while(loop){
                printf("Ano:  \n");
                scanf("%d",&temp_ano);
                if(temp_ano>=1  && temp_ano<=3){ 
                    p.ano=temp_ano;
                    loop=0;
                }
                else{
                    printf("Ano inválido. Tente novamente.  \n");
                }
            }
            
        } else if (opcao == 2) {
            void elimina( lista,  chave);

        } else if (opcao == 3) {
            printf("Ainda não implementado: ui_opcao_listar_alunos\n");
        } else if (opcao == 4) {
            printf("Ainda não implementado: ui_opcao_registar_despesa\n");
        } else if (opcao == 5) {
            printf("Ainda não implementado: ui_opcao_carregar_saldo\n");
        }
    }
}