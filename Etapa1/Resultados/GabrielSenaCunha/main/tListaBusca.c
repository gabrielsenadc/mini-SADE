#include "tListaBusca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tListaBusca{
    tPessoa **pessoa;
    int qtd;
};

tListaBusca *criaListaBusca(){
    tListaBusca *lista = malloc(sizeof(tListaBusca));

    lista->pessoa = NULL;
    lista->qtd = 0;

    return lista;
}

void adicionaPessoaListaBusca(tListaBusca *lista, tPessoa *pessoa){
    lista->qtd++;
    lista->pessoa = realloc(lista->pessoa, lista->qtd * sizeof(tPessoa*));
    lista->pessoa[lista->qtd - 1] = pessoa;
}

void desalocaListaBusca(void *dado){
    if(dado != NULL){
        tListaBusca *lista = (tListaBusca*) dado;
        if(lista->pessoa != NULL)
            free(lista->pessoa);
        free(lista);
    }
}

tPessoa* retornaPessoaBusca(tListaBusca* lista, int i){
    return lista->pessoa[i];
}

void imprimeNaTelaListaBusca(void *dado){
    tListaBusca *lista = (tListaBusca*) dado;
    for(int i = 0; i < lista->qtd; i++){
        printf("%d - %s (%s)\n", i + 1, retornaNome(retornaPessoaBusca(lista, i)), retornaCPF(retornaPessoaBusca(lista, i)));
    }
}


void imprimeEmArquivoListaBusca(void *dado, char *path){
    char arquivo[100];
    sprintf(arquivo, "%s/lista_busca.txt", path);
    FILE *arq = NULL;
    arq = fopen(arquivo, "a");
    tListaBusca *lista = (tListaBusca*) dado;

    for(int i = 0; i < lista->qtd; i++){
        fprintf(arq, "%d - %s (%s)\n", i + 1, retornaNome(retornaPessoaBusca(lista, i)), retornaCPF(retornaPessoaBusca(lista, i)));
    }

    fclose(arq);
}


