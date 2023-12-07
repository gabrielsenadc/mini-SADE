#include "tRelatorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tRelatorio{
    int atendidos;
    int idade;
    int f, m, o;
    int tamanho, lesoes;
    int paraCirurgia, paraCrioterapia;
};

tRelatorio *criaRelatorio(tListaPessoas *listaPessoas, tListaConsulta *listaConsulta){
    int atendidos = 0, idade = 0, pacientes = 0, f = 0, m = 0, o = 0;
    for(int i = 0; i < retornaQtdPesssoas(listaPessoas); i++){
        if(retornaAtendido(listaPessoas->pessoa[i]))
            atendidos++;
        if(retornaCargo(listaPessoas->pessoa[i]) == 'P'){
            pacientes++;
            idade += calculaIdade(listaPessoas->pessoa[i]);
            if(retornaGenero(listaPessoas->pessoa[i]) == 'M')
            m++;
            if(retornaGenero(listaPessoas->pessoa[i]) == 'F')
            f++;
            if(retornaGenero(listaPessoas->pessoa[i]) == 'O')
            o++;
        }
    }
    int tamanho = retornaTamanhoLesoesConsultas(listaConsulta);
    int lesoes = retornaQtdLesoesConsultas(listaConsulta);
    tamanho = tamanho / lesoes;
    idade = idade / pacientes;
    int paraCirurgia = retornaQtdLesoesParaCirurgiaConsultas(listaConsulta);
    int paraCrioterapia = retornaQtdLesoesParaCrioterapiaConsultas(listaConsulta);

    tRelatorio *relatorio = malloc(sizeof(tRelatorio));
    relatorio->atendidos = atendidos;
    relatorio->idade = idade;
    relatorio->f = f;
    relatorio->m = m;
    relatorio->o = o;
    relatorio->tamanho = tamanho;
    relatorio->lesoes = lesoes;
    relatorio->paraCirurgia = paraCirurgia;
    relatorio->paraCrioterapia = paraCrioterapia;

    return relatorio;
}

void desalocaRelatorio(void *dado){
    if(dado != NULL){
        tRelatorio *r = (tRelatorio*) dado;
        free(r);
    }
}

void imprimeNaTelaRelatorio(void *dado){
    tRelatorio *r = (tRelatorio*) dado;
    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->atendidos);
    printf("IDADE MEDIA: %d\n", r->idade);
    printf("DISTRIBUICAO POR GENERO:\n- FEMININO: %d\n- MASCULINO: %d\n- OUTROS: %d\n", r->f, r->m, r->o);
    printf("TAMANHO MEDIO DAS LESOES: %d\n", r->tamanho);
    printf("NUMERO TOTAL DE LESOES: %d\n", r->lesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d", r->paraCirurgia);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->paraCrioterapia);
}

void imprimeEmArquivoRelatorio(void *dado, char *path){
    char arquivo[100];
    sprintf(arquivo, "%s/biopsia.txt", path);
    FILE *arq = NULL;
    arq = fopen(arquivo, "a");
    tRelatorio *r = (tRelatorio*) dado;

    fprintf(arq, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->atendidos);
    fprintf(arq, "IDADE MEDIA: %d\n", r->idade);
    fprintf(arq, "DISTRIBUICAO POR GENERO:\n- FEMININO: %d\n- MASCULINO: %d\n- OUTROS: %d\n", r->f, r->m, r->o);
    fprintf(arq, "TAMANHO MEDIO DAS LESOES: %d\n", r->tamanho);
    fprintf(arq, "NUMERO TOTAL DE LESOES: %d\n", r->lesoes);
    fprintf(arq, "NUMERO TOTAL DE CIRURGIAS: %d", r->paraCirurgia);
    fprintf(arq, "NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->paraCrioterapia);


  fclose(arq);
}

void imprimeNaTela2Relatorio(tRelatorio *r){
    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->atendidos);
    printf("IDADE MEDIA: %d\n", r->idade);
    printf("DISTRIBUICAO POR GENERO:\n- FEMININO: %d\n- MASCULINO: %d\n- OUTROS: %d\n", r->f, r->m, r->o);
    printf("TAMANHO MEDIO DAS LESOES: %d\n", r->tamanho);
    printf("NUMERO TOTAL DE LESOES: %d\n", r->lesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d", r->paraCirurgia);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->paraCrioterapia);
}