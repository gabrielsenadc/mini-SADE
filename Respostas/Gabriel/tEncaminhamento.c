#include "tEncaminhamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_NOME 100

struct tEncaminhamento{
    char nomePaciente[MAX_TAM_NOME];
    char CPF[15];
    char especialidade[50]; 
    char motivo[300]; 
    char nomeMedico[MAX_TAM_NOME]; 
    char CRM[12]; 
    char data[11];
};

tEncaminhamento *criaEncaminhamento(char *nomePaciente, char *CPF, char *especialidade, char *motivo, char *nomeMedico, char *CRM, char *data){
    tEncaminhamento *e = malloc(sizeof(tEncaminhamento));

    strcpy(e->nomePaciente, nomePaciente);
    strcpy(e->CPF, CPF);
    strcpy(e->especialidade, especialidade);
    strcpy(e->motivo, motivo);
    strcpy(e->nomeMedico, nomeMedico);
    strcpy(e->CRM, CRM);
    strcpy(e->data, data);

    return e;
}

void desalocaEncaminhamento(void *dado){
    if(dado != NULL){
        tEncaminhamento *e = (tEncaminhamento*) dado;
        free(e);
    }
}

void imprimeNaTelaEncaminhamento(void *dado){
    tEncaminhamento *e = (tEncaminhamento*) dado;

    printf("PACIENTE: %s\n", e->nomePaciente);
    printf("CPF: %s\n\n", e->CPF);
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    printf("MOTIVO: %s\n\n", e->motivo);
    printf("%s (%s)\n", e->nomeMedico, e->CRM);
    printf("%s\n", e->data);
}

void imprimeEmArquivoEncaminhamento(void *dado, char *path){
    char arquivo[100];
    sprintf(arquivo, "%s/encaminhamento.txt", path);
    FILE *arq = NULL;
    arq = fopen(arquivo, "a");
    tEncaminhamento *e = (tEncaminhamento*) dado;

    fprintf(arq, "PACIENTE: %s\n", e->nomePaciente);
    fprintf(arq, "CPF: %s\n\n", e->CPF);
    fprintf(arq, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    fprintf(arq, "MOTIVO: %s\n\n", e->motivo);
    fprintf(arq, "%s (%s)\n", e->nomeMedico, e->CRM);
    fprintf(arq, "%s\n", e->data);

    fclose(arq);
}