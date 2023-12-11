#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tPessoa.h"
#include "tLesao.h"
#include "tFila.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"

typedef struct tConsulta tConsulta;

typedef struct tListaConsulta tListaConsulta;

tListaConsulta* criaListaConsulta();

void adicionaListaConsulta(tListaConsulta *lista, tConsulta *consulta);

void desalocaListaConsulta(tListaConsulta *lista);

void desalocaConsulta(tConsulta *c);

int retornaQtdConsulta(tListaConsulta *lista);

int retornaQtdLesoesConsultas(tListaConsulta *lista);

int retornaTamanhoLesoesConsultas(tListaConsulta *lista);

int retornaQtdLesoesParaCirurgiaConsultas(tListaConsulta *lista);

int retornaQtdLesoesParaCrioterapiaConsultas(tListaConsulta *lista);

tPessoa* pacienteCadastrado(char *CPF, tListaPessoas *lista);

void cadastraLesao(tListaLesao *lista);

void cadastraReceita(tFila *fila, char *nomePaciente, char *nomeMedico, char *CRM, char *dataStr);

void solicitaBiopsia(tFila *fila, tListaLesao *lista, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data);

void encaminhamento(tFila *fila, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data);

void RealizaConsulta(tFila *fila, tListaPessoas *listaPessoas, char *nomeMedico, char *CRM, tListaConsulta *listaConsulta);

void salvaConsultasBinario(tListaConsulta *lista, char *path);

void recuperaConsultasBinario(tListaConsulta *lista, char *path);

tConsulta* retornaConsultaLista(tListaConsulta *lista, int i);

#endif