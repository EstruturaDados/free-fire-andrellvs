#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. Definição da Struct ---
// Struct 'Item': Armazena os dados essenciais de um objeto coletado.
typedef struct {
    char nome[30];      // Nome do item (ex: Pistola, Munição 9mm)
    char tipo[20];      // Tipo do item (ex: arma, munição, cura, ferramenta)
    int quantidade;     // Quantidade em posse do jogador
} Item;

// --- 2. Variáveis Globais para o Inventário ---
#define MAX_ITENS 10
Item inventario[MAX_ITENS]; // Vetor de structs para armazenar até 10 itens.
int totalItens = 0;         // Contador de itens atualmente na mochila (índice do próximo item livre).

// --- 3. Protótipos das Funções ---
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
int buscarItem(const char *nomeBusca); // Retorna o índice do item ou -1 se não encontrado.

// ====================================================================
//                             FUNÇÃO PRINCIPAL
// ====================================================================

int main() {
    int opcao;

    printf("🎮 Sistema de Inventário - Desafio Novato (Sobrevivência) 🎒\n");
    printf("-----------------------------------------------------------\n");

    // Laço principal do programa (Loop do Jogo/Sistema)
    do {
        exibirMenu(); // Exibe as opções para o jogador.
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            // Tratamento de erro para entrada não numérica
            printf("\n⚠️ Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            opcao = -1; // Garante que o loop continue
        } else {
            // Execução da operação selecionada.
            switch (opcao) {
                case 1:
                    inserirItem();
                    break;
                case 2:
                    removerItem();
                    break;
                case 3:
                    listarItens();
                    break;
                case 4:
                    // Solicita o nome para a busca sequencial.
                    printf("➡️ Digite o nome do item para buscar: ");
                    char nomeBusca[30];
                    scanf("%s", nomeBusca); // Lê o nome (cuidado com espaços)
                    int indiceEncontrado = buscarItem(nomeBusca);
                    
                    if (indiceEncontrado != -1) {
                        printf("\n✨ Item Encontrado (Busca Sequencial) ✨\n");
                        printf("Nome: %s\n", inventario[indiceEncontrado].nome);
                        printf("Tipo: %s\n", inventario[indiceEncontrado].tipo);
                        printf("Quantidade: %d\n", inventario[indiceEncontrado].quantidade);
                    } else {
                        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
                    }
                    break;
                case 0:
                    printf("\n👋 Sistema de inventário encerrado. Boa sobrevivência!\n");
                    break;
                default:
                    printf("\n⚠️ Opção inválida. Escolha um número entre 0 e 4.\n");
            }
            // Listagem dos itens após cada operação (requisito)
            if (opcao >= 1 && opcao <= 4) {
                 printf("\n--- Estado Atual da Mochila ---\n");
                 listarItens();
                 printf("-------------------------------\n");
            }
        }
    } while (opcao != 0);

    return 0;
}

// ====================================================================
//                         IMPLEMENTAÇÃO DAS FUNÇÕES
// ====================================================================

/**
 * @brief Exibe o menu principal de opções para o jogador.
 */
void exibirMenu() {
    printf("\n--- Escolha sua Ação ---\n");
    printf("1. Cadastrar Novo Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Todos os Itens\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair do Sistema\n");
    printf("------------------------\n");
}

/**
 * @brief Adiciona um novo item ao inventário.
 * Requisito: Cadastro de até 10 itens.
 */
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n🛑 Mochila cheia! Não é possível carregar mais itens (%d/%d).\n", totalItens, MAX_ITENS);
        return;
    }

    printf("\n--- Cadastro de Novo Item ---\n");

    // Coleta o nome do item.
    printf("Nome do Item (max 29 caracteres): ");
    scanf("%s", inventario[totalItens].nome); // Simples para este nível, mas cuidado com espaços.

    // Coleta o tipo (arma, munição, cura, ferramenta).
    printf("Tipo do Item (ex: arma, municao, cura): ");
    scanf("%s", inventario[totalItens].tipo);

    // Coleta a quantidade.
    printf("Quantidade: ");
    while (scanf("%d", &inventario[totalItens].quantidade) != 1 || inventario[totalItens].quantidade <= 0) {
        printf("⚠️ Quantidade inválida. Digite um número inteiro positivo: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    // Aumenta o contador e confirma.
    printf("\n✅ Item '%s' adicionado à mochila (Posição: %d).\n", inventario[totalItens].nome, totalItens + 1);
    totalItens++;
}

/**
 * @brief Implementa a busca sequencial por nome.
 * @param nomeBusca Nome do item a ser localizado.
 * @return O índice do item no vetor ou -1 se não encontrado.
 */
int buscarItem(const char *nomeBusca) {
    // Laço 'for' para percorrer o vetor sequencialmente (Busca Sequencial).
    for (int i = 0; i < totalItens; i++) {
        // Compara a string de busca com o nome do item atual (case-sensitive).
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado! Retorna seu índice.
        }
    }
    return -1; // Item não encontrado após percorrer todo o vetor.
}

/**
 * @brief Remove um item do inventário, informando seu nome.
 */
void removerItem() {
    if (totalItens == 0) {
        printf("\n🚫 A mochila está vazia. Não há itens para remover.\n");
        return;
    }

    printf("\n--- Remoção de Item ---\n");
    printf("➡️ Digite o nome do item para remover: ");
    char nomeRemover[30];
    scanf("%s", nomeRemover);

    // Usa a função de busca sequencial para encontrar o item.
    int indiceRemover = buscarItem(nomeRemover);

    if (indiceRemover != -1) {
        // Remoção: Move o último item para a posição do item a ser removido.
        // Isso preenche o "buraco" e mantém a estrutura sequencial sem precisar mover todos os itens subsequentes.
        // O último item é copiado para a posição do item a ser excluído.
        if (indiceRemover != totalItens - 1) { // Evita a cópia se o item a remover for o último.
            inventario[indiceRemover] = inventario[totalItens - 1];
        }
        
        // Diminui o contador de itens, efetivamente "removendo" o último item (que agora pode ser uma duplicata ou o original que estava lá).
        totalItens--; 
        printf("\n🗑️ Item '%s' removido da mochila com sucesso.\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' não encontrado na mochila. A remoção falhou.\n", nomeRemover);
    }
}

/**
 * @brief Lista todos os itens atualmente registrados na mochila com seus dados.
 * Requisito: Listagem dos itens.
 */
void listarItens() {
    if (totalItens == 0) {
        printf("--- Mochila Vazia ---\n");
        printf("Ainda não há itens coletados. Corra e encontre algum loot!\n");
        return;
    }

    printf("--- ITENS ATUAIS NA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    printf("-------------------------------------------------------------------\n");
    printf("| %-4s | %-29s | %-15s | %-12s |\n", "POS", "NOME", "TIPO", "QUANTIDADE");
    printf("-------------------------------------------------------------------\n");

    // Laço 'for' para percorrer e imprimir cada item.
    for (int i = 0; i < totalItens; i++) {
        printf("| %-4d | %-29s | %-15s | %-12d |\n", 
               i + 1, // Posição (para o jogador)
               inventario[i].nome, 
               inventario[i].tipo, 
               inventario[i].quantidade);
    }
    printf("-------------------------------------------------------------------\n");
}