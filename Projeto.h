#ifndef PROJETO_H
#define PROJETO_H

#define MAX_PEDIDO 10000
#define MAX_NOME 61
#define MAX_ITEM 100
#define MAX_CPF 20
#define MAX_QTD 10
#define MAX_PRECO 10000
#define MAX_STATUS 51

typedef struct pedido {
    int numero;
    char nome[MAX_NOME];
    char item[MAX_ITEM];
    char cpf[MAX_CPF];
    char qtd[MAX_QTD];
    char preco[MAX_PRECO];
    char status[MAX_STATUS];
} pedido;

typedef pedido *p_pedido;

extern p_pedido pedidos[MAX_PEDIDO];

void exibirMenu();

void pausaParaContinuar();

void cadastrarPedido();

void exibirPedidosSalvos();

void calcularFaturamentoTotal();

void alterarStatusPedido();

void inicializaPedido();

void carregarPedidosDoCSV();

void buscarPedidoPorNumero();


#endif // PROJETO_H
