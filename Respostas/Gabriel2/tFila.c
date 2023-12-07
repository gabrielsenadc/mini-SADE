#include "tFila.h"
#include <stdio.h>
#include <stdlib.h>

struct tFila {
  int qtd;
  int jaImpresso;
  tDocumento **documento;
};

tFila *criaFila(){
  tFila *fila = malloc(sizeof(tFila));
  fila->qtd = 0;
  fila->documento = NULL;
  fila->jaImpresso = -1;
  return fila;
}

void desalocaFila(tFila *f){
  if(f != NULL){
    if(f->documento != NULL){
      for(int i = 0; i < f->qtd; i++){
        desalocaDocumento(f->documento[i]);
      }
      free(f->documento);
    }
    free(f);
  }
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
 func_ptr_imprimeEmArquivo ImprimeEmArquivo,
 func_ptr_desaloca desaloca){
  f->qtd++;
  f->documento = realloc(f->documento, f->qtd * sizeof(tDocumento*));
  f->documento[f->qtd - 1] = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
 }

int quantidadeDocumentosNaFila(tFila *f){
  return f->qtd;
}

void imprimeFila(tFila *f, char *path){
  for(int i = 0; i < f->qtd; i++){
    if(i > f->jaImpresso)
      imprimeNaTelaDocumento(f->documento[i]);
      imprimeEmArquivoDocumento(f->documento[i], path);
  }
  f->jaImpresso = f->qtd - 1;
}