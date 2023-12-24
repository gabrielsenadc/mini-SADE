#ifndef _TPESSOA_H_
#define _TPESSOA_H_
#include <stdio.h>

typedef struct tPessoa tPessoa;

typedef struct tListaPessoas tListaPessoas;

tListaPessoas *criaListaPessoas();

int cadastraPessoa(tListaPessoas *lista, int tipo);

/**
 * verifica se a pessoa tem o mesmo nome que o passado em parametro
 */
int igualNome(char *nome, tPessoa *pessoa);

/**
 * verifica se a pessoa tem o mesmo CPF que o passado em parametro
 */
int igualCPF(char *CPF, tPessoa *pessoa);

/**
 * verifica se a pessoa tem o mesmo usuario que o passado em parametro
 */
int igualUsuario(char *usuario, tPessoa *pessoa);

/**
 * verifica se a pessoa tem a mesma senha que a passado em parametro
 */
int igualSenha(char *senha, tPessoa *pessoa);

void desalocaPessoa(tPessoa *p);

void desalocaListaPessoas(tListaPessoas *l);

int retornaQtdPesssoas(tListaPessoas *lista);

char* retornaNome(tPessoa *pessoa);

char* retornaCPF(tPessoa *pessoa);

char* retornaTelefone(tPessoa *pessoa);

char retornaGenero(tPessoa *pessoa);

char retornaCargo(tPessoa *pessoa);

char* retornaUsuario(tPessoa *pessoa);

char* retornaSenha(tPessoa *pessoa);

char* retornaCRM(tPessoa *pessoa);

int retornaDia(tPessoa *pessoa);

int retornaMes(tPessoa *pessoa);

int retornaAno(tPessoa *pessoa);

/**
 * aumenta a qtd de vezes que a pessoa foi atendida
 */
void atenderPessoa(tPessoa *pessoa);

/**
 * retorna se a ṕessoa foi atendida
 */
int retornaAtendido(tPessoa *pessoa);

int calculaIdade(tPessoa *pessoa);

/**
 * retorna a pessoa na posicao "i" da lista
 */
tPessoa* retornaPessoaLista(tListaPessoas* lista, int i);

void recuperaBinarioPessoas(tListaPessoas *lista, FILE *arq);

void recuperaInicio(tListaPessoas *lista, FILE *arq);

void salvaBinarioPessoas(tListaPessoas *lista, char *path);

void printaMedicos(tListaPessoas *lista, char *path);

void printaSecretarios(tListaPessoas *lista, char *path);


#endif