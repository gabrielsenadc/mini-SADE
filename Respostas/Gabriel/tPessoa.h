#ifndef _TPESSOA_H_
#define _TPESSOA_H_

typedef struct {
  char nome[100];
  char CPF[15];
  int dia, mes, ano;
  char telefone[15];
  char genero[10];

  char cargo;

  char usuario[20];
  char senha[20];

  char CRM[12];

} tPessoa;

typedef struct {
  tPessoa **pessoa;
  int qtd;
} tListaPessoas;

tListaPessoas *criaListaPessoas();

void cadastraPessoa(tListaPessoas *lista, int tipo);

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

char* retornaGenero(tPessoa *pessoa);

char retornaCargo(tPessoa *pessoa);

char* retornaUsuario(tPessoa *pessoa);

char* retornaSenha(tPessoa *pessoa);

char* retornaCRM(tPessoa *pessoa);

int retornaDia(tPessoa *pessoa);
int retornaMes(tPessoa *pessoa);
int retornaAno(tPessoa *pessoa);




#endif