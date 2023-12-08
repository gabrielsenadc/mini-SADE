#ifndef _TPESSOA_H_
#define _TPESSOA_H_
#include <stdio.h>

typedef struct {
  char nome[100];
  char CPF[15];
  int dia, mes, ano;
  char telefone[15];
  char genero;

  char cargo;
  
  char usuario[20];
  char senha[20];

  char CRM[12];

  int atendido;

} tPessoa;

typedef struct {
  tPessoa **pessoa;
  int qtd;
  int pacientes;
  int medicos;
  int secretarios;
} tListaPessoas;

tListaPessoas *criaListaPessoas();

int cadastraPessoa(tListaPessoas *lista, int tipo);

int igualNome(char *nome, tPessoa *pessoa);

int igualCPF(char *CPF, tPessoa *pessoa);

int igualUsuario(char *usuario, tPessoa *pessoa);

int igualSenha(char *senha, tPessoa *pessoa);

void desalocaPessoa(tPessoa *p);

void desalocaLista(tListaPessoas *l);

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

void atenderPessoa(tPessoa *pessoa);

int retornaAtendido(tPessoa *pessoa);

int calculaIdade(tPessoa *pessoa);

tPessoa* retornaPessoaLista(tListaPessoas* lista, int i);

void salvaBinarioPacientes(tListaPessoas *lista, char *path);

void salvaBinarioMedicos(tListaPessoas *lista, char *path);

void salvaBinarioSecretarios(tListaPessoas *lista, char *path);

void recuperaBinarioPessoas(tListaPessoas *lista, FILE *arq);

void salvaBinarioPessoas(tListaPessoas *lista, char *path);
#endif