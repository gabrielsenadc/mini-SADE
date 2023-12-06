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
  char data[11];
  char telefone[15];
  char genero[10];
  
  printf("NOME COMPLETO: ");
  scanf("%[^\n]%*c", nome);
  strcpy(pessoa->nome, nome);

  printf("CPF: ");
  scanf("%[^\n]%*c", CPF);
  strcpy(pessoa->CPF, CPF);

  printf("DATA DE NASCIMENTO: ");
  scanf("%[^\n]%*c", data);
  strcpy(pessoa->data, data);

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
  }

  lista->pessoa[lista->qtd - 1] = pessoa;
}

int igualNome(char *nome, tPessoa *pessoa){
  return !(strcmp(nome, pessoa->nome));
}

char* retornaNome(tPessoa *pessoa){
  char *nome = pessoa->nome;
  return nome;
}

char* retornaCPF(tPessoa *pessoa){
  char *cpf = pessoa->CPF;
  return cpf;
}

char* retornaData(tPessoa *pessoa){
  char *data = pessoa->data;
  return data;
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