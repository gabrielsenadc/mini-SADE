#ifndef _TPESSOA_H_
#define _TPESSOA_H_
#include <stdio.h>

typedef struct tPessoa tPessoa;

typedef struct tListaPessoas tListaPessoas;

tListaPessoas *criaListaPessoas();

int cadastraPessoa(tListaPessoas *lista, int tipo);

int igualNome(char *nome, tPessoa *pessoa);

int igualCPF(char *CPF, tPessoa *pessoa);

int igualUsuario(char *usuario, tPessoa *pessoa);

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

//aumenta a qtd de vezes que a pessoa foi atendida
void atenderPessoa(tPessoa *pessoa);

//retiorna se a ṕessoa foi atendida
int retornaAtendido(tPessoa *pessoa);

int calculaIdade(tPessoa *pessoa);

tPessoa* retornaPessoaLista(tListaPessoas* lista, int i);

void recuperaBinarioPessoas(tListaPessoas *lista, FILE *arq);

void salvaBinarioPessoas(tListaPessoas *lista, char *path);

#endif