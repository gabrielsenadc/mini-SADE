#include "tListaBusca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tListaBusca{
    tPessoa **pessoa;
    int qtd;
};

tListaBusca *criaListaBusca(){
    tListaBusca *lista = malloc(sizeof(tListaBusca*));

    lista->pessoa = NULL;
    lista->qtd = 0;

    return lista;
}

void adicionaPessoaListaBusca(tListaBusca *lista, tPessoa *pessoa){
    lista->qtd++;
    lista->pessoa = realloc(lista->pessoa, lista->qtd * sizeof(tPessoa*));
    lista->pessoa[lista->qtd - 1] = pessoa;
}

void desalocaPessoa(tPessoa *p){
    if(p != NULL)
        free(p);
}

void desalocaListaBusca(void *dado){
    if(dado != NULL){
        tListaBusca *lista = (tListaBusca*) dado;
        for(int i = 0; i < lista->qtd; i++){
            desalocaPessoa(lista->pessoa[i]);
        }
        if(lista->pessoa != NULL)
            free(lista->pessoa);
        free(lista);
    }
}

void imprimeNaTelaListaBusca(void *dado){
    tListaBusca *lista = (tListaBusca*) dado;
    for(int i = 0; i < lista->qtd; i++){
        pritnf("%d - %s (%s)\n", i, lista->pessoa[i]->nome, lista->pessoa[i]->CPF);
    }
}

void imprimeEmArquivoListaBusca(void *dado, char *path){
    char arquivo[100];
    sprintf(arquivo, "%s/lista_busca.txt", path);
    FILE *arq = NULL;
    arq = fopen(arquivo, "a");
    tListaBusca *lista = (tListaBusca*) dado;

    for(int i = 0; i < lista->qtd; i++){
        fpritnf(arq, "%d - %s (%s)\n", i, lista->pessoa[i]->nome, lista->pessoa[i]->CPF);
    }

    fclose(arq);
}

