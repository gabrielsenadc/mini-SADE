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

/**
 * adiciona uma consulta na lista
 */
void adicionaListaConsulta(tListaConsulta *lista, tConsulta *consulta);

void desalocaListaConsulta(tListaConsulta *lista);

void desalocaConsulta(tConsulta *c);

int retornaQtdConsulta(tListaConsulta *lista);

int retornaQtdLesoesConsultas(tListaConsulta *lista);

int retornaTamanhoLesoesConsultas(tListaConsulta *lista);

int retornaQtdLesoesParaCirurgiaConsultas(tListaConsulta *lista);

int retornaQtdLesoesParaCrioterapiaConsultas(tListaConsulta *lista);

/**
 * retorna o paciente com o CPF passado por parametro, se nao tiver im paciente com esse, CPF retorna NULL
 */
tPessoa* pacienteCadastrado(char *CPF, tListaPessoas *lista);

/**
 * cadastra uma lesao durante a consulta
 */
void cadastraLesao(tListaLesao *lista);

/**
 * cadastra uma receita e manda para a fila de impressao
 */
void cadastraReceita(tFila *fila, char *nomePaciente, char *nomeMedico, char *CRM, char *dataStr);

/**
 * retorna 1 caso tenha mandado um biopsia para a fila de impressao; retorna 0 caso nao tenha conseguido
 */
int solicitaBiopsia(tFila *fila, tListaLesao *lista, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data);

/**
 * cadastra um encaminhamento e manda para a fila de impressao
 */
void encaminhamento(tFila *fila, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data);

void RealizaConsulta(tFila *fila, tListaPessoas *listaPessoas, char *nomeMedico, char *CRM, tListaConsulta *listaConsulta);

void salvaConsultasBinario(tListaConsulta *lista, char *path);

void recuperaConsultasBinario(tListaConsulta *lista, char *path);

/**
 * retorna a consulta na posicao "i" da lista
 */
tConsulta* retornaConsultaLista(tListaConsulta *lista, int i);

#endif