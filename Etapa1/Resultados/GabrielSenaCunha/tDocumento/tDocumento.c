#include "tDocumento.h"
#include <stdio.h>
#include <stdlib.h>

struct tDocumento {
  void *dado;
  func_ptr_imprimeNaTela imprimeNaTela;
  func_ptr_imprimeEmArquivo ImprimeEmArquivo;
  func_ptr_desaloca desaloca;
};

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
func_ptr_imprimeEmArquivo ImprimeEmArquivo,
func_ptr_desaloca desaloca){
  tDocumento* d = malloc(sizeof(tDocumento));
  d->dado = dado;
  d->imprimeNaTela = imprimeNaTela;
  d->desaloca = desaloca;
  d->ImprimeEmArquivo = ImprimeEmArquivo;
  return d;
}

void desalocaDocumento(tDocumento *doc){
  doc->desaloca(doc->dado);
  free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc){
  doc->imprimeNaTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path){
  doc->ImprimeEmArquivo(doc->dado, path);
}