/*
Desenvolva um programa que utilize as estruturas Data, Paciente e Consulta.
A estrutura Consulta deverá conter os dados do paciente, a data da consulta e uma descrição do atendimento.

Requisitos:
1. Cadastrar até 15 pacientes.
2. Registrar até 30 consultas.
3. Pesquisar as consultas de um paciente pelo código.
4. Listar consultas realizadas em determinada data.
5. Contabilizar o número de consultas por paciente.
6. Identificar o paciente com maior número de atendimentos.
*/

#include <stdio.h>
#define MAX_PACIENTES 15
#define MAX_CONSULTAS 30

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int codigo;
    char nome[50];
    int idade;
} Paciente;

typedef struct {
    Paciente paciente;
    Data data;
    char descricao[100];
} Consulta;

int buscarPaciente(Paciente pacientes[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (pacientes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

Data lerData() {
    Data d;
    printf("Data (dia mes ano, ex: 22 11 2026): ");
    scanf("%d %d %d", &d.dia, &d.mes, &d.ano);
    while (d.dia < 1 || d.dia > 31 || d.mes < 1 || d.mes > 12 || d.ano < 1900) {
        printf("Data invalida! Digite de novo (dia mes ano): ");
        scanf("%d %d %d", &d.dia, &d.mes, &d.ano);
    }
    return d;
}

int datasIguais(Data a, Data b) {
    return a.dia == b.dia && a.mes == b.mes && a.ano == b.ano;
}

void cadastrarPaciente(Paciente pacientes[], int *total) {
    if (*total >= MAX_PACIENTES) {
        printf("Limite de %d pacientes atingido!\n", MAX_PACIENTES);
        return;
    }
    Paciente novo;
    printf("Codigo: ");
    scanf("%d", &novo.codigo);
    if (buscarPaciente(pacientes, *total, novo.codigo) != -1) {
        printf("Erro: codigo ja cadastrado!\n");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Idade: ");
    scanf("%d", &novo.idade);
    if (novo.idade < 0) {
        printf("Erro: idade invalida!\n");
        return;
    }
    pacientes[*total] = novo;
    (*total)++;
    printf("Paciente cadastrado!\n");
}

void registrarConsulta(Paciente pacientes[], int totalPacientes, Consulta consultas[], int *totalConsultas) {
    if (*totalConsultas >= MAX_CONSULTAS) {
        printf("Limite de %d consultas atingido!\n", MAX_CONSULTAS);
        return;
    }
    int codigo;
    printf("Codigo do paciente: ");
    scanf("%d", &codigo);
    int pos = buscarPaciente(pacientes, totalPacientes, codigo);
    if (pos == -1) {
        printf("Paciente nao cadastrado!\n");
        return;
    }

    Consulta nova;
    nova.paciente = pacientes[pos];
    nova.data = lerData();
    printf("Descricao do atendimento: ");
    scanf(" %[^\n]", nova.descricao);

    consultas[*totalConsultas] = nova;
    (*totalConsultas)++;
    printf("Consulta registrada!\n");
}

void mostrarConsulta(Consulta c) {
    printf("%02d/%02d/%d | %s | %s\n",
           c.data.dia, c.data.mes, c.data.ano, c.paciente.nome, c.descricao);
}

void pesquisarPorPaciente(Consulta consultas[], int totalConsultas) {
    int codigo, achou = 0;
    printf("Codigo do paciente: ");
    scanf("%d", &codigo);
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].paciente.codigo == codigo) {
            mostrarConsulta(consultas[i]);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhuma consulta encontrada para esse paciente.\n");
    }
}

void listarPorData(Consulta consultas[], int totalConsultas) {
    Data procurada = lerData();
    int achou = 0;
    for (int i = 0; i < totalConsultas; i++) {
        if (datasIguais(consultas[i].data, procurada)) {
            mostrarConsulta(consultas[i]);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhuma consulta nessa data.\n");
    }
}

int contarConsultas(Consulta consultas[], int totalConsultas, int codigo) {
    int contador = 0;
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].paciente.codigo == codigo) {
            contador++;
        }
    }
    return contador;
}

void exibirConsultasPorPaciente(Paciente pacientes[], int totalPacientes, Consulta consultas[], int totalConsultas) {
    if (totalPacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalPacientes; i++) {
        printf("%s: %d consulta(s)\n", pacientes[i].nome,
               contarConsultas(consultas, totalConsultas, pacientes[i].codigo));
    }
}

void exibirPacienteMaisAtendido(Paciente pacientes[], int totalPacientes, Consulta consultas[], int totalConsultas) {
    if (totalConsultas == 0) {
        printf("Nenhuma consulta registrada.\n");
        return;
    }
    int posMaior = 0;
    int maior = contarConsultas(consultas, totalConsultas, pacientes[0].codigo);
    for (int i = 1; i < totalPacientes; i++) {
        int atual = contarConsultas(consultas, totalConsultas, pacientes[i].codigo);
        if (atual > maior) {
            maior = atual;
            posMaior = i;
        }
    }
    printf("Paciente com mais atendimentos: %s (%d consultas)\n", pacientes[posMaior].nome, maior);
}

void mostrarMenu() {
    printf("\n===== CLINICA =====\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Registrar consulta\n");
    printf("3 - Pesquisar consultas de um paciente\n");
    printf("4 - Listar consultas de uma data\n");
    printf("5 - Numero de consultas por paciente\n");
    printf("6 - Paciente com mais atendimentos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int main() {
    Paciente pacientes[MAX_PACIENTES];
    Consulta consultas[MAX_CONSULTAS];
    int totalPacientes = 0, totalConsultas = 0;
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrarPaciente(pacientes, &totalPacientes); break;
            case 2: registrarConsulta(pacientes, totalPacientes, consultas, &totalConsultas); break;
            case 3: pesquisarPorPaciente(consultas, totalConsultas); break;
            case 4: listarPorData(consultas, totalConsultas); break;
            case 5: exibirConsultasPorPaciente(pacientes, totalPacientes, consultas, totalConsultas); break;
            case 6: exibirPacienteMaisAtendido(pacientes, totalPacientes, consultas, totalConsultas); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}