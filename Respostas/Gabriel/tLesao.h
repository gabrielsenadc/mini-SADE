#ifndef _TLESAO_H_
#define _TLESAO_H_
#include <stdio.h>

typedef struct{
  char rotulo[5];
  char diagnostico[24];
  char regiao[15];
  int tamanho;
  int cirurgia;
  int crioterapia;
} tLesao;

typedef struct{
  tLesao **lesao;
  int qtd;
  int paraCirurgia;
} tListaLesao;


/**
 * Função que recebe todas as informações pertinentes a uma lesao e retorna
 * um ponteiro com a biopsia criada.
 */
tLesao* criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho, int cirurgia, int crioterapia);

/**
 * funcao que cria uma lista de lesoes, inicialmente com 0 lesoes
 */
tListaLesao *criaListaLesao();

/**
 * funcao que adiciona uma lesao a uma lista de lesoes;
 */
void adicionaListaLesao(tListaLesao *lista, tLesao *lesao);

/**
 * funcao que retorna o numero de lesoes para cirurgia
 */
int obtemNumeroLesoesParaCirurgia(tListaLesao *lista);

/**
 * funcao que retorna o numero de lesoes
 */
int obtemNumeroLesoes(tListaLesao *lista);

/**
 * funcao que retorna se a lesao eh para a cirurgia
 */
int obtemSeLesaoParaCirurgia(tLesao *lesao);

/**
 * Função que recebe o ponteiro para uma lista de lesoes e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaListaLesao(tListaLesao *lista);

/**
 * Função que recebe o ponteiro para uma lesao e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaLesao(tLesao *lesao);

/**
 * Função que recebe um ponteiro para uma lesao e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaLesao(tLesao *lesao);

/**
 * Função que recebe um ponteiro para uma lesao e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser editado.
 */
void imprimeEmArquivoLesao(tLesao *lesao, FILE * arq);

#endif