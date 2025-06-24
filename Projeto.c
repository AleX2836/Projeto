#include "Projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

p_pedido pedidos[MAX_PEDIDO];
int contador = 0;

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void inicializaPedido() {
    for (int i = 0; i < MAX_PEDIDO; i++) {
        pedidos[i] = NULL;
    }
}

void pausaParaContinuar() {
    printf("\nPressione ENTER para continuar..\n");
    getchar();
}

int contadorPedido() {
    return ++contador;
}


/**
 * A função exibirMenu(); tem o objetivo exibir o menu do sistema.
 */
void exibirMenu() {
    printf("\n Menu do Sistema \n");
    printf("1. Cadastrar Novo Pedido \n");
    printf("2. Exibir Pedidos Salvos (Arquivo) \n");
    printf("3. Exibir Faturamento Total \n");
    printf("4. alterar Status do Pedido \n");
    printf("5. Buscar Pedido por Numero \n");
    printf("9. SAIR do sistema \n");
    printf("Escolha sua opcao: \n");
}


/**
 * A função exibirDadosPedidos(); tem o objetivo auxiliar a função buscarPedidoPorNumero(); a mostrar os dados salvos no arquivo .CSV.
 */
void exibirDadosPedidos(pedido *p_p) {
    if (p_p == NULL) {
        printf("Referencia nula...\n");
        return;
    }
    printf("\n-----------------------------\n");
    printf("Numero do Pedido: %d\n", p_p->numero);
    printf("Nome: %s \n", p_p->nome);
    printf("Itens: %s\n", p_p->item);
    printf("CPF: %s \n", p_p->cpf);
    printf("Quantidade: %s \n", p_p->qtd);
    printf("Preco: %s \n", p_p->preco);
    printf("%s \n", p_p->status);
    printf("-----------------------------\n");
}


/**
 * A função cardapio(); tem o objetivo de mostrar os itens que estão disponíveis no estabelecimento.
*/

void cardapio() {
    printf("\n----------------------------\n");
    printf("\n      CARDAPIO\n");
    printf("\n1 - Self service (R$ 30)\n");
    printf("2 - Marmitex Pequena (R$ 13)\n");
    printf("3 - Marmitex Media (R$ 23)\n");
    printf("----------------------------\n\n");
}


/**
 * A função cadastrarPedido(); é a 'principal' função do sistema e tem o objetivo de salvar (número do pedido -
 * nome do cliente - item escolhido - quantidade do item - preço do item - CPF).
*/
void cadastrarPedido() {
    int i = 0;
    int escolhaCpf = 0;
    int posicao = -1;

    for (i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] == NULL) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Nao ha espaco na memoria para mais pedidos\n");
        return;
    }

    pedidos[posicao] = (pedido *)malloc(sizeof(pedido));
    if (pedidos[posicao] == NULL) {
        printf("Erro de alocacao de memoria\n");
        return;
    }

    pedidos[posicao]->numero = contadorPedido();
    strcpy(pedidos[posicao]->status, "Status do Pedido: Em Preparo...");

    cardapio();
    printf("Realizar um novo cadastro de pedido\n");

    printf("Numero do pedido: %d\n", pedidos[posicao]->numero);

    printf("Digite o nome do cliente: \n");
    limparBufferEntrada();
    fgets(pedidos[posicao]->nome, sizeof(pedidos[posicao]->nome), stdin);
    removerNovaLinha(pedidos[posicao]->nome);

    printf("Digite o item: \n");
    fgets(pedidos[posicao]->item, sizeof(pedidos[posicao]->item), stdin);
    removerNovaLinha(pedidos[posicao]->item);

    printf("Digite a Quantidade do item: \n");
    fgets(pedidos[posicao]->qtd, sizeof(pedidos[posicao]->qtd), stdin);
    removerNovaLinha(pedidos[posicao]->qtd);

    printf("Digite o preco total do item: \n");
    fgets(pedidos[posicao]->preco, sizeof(pedidos[posicao]->preco), stdin);
    removerNovaLinha(pedidos[posicao]->preco);

    printf("O cliente deseja cadastrar o CPF? (APERTE 0 PARA SIM E 1 PARA NAO)\n");
    scanf("%d", &escolhaCpf);
    limparBufferEntrada();

    if (escolhaCpf == 0) {
        printf("Digite o CPF do cliente: \n");
        fgets(pedidos[posicao]->cpf, sizeof(pedidos[posicao]->cpf), stdin);
        removerNovaLinha(pedidos[posicao]->cpf);
        printf("%s \n", pedidos[posicao]->status);
        printf("Pedido CADASTRADO \n");
    } else {
        strcpy(pedidos[posicao]->cpf, "NAO INFORMADO");
        printf("%s \n", pedidos[posicao]->status);
        printf("Pedido CADASTRADO \n");
    }

    FILE *arquivo = fopen("C:\\Users\\Pichau\\Projeto\\pasta\\pedidos.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%s\n",
        pedidos[posicao]->numero,
        pedidos[posicao]->nome,
        pedidos[posicao]->item,
        pedidos[posicao]->qtd,
        pedidos[posicao]->cpf,
        pedidos[posicao]->preco,
        pedidos[posicao]->status
    );

    fclose(arquivo);
}


/**
 * A função atualizarArquivoCSV(); tem o objetivo auxiliar no salvamento dos dados no arquivo .CSV, pois os dados de uma novo pedido ficam salvos na memória, essa função pega esses dados e salvo no arquivo .CSV.
*/
void atualizarArquivoCSV() {
    FILE *arquivo = fopen("C:\\Users\\Pichau\\Projeto\\pasta\\pedidos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para atualizar.\n");
        return;
    }

    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL) {
            fprintf(arquivo, "%d,%s,%s,%s,%s,%s,%s\n",
                pedidos[i]->numero,
                pedidos[i]->nome,
                pedidos[i]->item,
                pedidos[i]->qtd,
                pedidos[i]->cpf,
                pedidos[i]->preco,
                pedidos[i]->status
            );
        }
    }

    fclose(arquivo);
}


/**
 * A função exibirPedidosSalvos(); tem o objetivo de fazer a soma do valor de todos os pedidos feitos.
*/
void exibirPedidosSalvos() {

    char linha[256];

    FILE *arquivo = fopen("C:\\Users\\Pichau\\Projeto\\pasta\\pedidos.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de pedidos nao encontrado.\n");
        return;
    }

    printf("\nPedidos Salvos:\n");
    printf("============================\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    printf("============================\n");

    fclose(arquivo);
}


/**
 * A função calcularFaturamentoTotal(); tem o objetivo de fazer a soma do valor de todos os pedidos feitos.
*/
void calcularFaturamentoTotal() {
    float total = 0;
    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL) {
            total += atof(pedidos[i]->preco);
        }
    }
    printf("Faturamento total: R$ %.2f\n", total);
}


/**
 * A função alterarStatusPedido(); tem o objetivo de alterar o status dos pedidos que foram realizados outrora ou os que foram realizados recentemente.
*/
void alterarStatusPedido() {

    int numero;
    char novoStatus[MAX_STATUS];

    printf("Digite o numero do pedido que deseja alterar: ");
    scanf("%d", &numero);
    limparBufferEntrada();

    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL && pedidos[i]->numero == numero) {
            printf("Digite o novo status: ");
            fgets(novoStatus, MAX_STATUS, stdin);
            removerNovaLinha(novoStatus);
            strcpy(pedidos[i]->status, novoStatus);
            atualizarArquivoCSV();
            printf("Status atualizado com sucesso!\n");
            return;
        }
    }

    printf("Pedido nao encontrado.\n");
}


/**
 * A função carregarPedidosDoCSV(); tem o objetivo ler as informações que estão salvas no arquivo .CSV.
*/
void carregarPedidosDoCSV() {

    char linha[256];
    int maiorNumero = 0;
    int i = 0;
    int camposLidos = 0;

    for (int j = 0; j < MAX_PEDIDO; j++) {
        pedidos[j] = NULL;
    }

    contador = 0;

    FILE *arquivo = fopen("C:\\Users\\Pichau\\Projeto\\pasta\\pedidos.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de pedidos não encontrado. Iniciando com lista vazia.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (i >= MAX_PEDIDO) {
            printf("Limite de pedidos atingido durante o carregamento.\n");
            break;
        }

        // Tenta alocar espaço para o novo pedido
        pedidos[i] = (pedido *)malloc(sizeof(pedido));
        if (pedidos[i] == NULL) {
            printf("Erro de alocação de memória.\n");
            break;
        }

        removerNovaLinha(linha);

            camposLidos = sscanf(linha, "%d,%60[^,],%99[^,],%9[^,],%19[^,],%999[^,],%50[^\n]",
            &pedidos[i]->numero,
            pedidos[i]->nome,
            pedidos[i]->item,
            pedidos[i]->qtd,
            pedidos[i]->cpf,
            pedidos[i]->preco,
            pedidos[i]->status
        );

        if (camposLidos != 7) {
            printf("Linha inválida no CSV e será ignorada: %s\n", linha);
            pedidos[i] = NULL;

        } else {

            if (pedidos[i]->numero > maiorNumero) {
                maiorNumero = pedidos[i]->numero;
            }
            i++;
        }
    }

    contador = maiorNumero;
    fclose(arquivo);
}


/**
 * A função buscarPedidoPorNumero(); tem o objetivo buscar e mostrar um determinado pedido pelo número do pedido feito.
*/
void buscarPedidoPorNumero() {

    int numero;

    printf("Digite o numero do pedido que deseja buscar: ");
    scanf("%d", &numero);
    limparBufferEntrada();

    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL && pedidos[i]->numero == numero) {
            exibirDadosPedidos(pedidos[i]);
            return;
        }
    }
    printf("Pedido com numero %d nao encontrado.\n", numero);
}