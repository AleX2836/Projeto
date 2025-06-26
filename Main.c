#include <stdio.h>
#include "Projeto.h"

int main(void) {


    inicializaPedido();
    carregarPedidosDoCSV();

    int opcao = 0;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarPedido();
                break;
            case 2:
                exibirPedidosSalvos();
                break;
            case 3:
                calcularFaturamentoTotal();
                break;
            case 4:
                alterarStatusPedido();
                break;
            case 5:
                buscarPedidoPorNumero();
                break;
            case 9:
                printf("Encerrando o sistema\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
        if (opcao != 9) {
            pausaParaContinuar();
        }
    } while (opcao != 9);
    printf("Programa finalizado\n");
    return 0;
}






