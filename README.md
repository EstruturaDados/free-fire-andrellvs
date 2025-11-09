---
🔫🎒 Desafio Código da Ilha – Edição Free Fire
---
DESAFIO DE PROGRAMAÇÃO EM C: INVENTÁRIO DE SOBREVIVÊNCIA E OTIMIZAÇÃO
---
Este repositório documenta a solução para uma série de desafios de programação em C, focados na construção e otimização de um Sistema de Inventário simulando um jogo de sobrevivência. O projeto é uma progressão prática no uso de Estruturas de Dados (Vetores e Listas Encadeadas) e Algoritmos de Ordenação e Busca (Sequencial, Binária, Bubble, Insertion e Selection Sort).

---

VISÃO GERAL E NÍVEIS DE DIFICULDADE

O desafio é dividido em três níveis, cada um introduzindo conceitos fundamentais:

Nível | Foco Principal | Estruturas | Algoritmos
:--- | :--- | :--- | :---
Novato | Implementação básica de structs e operações sequenciais. | Vetores | Busca Sequencial
Aventureiro | Comparação de desempenho entre estruturas de dados. | Vetor vs. Lista Encadeada | Busca Sequencial e Busca Binária
Mestre | Análise empírica e escolha estratégica de algoritmos. | Vetores | Bubble, Insertion, Selection Sort e medição de performance.

---

FUNCIONALIDADES CHAVE

* Otimização: Aplicação de Busca Binária (O(log n)) para localização rápida de itens, demonstrando a necessidade de ordenação.
* Análise de Desempenho (Nível Mestre): O sistema mede e exibe o tempo de execução (clock()) e o número de comparações para os diferentes algoritmos de ordenação, provando qual estratégia é mais eficiente em diferentes cenários.
* Modelagem de Dados: Estruturas de dados complexas para simular itens (Componente) e suas prioridades.

---

COMO COMPILAR E EXECUTAR

O código está escrito em C padrão e é compilado usando o GNU Compiler Collection (GCC).

1. Clonar o Repositório

Use o comando git clone para baixar o código fonte:
```
git clone [URL_DO_SEU_REPOSITORIO] 
cd [NOME_DO_REPOSITORIO]
```
2. Compilar o Código

Assumindo que o código final (nível Mestre) está no arquivo inventario.c, use o gcc para compilar:
```
gcc inventario.c -o inventario 
```
3. Executar o Sistema

Após a compilação, execute o programa a partir do terminal:
```
./inventario
```
O programa será iniciado, e um menu interativo guiará você pelas funcionalidades de cadastro, ordenação e busca, mostrando métricas de desempenho.

---

EXEMPLO DE TRECHO DO CÓDIGO (NÍVEL MESTRE)

Abaixo está a definição da struct principal utilizada no nível Mestre:

typedef struct {
    char nome[30];      // Nome do componente (ex: "Chip Central")
    char tipo[20];      // Tipo (ex: "Controle", "Suporte", "Propulsão")
    int prioridade;     // Prioridade (1 a 10)
} Componente;

---

CONTRIBUIÇÃO

Contribuições para otimizar os algoritmos, refatorar o código ou expandir as funcionalidades são bem-vindas! Sinta-se à vontade para abrir uma issue ou enviar um pull request.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# 🔫🎒 Desafio Código da Ilha – Edição Free Fire

Bem-vindo ao **Desafio Código da Ilha – Edição Free Fire!**  
Neste desafio, você irá simular o gerenciamento de um **inventário de sobrevivência** em uma ilha misteriosa, utilizando a linguagem **C**.

A empresa **MateCheck** encarregou você de desenvolver o sistema de **mochila virtual** que ajudará os sobreviventes a se prepararem para escapar da ilha.  
O desafio é dividido em três níveis: **Novato**, **Aventureiro** e **Mestre**, cada um com mais complexidade e poder.


## 🎮 Nível Novato: Inventário Básico

### 🚩 Objetivo

Criar um programa em C com as seguintes funcionalidades:

- Adicionar itens à mochila (**nome**, **tipo** e **quantidade**)
- Remover itens pelo nome
- Listar os itens cadastrados

### ⚙️ Funcionalidades

- Utilização de `struct` para representar cada item
- Vetor estático com capacidade para até **10 itens**
- Leitura e escrita via terminal (`scanf`, `printf`)
- Menu interativo com `switch` e `do-while`

### 🧠 Simplicidade

- Sem ordenações, buscas especializadas ou uso de ponteiros
- Ideal para praticar manipulação básica de estruturas e arrays

### 📥 Entrada

O usuário escolhe ações no menu e preenche os dados dos itens conforme solicitado.

### 📤 Saída

O programa exibe os dados organizados em formato de tabela, com nome, tipo e quantidade.



## 🛡️ Nível Aventureiro: Mochila com Busca

### 🆕 Diferenças em relação ao Nível Novato

- Implementação de **busca sequencial** por nome
- Novidade no menu: opção de **"Buscar item por nome"**
- Exibição detalhada do item encontrado

### ⚙️ Funcionalidades

- O usuário pode procurar qualquer item já inserido
- Se encontrado, o programa exibe seus atributos
- Caso contrário, exibe mensagem de erro amigável

### 💡 Conceitos Adicionados

- **Busca sequencial**
- **Comparação de strings** (`strcmp`)
- **Controle com flag** para indicar se item foi encontrado

### 📥 Entrada

O usuário digita o nome do item que deseja buscar.

### 📤 Saída

- Detalhes completos do item (nome, tipo, quantidade)
- Ou uma mensagem de erro, se não for encontrado

---

## 🧠 Nível Mestre: Ordenação e Busca Binária

### 🆕 Diferenças em relação ao Nível Aventureiro

- Adição do campo **prioridade** aos itens (valores de 1 a 5)
- Possibilidade de **ordenar** a mochila por **nome**, **tipo** ou **prioridade**
- Implementação da **busca binária** por nome com verificação de ordenação

### ⚙️ Funcionalidades

- **Menu de ordenação**: o jogador escolhe o critério desejado
- Contador de **comparações na ordenação** para análise de desempenho
- **Busca binária** com validação de pré-requisito (lista deve estar ordenada por nome)

### 💡 Conceitos Adicionados

- **Enumeração** (`enum`) para critérios de ordenação
- **Ordenação com Insertion Sort**
- **Busca binária** (`binary search`)
- Uso de **bool** para controle de estado
- **Análise de desempenho** com contador de comparações

### 📥 Entrada

O usuário:

1. Adiciona itens com prioridade
2. Ordena os itens
3. Realiza busca binária pelo nome do item

### 📤 Saída

- Mochila **ordenada** com base no critério escolhido
- Exibição dos **dados do item buscado** ou mensagem de erro
- **Quantidade de comparações** realizadas durante a ordenação



## 🏁 Conclusão

Ao completar qualquer nível do **Desafio Código da Ilha – Edição Free Fire**, você terá avançado significativamente na programação em **C**, desenvolvendo habilidades práticas de:

- Manipulação de **estruturas e arrays**
- Criação de **menus interativos**
- Implementação de **buscas e ordenações**
- **Pensamento modular** e boas práticas de software

Cada nível representa uma missão rumo à **sobrevivência total**.  
Escolha seu nível, prepare sua mochila... e **boa sorte na ilha!** 🏝️💼🔍

> Equipe de Ensino – MateCheck
