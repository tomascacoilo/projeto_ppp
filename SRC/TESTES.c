#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATA.h"
#include "TRX.h"

// Redefinição da struct person com a tua lista integrada para o teste compilar
typedef struct {
    char* nome;
    data nasc;
    int curso;
    int ano;
    int numero;
    float saldo;
    node_trans* despesas; // A tua lista de despesas integrada aqui!
} person;

// Declaração dos tipos da lista de alunos para o compilador conhecer no main
typedef struct noLista {
    person pessoaLista;
    struct noLista* prox;
} noLista;

typedef noLista* pLista;

// Declaração das funções do teu colega (para o GCC saber que existem)
pLista cria();
int vazia(pLista lista);
void procura(pLista lista, int chave, pLista *ant, pLista *atual);
void insere(pLista lista, person p1);
pLista destroi(pLista lista);
pLista elimina(pLista lista, int chave);
void carrega(float valor, pLista lista, int chave);
int valida_pessoa(person* pessoa);

// --- FUNÇÕES AUXILIARES APENAS PARA O TESTE ---

// Função para criar um aluno dinamicamente sem encher o main de linhas
person criar_aluno_aux(char* nome, int dia, int mes, int ano_nasc, int curso, int ano_univ, int numero, float saldo) {
    person p;
    p.nome = (char*)malloc(strlen(nome) + 1);
    strcpy(p.nome, nome);
    p.nasc.dia = dia; p.nasc.mes = mes; p.nasc.ano = ano_nasc;
    p.curso = curso;
    p.ano = ano_univ;
    p.numero = numero;
    p.saldo = saldo;
    p.despesas = NULL; // O "insere" vai inicializar isto com o create()
    return p;
}

// Função para mostrar no ecrã o estado atual dos alunos
void imprime_sistema(pLista lista) {
    if (vazia(lista)) {
        printf("Lista de alunos vazia.\n");
        return;
    }
    pLista aux = lista->prox; // Salta o header
    while (aux != NULL) {
        printf("ID: %d | Nome: %-8s | Saldo: %.2f€\n", 
               aux->pessoaLista.numero, aux->pessoaLista.nome, aux->pessoaLista.saldo);
        aux = aux->prox;
    }
}

// --- MAIN (O CORAÇÃO DO TESTE) ---
int main() {
    printf("=== INICIO DOS TESTES GERAIS (ALUNOS + DESPESAS) ===\n\n");

    // 1. Criar a lista principal de alunos
    pLista lista_alunos = cria();
    printf("Sistema inicializado. Lista vazia? %s\n\n", vazia(lista_alunos) ? "SIM" : "NAO");

    // 2. Criar dados de teste (Repara que os números de estudante estão desordenados)
    person t_marcos = criar_aluno_aux("Marcos", 20, 8, 2004, 2, 2023, 2023010, 10.00); // Num maior
    person t_tomas  = criar_aluno_aux("Tomas", 15, 4, 2005, 3, 2024, 2024005, 30.00);  // Num menor

    // 3. Testar a validação do teu colega
    printf("--- Testando Validacao ---\n");
    printf("Validacao do Tomas: %s\n\n", valida_pessoa(&t_tomas) ? "VALIDO" : "INVALIDO");

    // 4. Inserir os alunos (A lista deve ordenar por número automaticamente)
    printf("--- A Inserir Alunos (Marcos primeiro no codigo, Tomas em segundo) ---\n");
    insere(lista_alunos, t_marcos);
    insere(lista_alunos, t_tomas);
    imprime_sistema(lista_alunos); // O Tomas deve aparecer antes do Marcos se a ordenação funcionar!

    // 5. Testar a função Carrega Saldo
    printf("\n--- Testando Carregamento de Saldo (Adicionar 15.50€ ao Tomas) ---\n");
    carrega(15.50, lista_alunos, 2024005);
    imprime_sistema(lista_alunos);

    // 6. O GRANDE TESTE: Ligar o Aluno às tuas despesas!
    printf("\n--- Testando Ligacao com o teu Modulo de Transacoes ---\n");
    pLista ant, atual;
    procura(lista_alunos, 2024005, &ant, &atual); // Procuramos o Tomás no sistema
    
    if (atual != NULL) {
        data d_hoje = {19, 5, 2026};
        
        // Se no teu "insere" fizeste -> no->pessoaLista.despesas = create();
        // Podemos usar diretamente a tua função efetuar_despesa aqui:
        if (atual->pessoaLista.despesas != NULL) {
            efetuar_despesa(atual->pessoaLista.despesas, 4.50, "Almoco de Teste", d_hoje);
            printf("Sucesso: Despesa de 4.50€ registada internamente para o aluno %s!\n", atual->pessoaLista.nome);
        } else {
            printf("Nota: A lista de despesas do aluno nao estava inicializada.\n");
        }
    }

    // 7. Testar a Eliminação de um elemento
    printf("\n--- Testando Eliminacao (Remover o Marcos do sistema) ---\n");
    elimina(lista_alunos, 2023010);
    imprime_sistema(lista_alunos);

    // 8. Limpar absolutamente tudo da memória (O vosso Destroi Corrigido!)
    printf("\n--- A Destruir a lista completa e a libertar a RAM ---\n");
    lista_alunos = destroi(lista_alunos);
    
    if (lista_alunos == NULL) {
        printf("Sucesso: Sistema totalmente limpo. Memorias libertadas!\n");
    }

    printf("\n=== FIM DOS TESTES ===\n");
    return 0;
}