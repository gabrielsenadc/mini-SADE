#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tPessoa.h"
#include "tLesao.h"
#include "tFila.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"

typedef struct {
	tListaLesao *lista;
}tConsulta;

tPessoa* pacienteCadastrado(char *CPF, tListaPessoas *lista){
    for(int i = 0; i < lista->qtd; i++){
        if(igualCPF(CPF, lista->pessoa[i]))
            return lista->pessoa[i];
    }
    return NULL;
}

void cadastraLesao(tListaLesao *lista){
    printf("CADASTRO DE LESAO:\n");

    char diagnostico[24];
    printf("DIAGNOSTICO CLINICO: ");
    scanf("%[^\n]%*c", diagnostico);

    char regiao[15];
    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]%*c", regiao);

    int tamanho;
    printf("TAMANHO:  ");
    scanf("%d%*c", &tamanho);
            
    int cirurgia;
    printf("ENVIAR PARA CIRURGIA: ");
    scanf("%d%*c", &cirurgia);

    int crioterapia;
    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d%*c", &crioterapia);

    int i = obtemNumeroLesoes(lista) + 1;
    char rotulo[5];
    sprintf(rotulo, "L%d", i);
    tLesao *lesao = criaLesao(rotulo, diagnostico, regiao, tamanho, cirurgia, crioterapia);
    adicionaListaLesao(lista, lesao);
}

void cadastraReceita(tFila *fila, char *nomePaciente, char *nomeMedico, char *CRM, char *dataStr){
    printf("RECEITA MEDICA:\n");

    eTipoUso tipoUso;
    char uso[7];
    printf("TIPO DE USO: ");
    scanf("%[^\n]%*c", uso);
    if(uso[0] == 'O')
        tipoUso = ORAL;
    if(uso[0] == 'T')
        tipoUso = TOPICO;
    
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]%*c", nomeMedicamento);

    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%[^\n]%*c", tipoMedicamento);

    int qntd;
    printf("QUANTIDADE: ");
    scanf("%d%*c", &qntd);

    char instrucoes[MAX_TAM_NOME_MEDICAMENTO];
    printf("INSTRUÇÕES DE USO: ");
    scanf("%[^\n]%*c", instrucoes);

    tReceita *receita = criaReceita(nomePaciente, tipoUso, nomeMedicamento, tipoMedicamento, instrucoes, qntd, nomeMedico, CRM, dataStr);
    insereDocumentoFila(fila, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
}

void solicitaBiopsia(tFila *fila, tListaLesao *lista, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data){
    if(obtemNumeroLesoesParaCirurgia(lista)){
        tBiopsia *b = criaBiopsia(nomePaciente, CPF, lista, nomeMedico, CRM, data);
        insereDocumentoFila(fila, b, imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
        printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO.");
    }
    else{
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA.");
    }

}

void encaminhamento(tFila *fila, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data){
    printf("ENCAMINHAMENTO:\n");
    
    char especialidade[50];
    printf("ESPECIALIDADE ENCAMINHADA: ");
    scanf("%[^\n]%*c", especialidade);

    char motivo[50];
    printf("MOTIVO: ");
    scanf("%[^\n]%*c", motivo);

    tEncaminhamento *e = criaEncaminhamento(nomePaciente, CPF, especialidade, motivo, nomeMedico, CRM, data);
    insereDocumentoFila(fila, e, imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);
}

tConsulta* RealizaConsulta(tFila *fila, tListaPessoas *listaPessoas, char *nomeMedico, char *CRM){
    char CPF[15];
    printf("CPF DO PACIENTE: ");
    scanf("%s%*c", CPF);
    tPessoa *pessoa = pacienteCadastrado(CPF, listaPessoas);
    if(pessoa == NULL)
        return NULL;
    
    char nomePaciente[100];
    strcpy(nomePaciente, retornaNome(pessoa));
    int dia = retornaDia(pessoa), mes = retornaMes(pessoa), ano = retornaAno(pessoa);
    printf("CPF DO PACIENTE: %s\n", CPF);
    printf("- NOME: %s\n", nomePaciente);
    printf("- DATA DE NASCIMENTO: %02d/%02d/%04d\n", dia, mes, ano);

    char data[11], pele[4];
    int diabetes, fumante, alergia, cancer;
    printf("DATA DA CONSULTA: ");
    scanf("%s%*c", data);

    printf("POSSUI DIABETES: ");
    scanf("%d%*c", &diabetes);

    printf("FUMANTE:  ");
    scanf("%d%*c", &fumante);

    printf("ALEGIA A MEDICAMENTO: ");
    scanf("%d%*c", &alergia);

    printf("HISTORICO DE CANCER:");
    scanf("%d%*c", &cancer);

    printf("TIPO DE PELE: ");
    scanf("%s%*c", pele);

    int acao;
    tListaLesao *listaLesao = criaListaLesao();
    strcpy(nomePaciente, retornaNome(pessoa));
    while(1){
        printf("ESCOLHA UMA OPCAO:\n(1) CADASTRAR LESAO\n(2) GERAR RECEITA MEDICA\n(3) SOLICITACAO DE BIOPSIA\n(4) ENCAMINHAMENTO\n(5) ENCERRAR CONSULTA\n");
        scanf("%d%*c", &acao);


        if(acao == 1){
            cadastraLesao(listaLesao);
        }
        if(acao == 2){
            cadastraReceita(fila, nomePaciente, nomeMedico, CRM, data);
        }
        if(acao == 3){
            solicitaBiopsia(fila, listaLesao, nomePaciente, CPF, nomeMedico, CRM, data);
        }
        if(acao == 4){
            encaminhamento(fila, nomePaciente, CPF, nomeMedico, CRM, data);
        }
        if(acao == 5){
            break;
        }
        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        scanf("%*c");
    }

    tConsulta *c = malloc(sizeof(tConsulta));
    c->lista = listaLesao;

    return c;
}

#endif