#include "tPessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tListaPessoas *criaListaPessoas(){
  tListaPessoas *lista = malloc(sizeof(tListaPessoas));
  lista->pessoa = NULL;
  lista->qtd = 0;
  return lista;
}

void cadastraPessoa(tListaPessoas *lista, int tipo){
  lista->qtd++;
  lista->pessoa = realloc(lista->pessoa, lista->qtd * sizeof(tPessoa*));
  tPessoa *pessoa = malloc(sizeof(tPessoa));
  
  char nome[100];
  char CPF[15];
  int dia, ano, mes;
  char telefone[15];
  char genero[10];
  
  printf("NOME COMPLETO: ");
  scanf("%[^\n]%*c", nome);
  strcpy(pessoa->nome, nome);

  printf("CPF: ");
  scanf("%[^\n]%*c", CPF);
  strcpy(pessoa->CPF, CPF);

  printf("DATA DE NASCIMENTO: ");
  scanf("%d/%d/%d%*c", &dia, &mes, &ano);
  pessoa->dia = dia;
  pessoa->mes = mes;
  pessoa->ano = ano;

  printf("TELEFONE: ");
  scanf("%[^\n]%*c", telefone);
  strcpy(pessoa->telefone, telefone);

  printf("GENERO: ");
  scanf("%[^\n]%*c", genero);
  strcpy(pessoa->genero, genero);

  if(tipo == 1){
    char usuario[20];
    char senha[20];
    char acesso[6];
    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", usuario);
    strcpy(pessoa->usuario, usuario);

    printf("SENHA: ");
    scanf("%[^\n]%*c", senha);
    strcpy(pessoa->senha, senha);

    printf("NIVEL DE ACESSO: ");
    scanf("%[^\n]%*c", acesso);
    pessoa->acesso = acesso[0];

    pessoa->cargo = 'S';
  }
  if(tipo == 2){
    char usuario[20];
    char senha[20];
    char CRM[12];

    printf("CRM: ");
    scanf("%[^\n]%*c", CRM);
    strcpy(pessoa->CRM, CRM);

    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", usuario);
    strcpy(pessoa->usuario, usuario);

    printf("SENHA: ");
    scanf("%[^\n]%*c", senha);
    strcpy(pessoa->senha, senha);

    pessoa->cargo = 'M';
  }
  if(tipo == 3)
    pessoa->cargo = 'P';

  lista->pessoa[lista->qtd - 1] = pessoa;
}

void desalocaPessoa(tPessoa *p){
  if(p != NULL)
    free(p);
}

void desalocaLista(tListaPessoas *l){
  if(l != NULL){
    for(int i = 0; i < l->qtd; i++){
      desalocaPessoa(l->pessoa[i]);
    }
    if(l->pessoa != NULL)
      free(l->pessoa);
    free(l);
  }
}

int igualNome(char *nome, tPessoa *pessoa){
  return !(strcmp(nome, pessoa->nome));
}

int igualCPF(char *CPF, tPessoa *pessoa){
  return !(strcmp(CPF, pessoa->CPF));
}

char* retornaNome(tPessoa *pessoa){
  char *nome = pessoa->nome;
  return nome;
}

char* retornaCPF(tPessoa *pessoa){
  char *cpf = pessoa->CPF;
  return cpf;
}

char* retornaTelefone(tPessoa *pessoa){
  char *telefone = pessoa->telefone;
  return telefone;
}

char* retornaGenero(tPessoa *pessoa){
  char *genero = pessoa->genero;
  return genero;
}

char retornaCargo(tPessoa *pessoa){
  return pessoa->cargo;
}

char* retornaUsuario(tPessoa *pessoa){
  char *usuario = pessoa->usuario;
  return usuario;
}

char* retornaSenha(tPessoa *pessoa){
  char *senha = pessoa->senha;
  return senha;
}

char* retornaCRM(tPessoa *pessoa){
  char *CRM = pessoa->CRM;
  return CRM;
}

char retornaAcesso(tPessoa *pessoa){
  return pessoa->acesso;
}

int retornaDia(tPessoa *pessoa){
  return pessoa->dia;
}
int retornaMes(tPessoa *pessoa){
  return pessoa->mes;
}
int retornaAno(tPessoa *pessoa){
  return pessoa->ano;
}
