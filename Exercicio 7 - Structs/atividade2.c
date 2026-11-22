/*
Uma papelaria precisa controlar seus produtos. Crie uma struct Produto com código, nome, preço e quantidade em estoque.
O programa deverá cadastrar até 15 produtos e oferecer um menu com as opções de cadastrar, listar, repor estoque, registrar venda e consultar produto pelo código.

Requisitos:
1. Não permitir códigos duplicados.
2. Impedir vendas superiores à quantidade disponível.
3. Atualizar o estoque por meio de funções que recebam ponteiros.
4. Calcular o valor total dos produtos em estoque.
5. Identificar o produto com maior valor total em estoque
*/

#include <stdio.h>
#define MAX_PRODUTOS 15

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;


int buscarProduto(Produto produtos[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}


void cadastrarProduto(Produto produtos[], int *total) {
    if (*total >= MAX_PRODUTOS) {
        printf("Limite de %d produtos atingido!\n", MAX_PRODUTOS);
        return;
    }

    int codigo;
    printf("Codigo: ");
    scanf("%d", &codigo);

   
    if (buscarProduto(produtos, *total, codigo) != -1) {
        printf("Erro: ja existe um produto com esse codigo!\n");
        return;
    }

    Produto novo;
    novo.codigo = codigo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Preco: ");
    scanf("%f", &novo.preco);
    printf("Quantidade em estoque: ");
    scanf("%d", &novo.quantidade);

    if (novo.preco < 0 || novo.quantidade < 0) {
        printf("Erro: preco e quantidade nao podem ser negativos!\n");
        return;
    }

    produtos[*total] = novo;
    (*total)++;
    printf("Produto cadastrado com sucesso!\n");
}


void listarProdutos(Produto produtos[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\n--- LISTA DE PRODUTOS ---\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: %d | %s | R$ %.2f | Estoque: %d\n",
               produtos[i].codigo, produtos[i].nome,
               produtos[i].preco, produtos[i].quantidade);
    }
}

void reporEstoque(Produto *p, int quantidade) {
    p->quantidade = p->quantidade + quantidade;
}

int registrarVenda(Produto *p, int quantidade) {
    if (quantidade > p->quantidade) {
        return 0; 
    }
    p->quantidade = p->quantidade - quantidade;
    return 1; 
}


int pedirCodigoExistente(Produto produtos[], int total) {
    int codigo;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);
    int pos = buscarProduto(produtos, total, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
    }
    return pos;
}


void opcaoRepor(Produto produtos[], int total) {
    int pos = pedirCodigoExistente(produtos, total);
    if (pos == -1) return;

    int qtd;
    printf("Quantidade a repor: ");
    scanf("%d", &qtd);
    if (qtd <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    reporEstoque(&produtos[pos], qtd); // manda o endereco com &
    printf("Estoque atualizado: %d unidades.\n", produtos[pos].quantidade);
}

void opcaoVenda(Produto produtos[], int total) {
    int pos = pedirCodigoExistente(produtos, total);
    if (pos == -1) return;

    int qtd;
    printf("Quantidade vendida: ");
    scanf("%d", &qtd);
    if (qtd <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    if (registrarVenda(&produtos[pos], qtd)) {
        printf("Venda registrada! Estoque agora: %d\n", produtos[pos].quantidade);
    } else {
        printf("Erro: so tem %d unidades em estoque!\n", produtos[pos].quantidade);
    }
}


void opcaoConsultar(Produto produtos[], int total) {
    int pos = pedirCodigoExistente(produtos, total);
    if (pos == -1) return;
    printf("Codigo: %d | %s | R$ %.2f | Estoque: %d\n",
           produtos[pos].codigo, produtos[pos].nome,
           produtos[pos].preco, produtos[pos].quantidade);
}


float calcularValorTotalEstoque(Produto produtos[], int total) {
    float soma = 0;
    for (int i = 0; i < total; i++) {
        soma = soma + produtos[i].preco * produtos[i].quantidade;
    }
    return soma;
}


void exibirProdutoMaiorValor(Produto produtos[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    int posMaior = 0;
    for (int i = 1; i < total; i++) {
        float valorAtual = produtos[i].preco * produtos[i].quantidade;
        float valorMaior = produtos[posMaior].preco * produtos[posMaior].quantidade;
        if (valorAtual > valorMaior) {
            posMaior = i;
        }
    }
    printf("Produto com maior valor em estoque: %s (R$ %.2f)\n",
           produtos[posMaior].nome,
           produtos[posMaior].preco * produtos[posMaior].quantidade);
}

void mostrarMenu() {
    printf("\n===== PAPELARIA =====\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Repor estoque\n");
    printf("4 - Registrar venda\n");
    printf("5 - Consultar produto pelo codigo\n");
    printf("6 - Valor total do estoque\n");
    printf("7 - Produto com maior valor em estoque\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}


int main() {
    Produto produtos[MAX_PRODUTOS];
    int total = 0;
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarProduto(produtos, &total); break;
            case 2: listarProdutos(produtos, total); break;
            case 3: opcaoRepor(produtos, total); break;
            case 4: opcaoVenda(produtos, total); break;
            case 5: opcaoConsultar(produtos, total); break;
            case 6:
                printf("Valor total em estoque: R$ %.2f\n",
                       calcularValorTotalEstoque(produtos, total));
                break;
            case 7: exibirProdutoMaiorValor(produtos, total); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}