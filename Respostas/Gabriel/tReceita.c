#include "tReceita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_NOME 100

struct tReceita{
  char nomePaciente[MAX_TAM_NOME];
  eTipoUso tipoUso;
  char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
  char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
  char instrucoes[MAX_TAM_INSTRUCOES];
  int qtd;
  char nomeMedico[MAX_TAM_NOME];
  char CRM[12];
  char dataStr[11];
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
char *tipoMedicamento, char *instrucoes, int qntd,
char *nomeMedico, char *CRM, char *dataStr){
  tReceita *receita = malloc(sizeof(tReceita));
  strcpy(receita->nomePaciente, nomePaciente);
  receita->tipoUso = tipoUso;
  strcpy(receita->nomeMedicamento, nomeMedicamento);
  strcpy(receita->tipoMedicamento, tipoMedicamento);
  strcpy(receita->instrucoes, instrucoes);
  receita->qtd = qntd;
  strcpy(receita->nomeMedico, nomeMedico);
  strcpy(receita->CRM, CRM);
  strcpy(receita->dataStr, dataStr);
  return receita;
}

void desalocaReceita(void *dado){
  tReceita *r = (tReceita*) dado;
  free(r);
}

void imprimeNaTelaReceita(void *dado){
  tReceita *r = (tReceita*) dado;
  printf("RECEITUARIO\n");
  printf("NOME: %s\n\n", r->nomePaciente);
  if(r->tipoUso == ORAL)
    printf("USO ORAL\n\n");
  if(r->tipoUso == TOPICO)
    printf("USO TOPICO\n\n");
  printf("%s\n", r->nomeMedicamento);
  printf("%d %s\n\n", r->qtd, r->tipoMedicamento);
  printf("%s\n\n", r->instrucoes);
  printf("%s (%s)\n", r->nomeMedico, r->CRM);
  printf("%s\n", r->dataStr);
}

void imprimeEmArquivoReceita(void *dado, char *path){
  char *arquivo;
  sprintf(arquivo, "%s/receita.txt", path);
  FILE *arq = NULL;
  arq = fopen(arquivo, "w");

  tReceita *r = (tReceita*) dado;
  fprintf(arq, "RECEITUARIO\n");
  fprintf(arq, "NOME: %s\n\n", r->nomePaciente);
  if(r->tipoUso == ORAL)
    fprintf(arq, "USO ORAL\n\n");
  if(r->tipoUso == TOPICO)
    fprintf(arq, "USO TOPICO\n\n");
  fprintf(arq, "%s\n", r->nomeMedicamento);
  fprintf(arq, "%d %s\n\n", r->qtd, r->tipoMedicamento);
  fprintf(arq, "%s\n\n", r->instrucoes);
  fprintf(arq, "%s (%s)\n", r->nomeMedico, r->CRM);
  fprintf(arq, "%s\n", r->dataStr);
  fclose(arq);
}