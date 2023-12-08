#include "tLesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tLesao* criaLesao(char *rotulo, char *diagnostico, char *regiao, int tamanho, int cirurgia, int crioterapia){
    tLesao* l = malloc(sizeof(tLesao));

    strcpy(l->rotulo, rotulo);
    strcpy(l->diagnostico, diagnostico);
    strcpy(l->regiao, regiao);
    l->tamanho = tamanho;
    l->cirurgia = cirurgia;
    l->crioterapia = crioterapia;
    
    return  l;
}

tListaLesao *criaListaLesao(){
    tListaLesao *lista = malloc(sizeof(tListaLesao));

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
    return lista->paraCirurgia;
}

int obtemNumeroLesoesParaCrioterapia(tListaLesao *lista){
    return lista->paraCrioterapia;
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