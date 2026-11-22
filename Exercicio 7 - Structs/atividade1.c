/*
Desenvolva um programa que permita cadastrar 10 alunos, utilizando uma struct Aluno com os campos matrícula, nome, nota1, nota2 e média
Requisitos:
1. Cadastrar os 10 alunos.
2. Calcular a média individual por meio de uma função.
3. Exibir a situação de cada aluno: aprovado (média ≥ 6,0) ou reprovado.
4. Identificar o aluno com a maior e a menor média.
5. Calcular a média geral da turma.
6. Informar quantos alunos ficaram acima da média geral.
*/

#include <stdio.h>
#define TOTAL_ALUNOS 10

typedef struct {
    int matricula;
    char nome[50];
    float nota1;
    float nota2;
    float media;
} Aluno;

float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2;
}

float lerNota(const char *texto) {
    float nota;
    printf("%s", texto);
    scanf("%f", &nota);
    while (nota < 0 || nota > 10) {
        printf("Nota invalida! Digite um valor de 0 a 10: ");
        scanf("%f", &nota);
    }
    return nota;
}

void cadastrarAlunos(Aluno alunos[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Aluno %d de %d ---\n", i + 1, quantidade);
        printf("Matricula: ");
        scanf("%d", &alunos[i].matricula);
        printf("Nome: ");
        scanf(" %[^\n]", alunos[i].nome);
        alunos[i].nota1 = lerNota("Nota 1: ");
        alunos[i].nota2 = lerNota("Nota 2: ");

        alunos[i].media = calcularMedia(alunos[i].nota1, alunos[i].nota2);
    }
}

void exibirSituacao(Aluno alunos[], int quantidade) {
    printf("\n===== SITUACAO DOS ALUNOS =====\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s | Media: %.1f | ", alunos[i].matricula, alunos[i].nome, alunos[i].media);
        if (alunos[i].media >= 6.0) {
            printf("APROVADO\n");
        } else {
            printf("REPROVADO\n");
        }
    }
}

void exibirMaiorEMenorMedia(Aluno alunos[], int quantidade) {
    int posMaior = 0; 
    int posMenor = 0; 

    for (int i = 1; i < quantidade; i++) {
        if (alunos[i].media > alunos[posMaior].media) {
            posMaior = i;
        }
        if (alunos[i].media < alunos[posMenor].media) {
            posMenor = i;
        }
    }

    printf("\nMaior media: %s (%.1f)\n", alunos[posMaior].nome, alunos[posMaior].media);
    printf("Menor media: %s (%.1f)\n", alunos[posMenor].nome, alunos[posMenor].media);
}

float calcularMediaGeral(Aluno alunos[], int quantidade) {
    float soma = 0;
    for (int i = 0; i < quantidade; i++) {
        soma = soma + alunos[i].media;
    }
    return soma / quantidade;
}

int contarAcimaDaMedia(Aluno alunos[], int quantidade, float mediaGeral) {
    int contador = 0;
    for (int i = 0; i < quantidade; i++) {
        if (alunos[i].media > mediaGeral) {
            contador++;
        }
    }
    return contador;
}

int main() {
    Aluno alunos[TOTAL_ALUNOS];

    cadastrarAlunos(alunos, TOTAL_ALUNOS);
    exibirSituacao(alunos, TOTAL_ALUNOS);
    exibirMaiorEMenorMedia(alunos, TOTAL_ALUNOS);

    float mediaGeral = calcularMediaGeral(alunos, TOTAL_ALUNOS);
    printf("\nMedia geral da turma: %.1f\n", mediaGeral);

    int acima = contarAcimaDaMedia(alunos, TOTAL_ALUNOS, mediaGeral);
    printf("Alunos acima da media geral: %d\n", acima);

    return 0;
}