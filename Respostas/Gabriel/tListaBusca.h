#ifndef _TLISTABUSCA_H_
#define _TLISTABUSCA_H_

typedef struct tListaBusca tListaBusca;

#include "tPessoa.h"

/**
 * funcao que cria um a lista de busca como NULL e qtd como 0
 */
tListaBusca *criaListaBusca();

/**
 * funcao que adiciona uma pessioa a lista
 */
void adicionaPessoaListaBusca(tListaBusca *lista, tPessoa *pessoa);

/**
 * funcao que desaloca uma pessoa
 */
void desalocaPessoa(tPessoa *p);

/**
 * Função que recebe o ponteiro genérico (que deve conter uma Lista de Busca) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaListaBusca(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter uma Lista dec Busca) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaListaBusca(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter uma Lista de Busca) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoListaBusca(void *dado, char *path);

#endif