#include "tBiopsia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_NOME 100

struct tBiopsia{
  char nomePaciente[MAX_TAM_NOME];
  char CPF[15];
  tListaLesao *lista;
  char nomeMedico[MAX_TAM_NOME];
  char CRM[12];
  char data[11];
};

tBiopsia *criaBiopsia(char *nomePaciente, char *CPF, tListaLesao *lista, char *nomeMedico, char *CRM, char *data){
  tBiopsia *b = malloc(sizeof(tBiopsia));
  strcpy(b->nomePaciente, nomePaciente);
  strcpy(b->CPF, CPF);
  b->lista = lista;
  strcpy(b->nomeMedico, nomeMedico);
  strcpy(b->CRM, CRM);
  strcpy(b->data, data);
  return b;
}

void desalocaBiopsia(void *dado){
  if(dado != NULL){
    tBiopsia *b = (tBiopsia*) dado;
    free(b);
  }
}

void imprimeNaTelaBiopsia(void *dado){
  tBiopsia *b = (tBiopsia*) dado;
  printf("PACIENTE: %s\n", b->nomePaciente);
  printf("CPF: %s\n\n", b->CPF);
  printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
  for(int i = 0; i < obtemNumeroLesoes(b->lista); i++){
    if(obtemSeLesaoParaCirurgia(b->lista->lesao[i]))
      imprimeNaTelaLesao(b->lista->lesao[i]);
  }
  printf("\n%s (%s)\n", b->nomeMedico, b->CRM);
  printf("%s\n", b->data);
}

void imprimeEmArquivoBiopsia(void *dado, char *path){
  char arquivo[100];
  sprintf(arquivo, "%s/biopsia.txt", path);
  FILE *arq = NULL;
  arq = fopen(arquivo, "a");
  tBiopsia *b = (tBiopsia*) dado;

  fprintf(arq, "PACIENTE: %s\n", b->nomePaciente);
  fprintf(arq, "CPF: %s\n\n", b->CPF);
  fprintf(arq, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
  for(int i = 0; i < obtemNumeroLesoes(b->lista); i++){
    if(obtemSeLesaoParaCirurgia(b->lista->lesao[i]))
      imprimeEmArquivoLesao(b->lista->lesao[i], arq);
  }
  fprintf(arq, "\n%s (%s)\n", b->nomeMedico, b->CRM);
  fprintf(arq, "%s\n\n", b->data);

  fclose(arq);
}