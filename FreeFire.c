#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para a função clock()

// --- 1. Definição da Struct ---
#define MAX_COMPONENTES 20
#define CHAVE_BUSCA "Chip Central"

// Struct Componente: Armazena os dados do item e sua prioridade na montagem.
typedef struct {
    char nome[30];      // Nome do componente (ex: "Chip Central")
    char tipo[20];      // Tipo (ex: "Controle", "Suporte", "Propulsão")
    int prioridade;     // Prioridade (1 a 10, sendo 10 a mais alta)
} Componente;

// --- 2. Variáveis Globais para o Inventário e Contadores ---
Componente componentes[MAX_COMPONENTES]; // Vetor estático para o inventário
int totalComponentes = 0;
long long comparacoes = 0;
double tempoExecucao = 0.0;

// --- 3. Protótipos das Funções ---
void exibirMenuPrincipal();
void cadastrarComponente();
void mostrarComponentes(Componente comps[], int n);

// Funções de Ordenação
void bubbleSortNome(Componente comps[], int n);
void insertionSortTipo(Componente comps[], int n);
void selectionSortPrioridade(Componente comps[], int n);

// Função de Busca
int buscaBinariaPorNome(Componente comps[], int n, const char *nomeChave);

// Função de Utilitário
void swap(Componente *a, Componente *b);
void medirEExecutar(void (*algoritmo)(Componente[], int), Componente comps[], int n, const char *algNome);

// ====================================================================
//                             FUNÇÃO PRINCIPAL
// ====================================================================

int main() {
    int opcao;
    
    printf("🚀 Sistema de Montagem da Torre de Fuga - Desafio Mestre 🛠️\n");
    printf("-----------------------------------------------------------\n");

    // Preenche o vetor com dados iniciais (opcional, para testes rápidos)
    // Exemplo de pré-carga para facilitar o teste:
    // strcpy(componentes[0].nome, CHAVE_BUSCA); strcpy(componentes[0].tipo, "Controle"); componentes[0].prioridade = 10;
    // strcpy(componentes[1].nome, "Cabo de Força"); strcpy(componentes[1].tipo, "Suporte"); componentes[1].prioridade = 5;
    // strcpy(componentes[2].nome, "Hélice V3"); strcpy(componentes[2].tipo, "Propulsao"); componentes[2].prioridade = 8;
    // totalComponentes = 3;


    do {
        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\n⚠️ Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n');
            opcao = -1;
        }
        while (getchar() != '\n'); // Limpa buffer

        if (opcao > 0 && opcao <= 5 && totalComponentes == 0 && opcao != 1) {
            printf("\n🛑 O inventário está vazio! Cadastre itens primeiro (Opção 1).\n");
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                // Bubble Sort (por Nome)
                medirEExecutar(bubbleSortNome, componentes, totalComponentes, "Bubble Sort (Nome)");
                break;
            case 3:
                // Insertion Sort (por Tipo)
                medirEExecutar(insertionSortTipo, componentes, totalComponentes, "Insertion Sort (Tipo)");
                break;
            case 4:
                // Selection Sort (por Prioridade)
                medirEExecutar(selectionSortPrioridade, componentes, totalComponentes, "Selection Sort (Prioridade)");
                break;
            case 5:
                // Busca Binária
                printf("\n--- BUSCA BINÁRIA OTIMIZADA ---\n");
                printf("Chave a buscar: **%s**\n", CHAVE_BUSCA);
                
                // A busca binária requer ordenação por nome. Garante que ela foi feita.
                bubbleSortNome(componentes, totalComponentes); 
                printf("-> Vetor temporariamente ordenado por NOME para a busca.\n");

                comparacoes = 0;
                clock_t inicio = clock();
                int indiceChave = buscaBinariaPorNome(componentes, totalComponentes, CHAVE_BUSCA);
                clock_t fim = clock();

                tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                if (indiceChave != -1) {
                    printf("\n✅ CHIP CENTRAL ENCONTRADO! Montagem pode iniciar.\n");
                    printf("  Localizado na Posição: %d\n", indiceChave + 1);
                    printf("  Desempenho: Comparações = %lld | Tempo = %.6f s\n", comparacoes, tempoExecucao);
                } else {
                    printf("\n❌ CHIP CENTRAL (%s) NÃO ENCONTRADO. Missão falhou.\n", CHAVE_BUSCA);
                    printf("  Desempenho: Comparações = %lld | Tempo = %.6f s\n", comparacoes, tempoExecucao);
                }
                mostrarComponentes(componentes, totalComponentes);
                break;
            case 0:
                printf("\n👋 Sistema de montagem encerrado. Fuga abortada.\n");
                break;
            default:
                printf("\n⚠️ Opção inválida. Escolha um número entre 0 e 5.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ====================================================================
//                         IMPLEMENTAÇÃO DE FUNÇÕES
// ====================================================================

/**
 * @brief Exibe o menu principal interativo.
 */
void exibirMenuPrincipal() {
    printf("\n--- ESTRATÉGIA DE MONTAGEM (Componentes: %d/%d) ---\n", totalComponentes, MAX_COMPONENTES);
    printf("1. ➕ Cadastrar Novo Componente\n");
    printf("2. 🔠 Ordenar por NOME (Bubble Sort)\n");
    printf("3. 🏷️ Ordenar por TIPO (Insertion Sort)\n");
    printf("4. 🔟 Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("5. 🔍 Buscar Componente-Chave (Busca Binária)\n");
    printf("0. 🚪 Sair do Sistema\n");
    printf("---------------------------------------------------\n");
}

/**
 * @brief Cadastra um novo componente no vetor.
 */
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n🛑 Limite de componentes (%d) atingido.\n", MAX_COMPONENTES);
        return;
    }

    Componente *novo = &componentes[totalComponentes];

    printf("\n--- Cadastro de Componente (%d/%d) ---\n", totalComponentes + 1, MAX_COMPONENTES);
    
    printf("Nome (max 29): ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0; // Remove newline

    printf("Tipo (ex: Controle, Suporte): ");
    fgets(novo->tipo, sizeof(novo->tipo), stdin);
    novo->tipo[strcspn(novo->tipo, "\n")] = 0;

    printf("Prioridade (1 a 10): ");
    while (scanf("%d", &novo->prioridade) != 1 || novo->prioridade < 1 || novo->prioridade > 10) {
        printf("⚠️ Prioridade inválida. Digite um número de 1 a 10: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n'); // Limpa buffer

    totalComponentes++;
    printf("\n✅ Componente '%s' cadastrado com sucesso.\n", novo->nome);
}

/**
 * @brief Exibe o vetor de componentes de forma formatada.
 */
void mostrarComponentes(Componente comps[], int n) {
    if (n == 0) return;
    
    printf("\n--- COMPONENTES ATUAIS (Montagem Final) ---\n");
    printf("----------------------------------------------------------------\n");
    printf("| %-4s | %-29s | %-15s | %-10s |\n", "POS", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-4d | %-29s | %-15s | %-10d |\n", 
               i + 1, 
               comps[i].nome, 
               comps[i].tipo, 
               comps[i].prioridade);
    }
    printf("----------------------------------------------------------------\n");
}

/**
 * @brief Função auxiliar para trocar dois componentes.
 */
void swap(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Função de utilitário para medir tempo e executar o algoritmo.
 */
void medirEExecutar(void (*algoritmo)(Componente[], int), Componente comps[], int n, const char *algNome) {
    if (n == 0) return;

    comparacoes = 0;
    clock_t inicio = clock();
    algoritmo(comps, n);
    clock_t fim = clock();

    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n*** Resultado da Ordenação: %s ***\n", algNome);
    printf("  Desempenho: Comparações = %lld | Tempo = %.6f s\n", comparacoes, tempoExecucao);
    mostrarComponentes(comps, n);
}

// ----------------------------------------------------------------
//                         ALGORITMOS DE ORDENAÇÃO
// ----------------------------------------------------------------

/**
 * @brief Bubble Sort: Ordena por Nome (String).
 */
void bubbleSortNome(Componente comps[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++; // Comparação de strings
            if (strcmp(comps[j].nome, comps[j + 1].nome) > 0) {
                swap(&comps[j], &comps[j + 1]);
            }
        }
    }
}

/**
 * @brief Insertion Sort: Ordena por Tipo (String).
 */
void insertionSortTipo(Componente comps[], int n) {
    for (int i = 1; i < n; i++) {
        Componente chave = comps[i];
        int j = i - 1;

        // Compara e desloca enquanto o tipo anterior for "maior" que a chave.
        while (j >= 0) {
            comparacoes++; // Comparação de strings
            if (strcmp(comps[j].tipo, chave.tipo) > 0) {
                comps[j + 1] = comps[j];
                j = j - 1;
            } else {
                break; // Sai do laço se a ordem estiver correta
            }
        }
        comps[j + 1] = chave;
        // A última comparação (que fez o laço quebrar ou j se tornar -1) deve ser contada.
        if (j == -1 && i > 0) { comparacoes++; } 
    }
}

/**
 * @brief Selection Sort: Ordena por Prioridade (Inteiro).
 */
void selectionSortPrioridade(Componente comps[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        // Encontra o elemento com a menor prioridade no restante do vetor.
        for (int j = i + 1; j < n; j++) {
            comparacoes++; // Comparação de inteiros
            if (comps[j].prioridade < comps[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o elemento encontrado com o primeiro elemento não ordenado (posição i).
        swap(&comps[min_idx], &comps[i]);
    }
}

// ----------------------------------------------------------------
//                           BUSCA BINÁRIA
// ----------------------------------------------------------------

/**
 * @brief Busca Binária: Localiza um componente por Nome em um vetor ORDENADO.
 * @return O índice do item ou -1 se não encontrado.
 */
int buscaBinariaPorNome(Componente comps[], int n, const char *nomeChave) {
    int inicio = 0;
    int fim = n - 1;
    int meio;
    int resultadoComparacao;
    
    comparacoes = 0; // Zera o contador de comparações para a busca.

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        
        // Compara a string no meio com a chave de busca.
        resultadoComparacao = strcmp(comps[meio].nome, nomeChave);
        comparacoes++; // Conta a comparação principal

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