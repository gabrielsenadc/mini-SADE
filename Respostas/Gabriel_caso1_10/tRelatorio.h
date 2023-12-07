#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include "tConsulta.h"

typedef struct tRelatorio tRelatorio;

tRelatorio *criaRelatorio(tListaPessoas *listaPessoas, tListaConsulta *listaConsulta);

void desalocaRelatorio(void *dado);
  
void imprimeNaTelaRelatorio(void *dado);

void imprimeEmArquivoRelatorio(void *dado, char *path);

void imprimeNaTela2Relatorio(tRelatorio *r);

#endif