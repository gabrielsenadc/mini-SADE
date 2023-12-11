#ifndef _TLESAO_H_
#define _TLESAO_H_
#include <stdio.h>

typedef struct tLesao tLesao;

typedef struct tListaLesao tListaLesao;

tLesao* criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho, int cirurgia, int crioterapia);

tListaLesao *criaListaLesao();

void adicionaListaLesao(tListaLesao *lista, tLesao *lesao);

int obtemNumeroLesoesParaCirurgia(tListaLesao *lista);

int obtemNumeroLesoesParaCrioterapia(tListaLesao *lista);

int obtemTamanhoLesoesLista(tListaLesao *lista);

int obtemNumeroLesoes(tListaLesao *lista);

int obtemSeLesaoParaCirurgia(tLesao *lesao);

void desalocaListaLesao(tListaLesao *lista);

void desalocaLesao(tLesao *lesao);

void imprimeNaTelaLesao(tLesao *lesao);

void imprimeEmArquivoLesao(tLesao *lesao, FILE * arq);

void salvaBinarioLesoes(tListaLesao *lista, FILE * arq);

tListaLesao* recuperaLesaoBinario(FILE * arq, int qtd);

tLesao* retornaLesaoLista(tListaLesao *lista, int i);

#endif