#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATA.h"
#include "TRX.h"
#include "user.h"  
#include <string.h>
#define MAX 100

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