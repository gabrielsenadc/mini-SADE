#include "tLesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tLesao{
  char rotulo[5];
  char diagnostico[24];
  char regiao[15];
  int tamanho;
  int cirurgia;
  int crioterapia;
};

struct tListaLesao{
  tLesao **lesao;
  int qtd;
  int paraCirurgia;
  int paraCrioterapia;
};

tLesao* criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho, int cirurgia, int crioterapia){
    tLesao* l = calloc(1, sizeof(tLesao));

    strcpy(l->rotulo, rotulo);
    strcpy(l->diagnostico, diagnostico);
    strcpy(l->regiao, regiao);
    l->tamanho = tamanho;
    l->cirurgia = cirurgia;
    l->crioterapia = crioterapia;
    
    return  l;
}

tListaLesao *criaListaLesao(){
    tListaLesao *lista = calloc(1, sizeof(tListaLesao));

    lista->lesao = NULL;
    lista->qtd = 0;
    lista->paraCirurgia = 0;
    lista->paraCrioterapia = 0;

    return lista;
}

void adicionaListaLesao(tListaLesao *lista, tLesao *lesao){
    lista->qtd++;
    lista->lesao = realloc(lista->lesao, lista->qtd * sizeof(tLesao*));
    if(obtemSeLesaoParaCirurgia(lesao))
        lista->paraCirurgia++;
    if(lesao->crioterapia)
        lista->paraCrioterapia++;
    lista->lesao[lista->qtd - 1] = lesao;
}

int obtemNumeroLesoesParaCirurgia(tListaLesao *lista){
    int qtd = 0;
    for(int i = 0; i < lista->qtd; i++){
        if(lista->lesao[i]->cirurgia)
            qtd++;
    }
    return qtd;
}

int obtemNumeroLesoesParaCrioterapia(tListaLesao *lista){
    int qtd = 0;
    for(int i = 0; i < lista->qtd; i++){
        if(lista->lesao[i]->crioterapia)
            qtd++;
    }
    return qtd;
}

int obtemNumeroLesoes(tListaLesao *lista){
    return lista->qtd;
}

int obtemSeLesaoParaCirurgia(tLesao *lesao){
    return lesao->cirurgia;
}

int obtemTamanhoLesoesLista(tListaLesao *lista){
    int tamanho = 0;
    for(int i = 0; i < lista->qtd; i++){
        tamanho += lista->lesao[i]->tamanho;
    }
    return tamanho;
}

void desalocaListaLesao(tListaLesao *lista){
    if(lista != NULL){
        for(int i = 0; i < obtemNumeroLesoes(lista); i++){
            desalocaLesao(lista->lesao[i]);
        }
        if(lista->lesao != NULL)
            free(lista->lesao);
        free(lista);
    }
}


void desalocaLesao(tLesao *lesao){
    if(lesao != NULL)
        free(lesao); 
}

void imprimeNaTelaLesao(tLesao *lesao){
    printf("%s - %s - %s - %dMM\n", lesao->rotulo, lesao->diagnostico, lesao->regiao, lesao->tamanho);
}

void imprimeEmArquivoLesao(tLesao *lesao, FILE * arq){
    fprintf(arq, "%s - %s - %s - %dMM\n", lesao->rotulo, lesao->diagnostico, lesao->regiao, lesao->tamanho);
}

void salvaBinarioLesoes(tListaLesao *lista, FILE * arq){

  for(int i = 0; i < lista->qtd; i++){
      fwrite(lista->lesao[i], sizeof(tLesao), 1, arq);
  }

}

tListaLesao* recuperaLesaoBinario(FILE * arq, int qtd){
    tListaLesao *lista = malloc(sizeof(tListaLesao));
    lista->qtd = qtd;
    lista->lesao = malloc(qtd * sizeof(tLesao*));
    for(int i = 0; i < qtd; i++){
        tLesao *lesao = malloc(sizeof(tLesao));
        fread(lesao, sizeof(tLesao), 1, arq);
        lista->lesao[i] = lesao;
    }
    return lista;
}

tLesao* retornaLesaoLista(tListaLesao *lista, int i){
    return lista->lesao[i];
}