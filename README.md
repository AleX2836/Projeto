# Projeto: Sistema de Pedidos de Lanchonete/Restaurante

Este é um projeto desenvolvido para a disciplina de Linguagem de Programação da
Fatec Arthur de Azevedo - Mogi Mirim, sob a orientação do Prof. Me. Marcos Roberto
de Moraes. O objetivo é aplicar conceitos de estruturas de dados, manipulação de 
arquivos e práticas de desenvolvimento de software em C.

## Tema Escolhido

Esse projeto implementa um sistema de cadastro de pedidos para um restaurante ou lanchonete,
permitindo o controle dos pedidos com informações como número dos pedidos, nome do cliente,
Item escolhido, a quantidade de item escolhido, o preço total, CPF e Status do pedido.

## Funcionalidades Implementadas

- Cadastro de novos Pedidos;
- Exibir Todos Pedidos Salvos;
- Calculo do Faturamento Total;
- Atualização do Status do Pedido;
- Excluir pedido;
- Busca por número do Pedido.

## Estrutura de Dados

Os dados são armazenados em memória utilizando um vetor globalde ponteiros para
structs, com alocação dinâmica. A persistência dos dados é realizada em um arquivo
CSV.

## Como Baixar e Compilar

1. **Clone o repositório:**
    ```bash
   git clone github.com/AleX2836/Projeto.git
   cd Projeto
   ```

2. **Compile o código:**
   Certifique-se de ter um compilador C(como o GCC) instalado.
   ```bash
   gcc -O main.c Projeto.c -Wall
   ```

## Como Testar

1. **Execute o programa compilado:**
   ```bash
   ./Projeto
   ```

2. Siga as instruções do menu interativo no console para realizaras operações de Cadastro de pedidos.

## Autores

- Alexsander Vieira Junior
- Bruno Chagas De Oliveira
- Caio vitor
- Fábio de Paula
- Luidy de Magalhaes Faria