#include "tPessoa.h"
#include <stdlib.h>
#include <string.h>

struct tPessoa{
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

};

struct tListaPessoas{
  tPessoa **pessoa;
  int qtd;
  int pacientes;
  int medicos;
  int secretarios;
};

tListaPessoas *criaListaPessoas(){
  tListaPessoas *lista = malloc(sizeof(tListaPessoas));
  lista->pessoa = NULL;
  lista->qtd = 0;
  lista->pacientes = 0;
  lista->medicos = 0;
  lista->secretarios = 0;
  return lista;
}

int verificaCPF(tListaPessoas *lista, char cargo, char *CPF){
  for(int i = 0; i < lista->qtd; i++){
    if(retornaCargo(lista->pessoa[i]) == cargo){
      if(igualCPF(CPF, lista->pessoa[i]))
        return 1;
    }
  }
  return 0;
}

int cadastraPessoa(tListaPessoas *lista, int tipo){
  char nome[100];
  char CPF[15];
  int dia, ano, mes;
  char telefone[15];
  char genero[10];
  
  printf("NOME COMPLETO: ");
  scanf("%[^\n]%*c", nome);

  printf("CPF: ");
  scanf("%[^\n]%*c", CPF);

  printf("DATA DE NASCIMENTO: ");
  scanf("%d/%d/%d%*c", &dia, &mes, &ano);

  printf("TELEFONE: ");
  scanf("%[^\n]%*c", telefone);

  printf("GENERO: ");
  scanf("%[^\n]%*c", genero);

  char usuario[20];
  char senha[20];
  char acesso[6];
  char CRM[12];
  char cargo;
  if(tipo == 1){
    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", usuario);

    printf("SENHA: ");
    scanf("%[^\n]%*c", senha);

    printf("NIVEL DE ACESSO: ");
    scanf("%[^\n]%*c", acesso);
    cargo = acesso[0];
  }
  if(tipo == 2){
    printf("CRM: ");
    scanf("%[^\n]%*c", CRM);

    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", usuario);

    printf("SENHA: ");
    scanf("%[^\n]%*c", senha);
    cargo = 'M';
  }
  if(tipo == 3)
    cargo = 'P';

  if(verificaCPF(lista, cargo, CPF)){
    printf("CPF JA EXISTENTE\n");
    return 0;
  }

  lista->qtd++;
  lista->pessoa = realloc(lista->pessoa, lista->qtd * sizeof(tPessoa*));
  tPessoa *pessoa = calloc(1, sizeof(tPessoa));
  
  
  strcpy(pessoa->nome, nome);
  strcpy(pessoa->CPF, CPF);
  pessoa->dia = dia;
  pessoa->mes = mes;
  pessoa->ano = ano;
  strcpy(pessoa->telefone, telefone);
  pessoa->genero = genero[0];
  pessoa->atendido = 0;

  if(tipo == 1){
    strcpy(pessoa->usuario, usuario);
    strcpy(pessoa->senha, senha);
    pessoa->cargo = acesso[0];
    lista->secretarios++;
    pessoa->CRM[0] = '\0';
  }
  if(tipo == 2){
    strcpy(pessoa->CRM, CRM);
    strcpy(pessoa->usuario, usuario);
    strcpy(pessoa->senha, senha);
    pessoa->cargo = 'M';
    lista->medicos++;
  }
  if(tipo == 3){
    pessoa->cargo = 'P';
    lista->pacientes++;
    pessoa->senha[0] = '\0';
    pessoa->usuario[0] = '\0';
    pessoa->CRM[0] = '\0';
  }
  lista->pessoa[lista->qtd - 1] = pessoa;
  return 1;
}

void desalocaPessoa(tPessoa *p){
  if(p != NULL)
    free(p);
}

void desalocaListaPessoas(tListaPessoas *l){
  if(l != NULL){
    for(int i = 0; i < l->qtd; i++){
      desalocaPessoa(l->pessoa[i]);
    }
    if(l->pessoa != NULL)
      free(l->pessoa);
    free(l);
  }
}

int retornaQtdPesssoas(tListaPessoas *lista){
  return lista->qtd;
}

int igualUsuario(char *usuario, tPessoa *pessoa){
  return !strcmp(usuario, pessoa->usuario);
}

int igualSenha(char *senha, tPessoa *pessoa){
  return !strcmp(senha, pessoa->senha);
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

char retornaGenero(tPessoa *pessoa){
  return pessoa->genero;
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

int retornaDia(tPessoa *pessoa){
  return pessoa->dia;
}
int retornaMes(tPessoa *pessoa){
  return pessoa->mes;
}
int retornaAno(tPessoa *pessoa){
  return pessoa->ano;
}

void atenderPessoa(tPessoa *pessoa){
  pessoa->atendido++;
}

int retornaAtendido(tPessoa *pessoa){
  return pessoa->atendido;
}


//estava calculando a idade errado
int calculaIdade(tPessoa *pessoa){
  int ano = 2023 - pessoa->ano - 1;
  if((pessoa->dia <= 9 && pessoa->mes == 11) || (pessoa->mes < 11)){
    ano++;
  }
  return ano;
}

tPessoa* retornaPessoaLista(tListaPessoas* lista, int i){
  return lista->pessoa[i];
}

void recuperaBinarioPessoas(tListaPessoas *lista, FILE *arq){
  int qtd = 0;
  fread(&qtd, sizeof(int), 1, arq);

  lista->qtd = qtd;
  lista->pessoa = realloc(lista->pessoa, lista->qtd * sizeof(tPessoa*));
  for(int i = 0; i < lista->qtd; i++){
    tPessoa *pessoa = malloc(sizeof(tPessoa));
    fread(pessoa, sizeof(tPessoa), 1, arq);
    lista->pessoa[i] = pessoa;
  }

  fclose(arq);
}

void salvaBinarioPessoas(tListaPessoas *lista, char *path){
  char diretorio[200];
  sprintf(diretorio, "%s/pessoas.bin", path);
  FILE *arq = fopen(diretorio, "wb");

  fwrite(&(lista->qtd), sizeof(int), 1, arq);

  for(int i = 0; i < lista->qtd; i++){
      fwrite(lista->pessoa[i], sizeof(tPessoa), 1, arq);
  }

  fclose(arq);
}



