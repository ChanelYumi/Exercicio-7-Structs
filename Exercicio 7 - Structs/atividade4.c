/*
Uma loja deseja controlar suas vendas. Crie as estruturas Produto e Venda, sendo que cada venda deverá armazenar os dados de um produto, a quantidade vendida e o valor total.

Requisitos:
1. Cadastrar até 10 produtos.
2. Registrar até 20 vendas.
3. Associar cada venda a um produto cadastrado.
4. Atualizar o estoque após cada venda.
5. Calcular o faturamento total.
6. Identificar o produto que gerou o maior faturamento.
*/

#include <stdio.h>
#define MAX_PRODUTOS 10
#define MAX_VENDAS 20

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

typedef struct {
    Produto produto;     // dados do produto vendido
    int quantidade;      // quantas unidades
    float valorTotal;    // preco x quantidade
} Venda;

int buscarProduto(Produto produtos[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto(Produto produtos[], int *totalProdutos) {
    if (*totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de %d produtos atingido!\n", MAX_PRODUTOS);
        return;
    }
    Produto novo;
    printf("Codigo: ");
    scanf("%d", &novo.codigo);
    if (buscarProduto(produtos, *totalProdutos, novo.codigo) != -1) {
        printf("Erro: codigo ja cadastrado!\n");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Preco: ");
    scanf("%f", &novo.preco);
    printf("Estoque: ");
    scanf("%d", &novo.estoque);
    if (novo.preco < 0 || novo.estoque < 0) {
        printf("Erro: valores negativos nao sao permitidos!\n");
        return;
    }
    produtos[*totalProdutos] = novo;
    (*totalProdutos)++;
    printf("Produto cadastrado!\n");
}

void atualizarEstoque(Produto *p, int quantidadeVendida) {
    p->estoque = p->estoque - quantidadeVendida;
}

void registrarVenda(Produto produtos[], int totalProdutos, Venda vendas[], int *totalVendas) {
    if (*totalVendas >= MAX_VENDAS) {
        printf("Limite de %d vendas atingido!\n", MAX_VENDAS);
        return;
    }
    int codigo, qtd;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    int pos = buscarProduto(produtos, totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao cadastrado!\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &qtd);
    if (qtd <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    if (qtd > produtos[pos].estoque) {
        printf("Estoque insuficiente! Disponivel: %d\n", produtos[pos].estoque);
        return;
    }

    Venda nova;
    nova.produto = produtos[pos];               
    nova.quantidade = qtd;
    nova.valorTotal = produtos[pos].preco * qtd;

    vendas[*totalVendas] = nova;
    (*totalVendas)++;

    atualizarEstoque(&produtos[pos], qtd);
    printf("Venda registrada! Total: R$ %.2f | Estoque restante: %d\n",
           nova.valorTotal, produtos[pos].estoque);
}

void listarProdutos(Produto produtos[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("%d - %s | R$ %.2f | Estoque: %d\n",
               produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

void listarVendas(Venda vendas[], int total) {
    if (total == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("Venda %d: %s | %d un. | R$ %.2f\n",
               i + 1, vendas[i].produto.nome, vendas[i].quantidade, vendas[i].valorTotal);
    }
}

float calcularFaturamento(Venda vendas[], int totalVendas) {
    float soma = 0;
    for (int i = 0; i < totalVendas; i++) {
        soma = soma + vendas[i].valorTotal;
    }
    return soma;
}

float faturamentoDoProduto(Venda vendas[], int totalVendas, int codigo) {
    float soma = 0;
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].produto.codigo == codigo) {
            soma = soma + vendas[i].valorTotal;
        }
    }
    return soma;
}


void exibirProdutoMaiorFaturamento(Produto produtos[], int totalProdutos, Venda vendas[], int totalVendas) {
    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }
    int posMaior = 0;
    float maior = faturamentoDoProduto(vendas, totalVendas, produtos[0].codigo);
    for (int i = 1; i < totalProdutos; i++) {
        float atual = faturamentoDoProduto(vendas, totalVendas, produtos[i].codigo);
        if (atual > maior) {
            maior = atual;
            posMaior = i;
        }
    }
    printf("Produto com maior faturamento: %s (R$ %.2f)\n", produtos[posMaior].nome, maior);
}

void mostrarMenu() {
    printf("\n===== LOJA =====\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Registrar venda\n");
    printf("3 - Listar produtos\n");
    printf("4 - Listar vendas\n");
    printf("5 - Faturamento total\n");
    printf("6 - Produto com maior faturamento\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    Venda vendas[MAX_VENDAS];
    int totalProdutos = 0, totalVendas = 0;
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrarProduto(produtos, &totalProdutos); break;
            case 2: registrarVenda(produtos, totalProdutos, vendas, &totalVendas); break;
            case 3: listarProdutos(produtos, totalProdutos); break;
            case 4: listarVendas(vendas, totalVendas); break;
            case 5: printf("Faturamento total: R$ %.2f\n", calcularFaturamento(vendas, totalVendas)); break;
            case 6: exibirProdutoMaiorFaturamento(produtos, totalProdutos, vendas, totalVendas); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}