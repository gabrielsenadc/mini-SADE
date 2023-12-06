#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct {
  char nome[100];
  char CPF[15];
  char data[11];
  char telefone[15];
  char genero[10];

  char cargo;

  char usuario[20];
  char senha[20];

  char CRM[12];

  char acesso;
} tPessoa;

typedef struct {
  tPessoa **pessoa;
  int qtd;
} tListaPessoas;

tListaPessoas *criaListaPessoas();

void cadastraPessoa(tListaPessoas *lista, int tipo);

int igualNome(char *nome, tPessoa *pessoa);

char* retornaNome(tPessoa *pessoa);

char* retornaCPF(tPessoa *pessoa);

char* retornaData(tPessoa *pessoa);

char* retornaTelefone(tPessoa *pessoa);

char* retornaGenero(tPessoa *pessoa);

char retornaCargo(tPessoa *pessoa);

char* retornaUsuario(tPessoa *pessoa);

char* retornaSenha(tPessoa *pessoa);

char* retornaCRM(tPessoa *pessoa);

char retornaAcesso(tPessoa *pessoa);



#endif