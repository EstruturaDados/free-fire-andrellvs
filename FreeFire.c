#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. Definição das Structs ---

// Struct Item: Dados base do objeto (comum às duas estruturas).
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct No: Estrutura para a Lista Encadeada.
typedef struct No {
    Item dados;               // Armazena a struct Item
    struct No *proximo;       // Ponteiro para o próximo nó da lista
} No;

// --- 2. Variáveis Globais para o Inventário e Contadores ---

// Vetor (Lista Sequencial)
#define MAX_ITENS 10
Item inventarioVetor[MAX_ITENS];
int totalItensVetor = 0;

// Lista Encadeada (Estrutura Dinâmica)
No *listaCabeca = NULL; // Ponteiro para o início da lista
int totalItensLista = 0;

// Contadores de Comparações (Requisito 6)
long long comparacoesSequencial = 0;
long long comparacoesBinaria = 0;

// ----------------------------------------------------------------------------------
//                             PROTÓTIPOS DAS FUNÇÕES
// ----------------------------------------------------------------------------------

// Menu Principal
void exibirMenuPrincipal();
void menuVetor();
void menuLista();
void realizarBusca(int tipoEstrutura);

// Funções do Vetor
void inserirItemVetor(Item novoItem);
void removerItemVetor(const char *nomeRemover);
void listarItensVetor();
int buscarSequencialVetor(const char *nomeBusca);
void ordenarVetor();
int buscarBinariaVetor(const char *nomeBusca);

// Funções da Lista Encadeada
void inserirItemLista(Item novoItem);
void removerItemLista(const char *nomeRemover);
void listarItensLista();
int buscarSequencialLista(const char *nomeBusca);
void limparLista();

// ----------------------------------------------------------------------------------
//                             FUNÇÃO PRINCIPAL (MAIN)
// ----------------------------------------------------------------------------------

int main() {
    int opcaoPrincipal;

    printf("🎮 Sistema de Inventário - Desafio Aventureiro (Comparação de Estruturas) ⚔️\n");

    do {
        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcaoPrincipal) != 1) {
            printf("\n⚠️ Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n');
            opcaoPrincipal = -1;
        } else {
            switch (opcaoPrincipal) {
                case 1:
                    menuVetor();
                    break;
                case 2:
                    menuLista();
                    break;
                case 3:
                    realizarBusca(1); // Busca no Vetor
                    break;
                case 4:
                    realizarBusca(2); // Busca na Lista
                    break;
                case 0:
                    limparLista(); // Libera a memória alocada dinamicamente.
                    printf("\n👋 Sistema encerrado. Memória liberada.\n");
                    break;
                default:
                    printf("\n⚠️ Opção inválida. Escolha um número entre 0 e 4.\n");
            }
        }
    } while (opcaoPrincipal != 0);

    return 0;
}

// ----------------------------------------------------------------------------------
//                                FUNÇÕES GERAIS DE MENU
// ----------------------------------------------------------------------------------

/**
 * @brief Exibe o menu principal para seleção da estrutura de dados ou busca.
 */
void exibirMenuPrincipal() {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Gerenciar Mochila (Vetor)\n");
    printf("2. Gerenciar Mochila (Lista Encadeada)\n");
    printf("3. Realizar Buscas (Apenas Vetor)\n");
    printf("4. Realizar Buscas (Apenas Lista)\n");
    printf("0. Sair\n");
    printf("------------------------\n");
}

/**
 * @brief Cria e retorna um novo item lido do usuário.
 * @return Struct Item preenchida.
 */
Item criarNovoItem() {
    Item novoItem;
    printf("\n➡️ Digite os dados do Item:\n");
    printf("Nome (max 29): ");
    scanf("%s", novoItem.nome);
    printf("Tipo (ex: arma, cura, municao): ");
    scanf("%s", novoItem.tipo);
    printf("Quantidade: ");
    while (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("⚠️ Quantidade inválida. Digite um número inteiro positivo: ");
        while (getchar() != '\n');
    }
    return novoItem;
}

/**
 * @brief Menu de operações para o Vetor.
 */
void menuVetor() {
    int op;
    do {
        printf("\n--- MOCHILA VETOR (Sequencial) ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Ordenar Itens (Bubble Sort por Nome)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &op) != 1) { op = -1; while (getchar() != '\n'); }

        char nome[30];
        switch (op) {
            case 1: inserirItemVetor(criarNovoItem()); break;
            case 2:
                printf("➡️ Digite o nome do item para remover: ");
                scanf("%s", nome);
                removerItemVetor(nome);
                break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("⚠️ Opção inválida.\n");
        }
    } while (op != 0);
}

/**
 * @brief Menu de operações para a Lista Encadeada.
 */
void menuLista() {
    int op;
    do {
        printf("\n--- MOCHILA LISTA (Encadeada) ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &op) != 1) { op = -1; while (getchar() != '\n'); }

        char nome[30];
        switch (op) {
            case 1: inserirItemLista(criarNovoItem()); break;
            case 2:
                printf("➡️ Digite o nome do item para remover: ");
                scanf("%s", nome);
                removerItemLista(nome);
                break;
            case 3: listarItensLista(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("⚠️ Opção inválida.\n");
        }
    } while (op != 0);
}

/**
 * @brief Menu e execução das buscas, com contagem de comparações.
 * @param tipoEstrutura 1 para Vetor, 2 para Lista.
 */
void realizarBusca(int tipoEstrutura) {
    char nomeBusca[30];
    int indice;

    printf("\n--- REALIZAR BUSCA (%s) ---\n", (tipoEstrutura == 1) ? "VETOR" : "LISTA ENCADEADA");
    printf("➡️ Digite o nome do item para buscar: ");
    scanf("%s", nomeBusca);
    
    comparacoesSequencial = 0;
    comparacoesBinaria = 0;

    if (tipoEstrutura == 1) { // Busca no Vetor (Sequencial e Binária)
        // Busca Sequencial
        indice = buscarSequencialVetor(nomeBusca);
        if (indice != -1) {
            printf("\n✅ Busca Sequencial: Item '%s' encontrado na posição %d.\n", nomeBusca, indice + 1);
        } else {
            printf("\n❌ Busca Sequencial: Item '%s' não encontrado.\n", nomeBusca);
        }
        printf("➡️ Comparações (Sequencial): %lld\n", comparacoesSequencial);
        
        // Busca Binária (Requer Ordenação)
        if (totalItensVetor > 0) {
            ordenarVetor(); // Garante a ordenação antes da Binária.
            indice = buscarBinariaVetor(nomeBusca);
             if (indice != -1) {
                printf("✅ Busca Binária: Item '%s' encontrado na posição %d.\n", nomeBusca, indice + 1);
            } else {
                printf("❌ Busca Binária: Item '%s' não encontrado.\n", nomeBusca);
            }
            printf("➡️ Comparações (Binária): %lld\n", comparacoesBinaria);
        } else {
             printf("\n--- Busca Binária NÃO REALIZADA (Vetor vazio) ---\n");
        }

    } else { // Busca na Lista Encadeada (Apenas Sequencial)
        indice = buscarSequencialLista(nomeBusca);
        if (indice != -1) {
            printf("\n✅ Busca Sequencial (Lista): Item '%s' encontrado (posição lógica %d).\n", nomeBusca, indice + 1);
        } else {
            printf("\n❌ Busca Sequencial (Lista): Item '%s' não encontrado.\n", nomeBusca);
        }
         printf("➡️ Comparações (Sequencial): %lld\n", comparacoesSequencial);
    }
}

// ----------------------------------------------------------------------------------
//                          FUNÇÕES DA MOCHILA (VETOR)
// ----------------------------------------------------------------------------------

/**
 * @brief Insere um item na primeira posição livre do vetor.
 */
void inserirItemVetor(Item novoItem) {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n🛑 Mochila Vetor cheia! Não é possível carregar mais itens.\n");
        return;
    }
    inventarioVetor[totalItensVetor] = novoItem;
    totalItensVetor++;
    printf("\n✅ Item '%s' adicionado ao Vetor.\n", novoItem.nome);
}

/**
 * @brief Remove um item por nome, deslocando os elementos subsequentes.
 */
void removerItemVetor(const char *nomeRemover) {
    int i = 0;
    // 1. Busca Sequencial para achar o índice.
    for (; i < totalItensVetor; i++) {
        if (strcmp(inventarioVetor[i].nome, nomeRemover) == 0) {
            break;
        }
    }

    if (i < totalItensVetor) {
        // 2. Remoção (Alto custo em vetor): Desloca todos os itens após o removido.
        for (int j = i; j < totalItensVetor - 1; j++) {
            inventarioVetor[j] = inventarioVetor[j + 1];
        }
        totalItensVetor--;
        printf("\n🗑️ Item '%s' removido do Vetor.\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' não encontrado no Vetor.\n", nomeRemover);
    }
}

/**
 * @brief Lista todos os itens do vetor.
 */
void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("\n--- Mochila Vetor Vazia ---\n");
        return;
    }
    printf("\n--- ITENS VETOR (%d/%d) ---\n", totalItensVetor, MAX_ITENS);
    printf("| %-4s | %-29s | %-15s | %-12s |\n", "POS", "NOME", "TIPO", "QUANTIDADE");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("| %-4d | %-29s | %-15s | %-12d |\n", i + 1, inventarioVetor[i].nome, inventarioVetor[i].tipo, inventarioVetor[i].quantidade);
    }
    printf("-------------------------------------------------------------------\n");
}

/**
 * @brief Implementa a busca sequencial no vetor, contando as comparações.
 * @return O índice do item ou -1.
 */
int buscarSequencialVetor(const char *nomeBusca) {
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++; // Conta uma comparação
        if (strcmp(inventarioVetor[i].nome, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Ordena o vetor usando o algoritmo Bubble Sort (por nome).
 */
void ordenarVetor() {
    Item temp;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            // Compara os nomes para ordenação alfabética.
            if (strcmp(inventarioVetor[j].nome, inventarioVetor[j + 1].nome) > 0) {
                // Swap (Troca)
                temp = inventarioVetor[j];
                inventarioVetor[j] = inventarioVetor[j + 1];
                inventarioVetor[j + 1] = temp;
            }
        }
    }
    printf("\n✔️ Vetor ordenado por nome (Bubble Sort).\n");
}

/**
 * @brief Implementa a busca binária no vetor ordenado, contando as comparações.
 * @return O índice do item ou -1.
 */
int buscarBinariaVetor(const char *nomeBusca) {
    int inicio = 0;
    int fim = totalItensVetor - 1;
    int meio;
    int resultadoComparacao;
    
    // Zera o contador de comparações para a Binária.
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        resultadoComparacao = strcmp(inventarioVetor[meio].nome, nomeBusca);
        comparacoesBinaria++; // Conta uma comparação

        if (resultadoComparacao == 0) {
            return meio; // Item encontrado
        } else if (resultadoComparacao < 0) {
            inicio = meio + 1; // Item está na metade superior
        } else {
            fim = meio - 1; // Item está na metade inferior
        }
    }
    return -1; // Item não encontrado
}

// ----------------------------------------------------------------------------------
//                       FUNÇÕES DA MOCHILA (LISTA ENCADEDA)
// ----------------------------------------------------------------------------------

/**
 * @brief Insere um novo nó no início da lista encadeada.
 */
void inserirItemLista(Item novoItem) {
    // 1. Aloca memória para o novo nó (Item dinâmico).
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n🛑 Erro de alocação de memória!\n");
        return;
    }

    // 2. Preenche os dados e ajusta os ponteiros.
    novoNo->dados = novoItem;
    novoNo->proximo = listaCabeca; // O novo nó aponta para onde a cabeça apontava.
    listaCabeca = novoNo;        // A cabeça aponta para o novo nó.

    totalItensLista++;
    printf("\n✅ Item '%s' adicionado à Lista Encadeada.\n", novoItem.nome);
}

/**
 * @brief Remove um item por nome da lista encadeada.
 */
void removerItemLista(const char *nomeRemover) {
    No *atual = listaCabeca;
    No *anterior = NULL;

    // 1. Busca Sequencial pelo item.
    while (atual != NULL && strcmp(atual->dados.nome, nomeRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        // 2. Remoção (Baixo custo): Ajusta os ponteiros.
        if (anterior == NULL) {
            // O item a ser removido é o primeiro (cabeça).
            listaCabeca = atual->proximo;
        } else {
            // O item está no meio ou fim. O anterior aponta para o próximo do atual.
            anterior->proximo = atual->proximo;
        }

        free(atual); // Libera a memória do nó removido.
        totalItensLista--;
        printf("\n🗑️ Item '%s' removido da Lista Encadeada.\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' não encontrado na Lista Encadeada.\n", nomeRemover);
    }
}

/**
 * @brief Lista todos os itens da lista encadeada (percorrendo os nós).
 */
void listarItensLista() {
    if (listaCabeca == NULL) {
        printf("\n--- Mochila Lista Vazia ---\n");
        return;
    }
    printf("\n--- ITENS LISTA ENCADEDA (Total: %d) ---\n", totalItensLista);
    printf("| %-4s | %-29s | %-15s | %-12s |\n", "POS", "NOME", "TIPO", "QUANTIDADE");
    printf("-------------------------------------------------------------------\n");

    No *atual = listaCabeca;
    int pos = 1;
    while (atual != NULL) {
        printf("| %-4d | %-29s | %-15s | %-12d |\n", pos, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        pos++;
    }
    printf("-------------------------------------------------------------------\n");
}

/**
 * @brief Implementa a busca sequencial na lista encadeada, contando as comparações.
 * @return A posição lógica (1, 2, 3...) do item ou -1.
 */
int buscarSequencialLista(const char *nomeBusca) {
    No *atual = listaCabeca;
    int pos = 1;

    // Zera o contador de comparações para a Lista.
    comparacoesSequencial = 0;

    while (atual != NULL) {
        comparacoesSequencial++; // Conta uma comparação
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            return pos; // Item encontrado
        }
        atual = atual->proximo;
        pos++;
    }
    return -1; // Item não encontrado
}

/**
 * @brief Libera a memória alocada por todos os nós da lista (manutenção).
 */
void limparLista() {
    No *atual = listaCabeca;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    listaCabeca = NULL;
    totalItensLista = 0;
}