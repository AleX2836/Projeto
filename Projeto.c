#include "Projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

p_pedido pedidos[MAX_PEDIDO];

//Variável para armazenar o número dos medidos.
int contador = 0;

//Variáves para uso da tabela ASCII.
int a = 186;
int b = 187;
int c = 201;
int d = 188;
int e = 200;
int f = 175;

/**
 * A função limparBufferEntrada(); tem o objetivo de remover caracteres restantes no buffer de entrada.
*/
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * A função removerNovaLinha(); tem o objetivo de remover o caracter de nova linha(\n).
*/
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/**
 * A função inicializaPedido(); tem o objetivo inicializar os pedidos no arquivo CSV.
*/
void inicializaPedido() {
    for (int i = 0; i < MAX_PEDIDO; i++) {
        pedidos[i] = NULL;
    }
}

/**
 * A função pausaParaContinuar(); tem o objetivo de dar um intervalo no meio das ações do sistema.
*/
void pausaParaContinuar() {
    printf("\n Pressione ENTER para continuar..\n");
    getchar();
}

/**
 * A função contadorPedido(); tem o objetivo de acumular os números dos pedidos de forma crescente.
*/
int contadorPedido() {
    return ++contador;
}

/**
 * A função linhas(int qtd); tem o objetivo de ajudar na estética dos menus.
*/
void linhas(int qtd){

    int v = 220;

    for (int i = 0; i < qtd; i++) {
        printf("%c", v);
    }
}

/**
 * A função validarNome(); tem o objetivo de ser uma função auxiliar, para que o usuário digite corretamente o seu nome.
*/
int validarNome(const *nome) {

    if (strlen(nome) == 0) return 0;

    for (int i = 0; nome[i] != '\0'; i++) {
        if (nome[i] >='0' && nome[i] <= '9') {
            return 0;
        }
    }
    return 1;
}

/**
 * A função validarCPF(); tem o objetivo de ser uma função auxiliar, para que o usuário digite corretamente o seu CPF.
*/
int validarCPF(const char *cpf) {

    if (strlen(cpf) != 14) return 0;

    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            if (cpf[i] != '.')
                return 0;
        } else if (i == 11) {
            if (cpf[i] != '-')
                return 0;
        } else {
            if (cpf[i] < '0' || cpf[i] > '9')
                return 0;
        }
    }
    return 1;
}

/**
 * A função exibirMenu(); tem o objetivo exibir o menu do sistema.
*/
void exibirMenu() {

    printf(" %c=================================%c\n", c, b);
    printf(" %c                                 %c\n", a, a);
    printf(" %c         Menu do Sistema         %c\n", a, a);
    printf(" %c                                 %c\n", a, a);
    printf(" %c   1 %c Cadastrar Novo Pedido     %c\n", a,f, a);
    printf(" %c   2 %c Exibir Pedidos Salvos     %c\n", a,f, a);
    printf(" %c   3 %c Exibir Faturamento Total  %c\n", a,f, a);
    printf(" %c   4 %c Alterar Status do Pedido  %c\n", a,f, a);
    printf(" %c   5 %c Buscar Pedido por Numero  %c\n", a,f, a);
    printf(" %c   6 %c Excluir pedido            %c\n", a,f, a);
    printf(" %c   9 %c SAIR do sistema           %c\n", a,f, a);
    printf(" %c                                 %c\n", a, a);
    printf(" %c        Escolha sua opcao        %c\n", a, a);
    printf(" %c=================================%c\n", e, d);

}

/**
 * A função exibirDadosPedidos(); tem o objetivo auxiliar a função buscarPedidoPorNumero(); a mostrar os dados salvos no arquivo .CSV.
*/
void exibirDadosPedidos(pedido *p_p) {

    if (p_p == NULL) {
        printf(" Referencia nula...\n");
        return;
    }

    linhas(35);
    printf("\n   Pedido      :  %d     \n",p_p->numero);
    printf("   Nome        :  %s     \n",p_p->nome);
    printf("   Item        :  %s     \n",p_p->item);
    printf("   Quantidade  :  %s     \n",p_p->qtd);
    printf("   CPF         :  %s     \n",p_p->cpf);
    printf("   Preco       :  R$ %s  \n",p_p->preco);
    printf("   Status      : %s     \n",p_p->status);
    linhas(35);
}

/**
 * A função cardapio(); tem o objetivo de mostrar os itens que estão disponíveis no estabelecimento.
*/

void cardapio() {

    printf(" %c=================================%c\n", c, b);
    printf(" %c                                 %c\n",a ,a);
    printf(" %c           CARDAPIO              %c\n",a ,a);
    printf(" %c                                 %c\n",a ,a);
    printf(" %c  1 %c Self service.....(R$ 30)   %c\n",a,f ,a);
    printf(" %c  2 %c Marmitex Pequena.(R$ 13)   %c\n",a,f ,a);
    printf(" %c  3 %c Marmitex Media...(R$ 23)   %c\n",a,f ,a);
    printf(" %c  4 %c Marmitex Grande..(R$ 30)   %c\n",a,f ,a);
    printf(" %c  5 %c Marmitex do dia..(R$ 23)   %c\n",a,f ,a);
    printf(" %c  6 %c Coca Cola........(R$ 08)   %c\n",a,f ,a);
    printf(" %c  7 %c Coxinha..........(R$ 10)   %c\n",a,f ,a);
    printf(" %c                                 %c\n",a ,a);
    printf(" %c        Escolha sua opcao        %c\n", a ,a);
    printf(" %c==================================%c\n", e, d);

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
        printf(" Nao ha espaco na memoria para mais pedidos\n");
        return;
    }

    pedidos[posicao] = (pedido *)malloc(sizeof(pedido));

    if (pedidos[posicao] == NULL) {
        printf(" Erro de alocacao de memoria\n");
        return;
    }

    limparBufferEntrada();

    cardapio();
    printf("\n Realizar um novo cadastro de pedido\n");

    pedidos[posicao]->numero = contadorPedido();
    strcpy(pedidos[posicao]->status, " Em Preparo...");

    printf(" Numero do pedido: %d\n", pedidos[posicao]->numero);


    do {
        printf(" Digite o nome do cliente: \n");
        fgets(pedidos[posicao]->nome, sizeof(pedidos[posicao]->nome), stdin);
        removerNovaLinha(pedidos[posicao]->nome);
        if (!validarNome(pedidos[posicao]->nome)) {
            printf(" Nome invalido\n");
        }
    }while (!validarNome(pedidos[posicao]->nome));

    printf(" Digite o item: \n");
    fgets(pedidos[posicao]->item, sizeof(pedidos[posicao]->item), stdin);
    removerNovaLinha(pedidos[posicao]->item);

    printf(" Digite a Quantidade do item: \n");
    fgets(pedidos[posicao]->qtd, sizeof(pedidos[posicao]->qtd), stdin);
    removerNovaLinha(pedidos[posicao]->qtd);

    printf(" Digite o preco total do item: \n");
    fgets(pedidos[posicao]->preco, sizeof(pedidos[posicao]->preco), stdin);
    removerNovaLinha(pedidos[posicao]->preco);

    printf(" O cliente deseja cadastrar o CPF? (APERTE 0 PARA SIM E 1 PARA NAO)\n");
    scanf("%d", &escolhaCpf);
    limparBufferEntrada();

    if (escolhaCpf == 0) {

        do {
        printf("\n Digite o CPF do cliente (XXX.XXX.XXX-XX): \n");
        fgets(pedidos[posicao]->cpf, sizeof(pedidos[posicao]->cpf), stdin);
        removerNovaLinha(pedidos[posicao]->cpf);

        if (!validarCPF(pedidos[posicao]->cpf)){
            printf("\n CPF digitado incorretamente, digite novamente. \n");
        }

        }while (!validarCPF(pedidos[posicao]->cpf));

        printf("%s \n", pedidos[posicao]->status);
        printf("\n Pedido CADASTRADO \n");

    } else {
        strcpy(pedidos[posicao]->cpf, "NAO INFORMADO");

        printf("%s \n", pedidos[posicao]->status);
        printf("\n Pedido CADASTRADO \n");
    }

    FILE *arquivo = fopen("C:\\Users\\Pichau\\Projeto\\pasta\\pedidos.csv", "a");
    if (arquivo == NULL) {

        printf(" Erro ao abrir o arquivo para escrita.\n");

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
        printf(" Erro ao abrir o arquivo para atualizar.\n");
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
    int campos;
    pedido p;
    int g = 254;
    int h = 219;
    int v = 220;

    FILE *arquivo = fopen("C:\\Users\\Pichau\\Projeto\\pasta\\pedidos.csv", "r");
    if (arquivo == NULL) {
        printf(" Arquivo de pedidos nao encontrado.\n");
        return;
    }

    printf("\n              PEDIDOS SALVOS\n");
    linhas(45);
    printf("\n");
    linhas(20);


    while (fgets(linha, sizeof(linha), arquivo)) {
        removerNovaLinha(linha);

        campos = sscanf(linha, "%d,%60[^,],%99[^,],%9[^,],%19[^,],%999[^,],%50[^\n]",
           &p.numero, p.nome, p.item, p.qtd, p.cpf, p.preco, p.status
       );


        if (campos == 7) {
            linhas(20);
            printf("\n %c Pedido #%d          \n",g, p.numero);
            printf(" %c Nome        :  %s     \n",g, p.nome);
            printf(" %c Item        :  %s     \n",g, p.item);
            printf(" %c Quantidade  :  %s     \n",g, p.qtd);
            printf(" %c CPF         :  %s     \n",g, p.cpf);
            printf(" %c Preco       :  R$ %s  \n",g, p.preco);
            printf(" %c Status      : %s     \n",g, p.status);
            linhas(20);
        } else {
            printf(" Linha inválida encontrada: %s\n", linha);
        }
    }

    linhas(20);
    printf("\n");
    linhas(45);
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
    linhas(35);
    printf("\n");
    printf("\n  Faturamento total: R$ %.2f  \n", total);
    printf("\n");
    linhas(35);
}

/**
 * A função alterarStatusPedido(); tem o objetivo de alterar o status dos pedidos que foram realizados outrora ou os que foram realizados recentemente.
*/
void alterarStatusPedido() {

    int numero;
    char novoStatus[MAX_STATUS];

    printf(" Digite o numero do pedido que deseja alterar: ");
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
    printf(" Pedido nao encontrado.\n");
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
        printf(" Arquivo de pedidos nao encontrado.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (i >= MAX_PEDIDO) {
            printf(" Limite de pedidos atingido.\n");
            break;
        }

        pedidos[i] = (pedido *)malloc(sizeof(pedido));
        if (pedidos[i] == NULL) {
            printf(" Erro de alocação de memória.\n");
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
            printf(" Linha inválida no CSV e será ignorada: %s\n", linha);
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

    printf(" Digite o numero do pedido que deseja buscar: ");
    scanf("%d", &numero);
    limparBufferEntrada();

    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL && pedidos[i]->numero == numero) {
            exibirDadosPedidos(pedidos[i]);
            return;
        }
    }
    printf(" Pedido com numero %d nao encontrado.\n", numero);
}

/**
 * A função excluirPedido(); tem o objetivo excluir algum pedido já feito.
*/
void excluirPedido() {

    int n;
    int encontrado;
    int novo = 1;

    printf(" Digite o numero do pedido a ser excluido: ");
    scanf("%d", &n);
    limparBufferEntrada();

    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL && pedidos[i]->numero == n) {
        pedidos[i] = NULL;
        encontrado = 1;
        break;
        }
    }

    if (!encontrado) {
        printf(" Pedido com numero %d nao encontrado.\n", n);
        return;
    }

    for (int i = 0; i < MAX_PEDIDO; i++) {
        if (pedidos[i] != NULL) {
            pedidos[i] -> numero = novo++;
        }
    }

    contador = novo - 1;

    atualizarArquivoCSV();
    printf("Pedido excluido");

}