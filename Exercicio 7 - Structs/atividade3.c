/*
Desenvolva um sistema para cadastrar até 8 funcionários, armazenando código, nome, cargo, salário-base e quantidade de horas extras.

Requisitos:
1. Calcular o valor da hora considerando 160 horas mensais.
2. Calcular cada hora extra com acréscimo de 50%.
3. Calcular o salário bruto.
4. Aplicar um desconto fictício de 10% sobre o salário bruto.
5. Exibir o salário líquido de cada funcionário.
6. Identificar o maior salário líquido e o custo total da folha.
*/

#include <stdio.h>

#define MAX_FUNCIONARIOS 8
#define HORAS_MENSAIS 160
#define DESCONTO 0.10   // 10%

typedef struct {
    int codigo;
    char nome[50];
    char cargo[30];
    float salarioBase;
    int horasExtras;
    float salarioBruto;
    float salarioLiquido;
} Funcionario;


float calcularValorHora(float salarioBase) {
    return salarioBase / HORAS_MENSAIS;
}

float calcularHorasExtras(float salarioBase, int horasExtras) {
    float valorHoraExtra = calcularValorHora(salarioBase) * 1.5;
    return valorHoraExtra * horasExtras;
}

float calcularSalarioBruto(float salarioBase, int horasExtras) {
    return salarioBase + calcularHorasExtras(salarioBase, horasExtras);
}

float calcularSalarioLiquido(float salarioBruto) {
    return salarioBruto - (salarioBruto * DESCONTO);
}

int lerQuantidade() {
    int qtd;
    printf("Quantos funcionarios deseja cadastrar (1 a %d)? ", MAX_FUNCIONARIOS);
    scanf("%d", &qtd);
    while (qtd < 1 || qtd > MAX_FUNCIONARIOS) {
        printf("Valor invalido! Digite de 1 a %d: ", MAX_FUNCIONARIOS);
        scanf("%d", &qtd);
    }
    return qtd;
}


void cadastrarFuncionarios(Funcionario f[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Funcionario %d ---\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &f[i].codigo);
        printf("Nome: ");
        scanf(" %[^\n]", f[i].nome);
        printf("Cargo: ");
        scanf(" %[^\n]", f[i].cargo);
        printf("Salario base: ");
        scanf("%f", &f[i].salarioBase);
        printf("Horas extras: ");
        scanf("%d", &f[i].horasExtras);

        if (f[i].salarioBase < 0 || f[i].horasExtras < 0) {
            printf("Valores negativos nao sao permitidos. Digite este funcionario de novo.\n");
            i--; 
            continue;
        }

        f[i].salarioBruto = calcularSalarioBruto(f[i].salarioBase, f[i].horasExtras);
        f[i].salarioLiquido = calcularSalarioLiquido(f[i].salarioBruto);
    }
}


void exibirFuncionarios(Funcionario f[], int qtd) {
    printf("\n===== FOLHA DE PAGAMENTO =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s (%s)\n", f[i].codigo, f[i].nome, f[i].cargo);
        printf("   Valor da hora: R$ %.2f\n", calcularValorHora(f[i].salarioBase));
        printf("   Horas extras:  R$ %.2f\n", calcularHorasExtras(f[i].salarioBase, f[i].horasExtras));
        printf("   Bruto:         R$ %.2f\n", f[i].salarioBruto);
        printf("   Desconto 10%%:  R$ %.2f\n", f[i].salarioBruto * DESCONTO);
        printf("   LIQUIDO:       R$ %.2f\n", f[i].salarioLiquido);
    }
}

void exibirMaiorSalario(Funcionario f[], int qtd) {
    int posMaior = 0;
    for (int i = 1; i < qtd; i++) {
        if (f[i].salarioLiquido > f[posMaior].salarioLiquido) {
            posMaior = i;
        }
    }
    printf("\nMaior salario liquido: %s (R$ %.2f)\n", f[posMaior].nome, f[posMaior].salarioLiquido);
}

float calcularCustoFolha(Funcionario f[], int qtd) {
    float soma = 0;
    for (int i = 0; i < qtd; i++) {
        soma = soma + f[i].salarioBruto;
    }
    return soma;
}

int main() {
    Funcionario funcionarios[MAX_FUNCIONARIOS];

    int qtd = lerQuantidade();
    cadastrarFuncionarios(funcionarios, qtd);
    exibirFuncionarios(funcionarios, qtd);
    exibirMaiorSalario(funcionarios, qtd);
    printf("Custo total da folha (soma dos brutos): R$ %.2f\n", calcularCustoFolha(funcionarios, qtd));

    return 0;
}