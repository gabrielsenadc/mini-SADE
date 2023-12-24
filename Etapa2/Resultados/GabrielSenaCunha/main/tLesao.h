#ifndef _TLESAO_H_
#define _TLESAO_H_
#include <stdio.h>

typedef struct tLesao tLesao;

typedef struct tListaLesao tListaLesao;

tLesao* criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho, int cirurgia, int crioterapia);

tListaLesao *criaListaLesao();

/**
 * adiciona uma lesao na lista
 */
void adicionaListaLesao(tListaLesao *lista, tLesao *lesao);

/**
 * retorna numero de lesoes para cirurgia em uma lista de lesoes
 */
int retornaNumeroLesoesParaCirurgia(tListaLesao *lista);

/**
 * retorna numero de lesoes para a crioterapia em uma lista de lesoes
 */
int retornaNumeroLesoesParaCrioterapia(tListaLesao *lista);

/**
 * retorna a soma de todos os tamanhos de lesoes
 */
int retornaTamanhoLesoesLista(tListaLesao *lista);

int retornaNumeroLesoes(tListaLesao *lista);

int retornaSeLesaoParaCirurgia(tLesao *lesao);

void desalocaListaLesao(tListaLesao *lista);

void desalocaLesao(tLesao *lesao);

void imprimeNaTelaLesao(tLesao *lesao);

void imprimeEmArquivoLesao(tLesao *lesao, FILE * arq);

void salvaBinarioLesoes(tListaLesao *lista, FILE * arq);

/**
 * retorna uma lista de lesoes de uma consulta, recuperada no banco de dados
 */
tListaLesao* recuperaLesoesBinario(FILE * arq, int qtd);

/**
 * retorna a lesao na posicao "i" da lista
 */
tLesao* retornaLesaoLista(tListaLesao *lista, int i);

void PrintaListaLesao(tListaLesao *lista, FILE *arq);

#endif