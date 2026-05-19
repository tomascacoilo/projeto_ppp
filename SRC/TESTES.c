#include <stdio.h>
#include "TRX.h" // Substitui pelo nome correto do teu ficheiro .h de transações

// Função auxiliar apenas para nos ajudar a ver o resultado do teste
void imprimir_teste(node_trans* lista) {
    if (check_empty(lista)) {
        printf("A lista esta vazia!\n");
        return;
    }

    // Saltamos o header para começar nos dados reais
    node_trans* atual = lista->next;
    while (atual != NULL) {
        printf("[%02d/%02d/%d] %-15s : %d€\n", 
               atual->trx.date.dia, atual->trx.date.mes, atual->trx.date.ano,
               atual->trx.info, atual->trx.valor);
        atual = atual->next;
    }
}

int main() {
    printf("--- INICIO DOS TESTES ---\n");

    // 1. Testar a criação da lista (Nó Sentinela)
    node_trans* minha_lista = create();
    if (minha_lista == NULL) {
        printf("Erro ao criar a lista.\n");
        return 1;
    }

    // 2. Testar se a lista inicia vazia
    if (check_empty(minha_lista)) {
        printf("Sucesso: A lista foi criada e esta vazia.\n");
    }

    printf("\n--- Inserindo Despesas (Desordenadas no código) ---\n");
    
    // Criar algumas datas de teste
    data d_natal = {25, 12, 2024};
    data d_pascoa = {31, 3, 2024};
    data d_ano_novo = {1, 1, 2025};
    data d_aniversario = {15, 6, 2024};

    // Inserir em ordem aleatória para testar a ordenação por data
    efetuar_despesa(minha_lista, 50, "Prenda Natal", d_natal);
    efetuar_despesa(minha_lista, 15, "Ovo Pascoa", d_pascoa);
    efetuar_despesa(minha_lista, 120, "Festa Ano Novo", d_ano_novo);
    efetuar_despesa(minha_lista, 30, "Jantar Aniv", d_aniversario);

    // 3. Imprimir para verificar se o "while" ordenou bem
    // O resultado esperado deve ser: Páscoa -> Aniversário -> Natal -> Ano Novo
    imprimir_teste(minha_lista);

    // 4. Testar a limpeza da lista (clean)
    printf("\n--- A limpar a lista e libertar memoria ---\n");
    minha_lista = clean(minha_lista);

    // 5. Verificar se ficou tudo a NULL
    if (minha_lista == NULL) {
        printf("Sucesso: Toda a memoria foi libertada e o ponteiro ficou a NULL.\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");
    return 0;
}