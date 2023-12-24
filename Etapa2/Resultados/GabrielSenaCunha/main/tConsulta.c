#include "tConsulta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tConsulta{
	tListaLesao *listaLesao;
	int qtd;
    char CPFpaciente[15];
    char CRM[12];
    char data[11];
    int diabetes, fumante, alergia, cancer;
    char pele[4];
};

struct tListaConsulta{
	tConsulta **consulta;
    int qtd;
};

tListaLesao *retornaListaLesao(tConsulta *c){
    return c->listaLesao;
}

int retornaFumanteConsulta(tConsulta *c){
    return c->fumante;
}
int retornaAlergiaConsulta(tConsulta *c){
    return c->alergia;
}
int retornaCancerConsulta(tConsulta *c){
    return c->cancer;
}
int retornaDiabtesConsulta(tConsulta *c){
    return c->diabetes;
}
char* retornaPeleConsulta(tConsulta *c){
    char *pele = c->pele;
    return pele;
}

char* retornaDataConsulta(tConsulta *c){
    char *data = c->data;
    return data;
}

int retornaQtdLesaoConsulta(tConsulta *c){
    return c->qtd;
}

char* retornaCPFConsulta(tConsulta *c){
    char *CPF = c->CPFpaciente;
    return CPF;
}

tListaConsulta* criaListaConsulta(){
    tListaConsulta *lista = calloc(1, sizeof(tListaConsulta));
    lista->consulta = NULL;
    lista->qtd = 0;
    return lista;
}

void adicionaListaConsulta(tListaConsulta *lista, tConsulta *consulta){
    lista->qtd++;
    lista->consulta = realloc(lista->consulta, lista->qtd * sizeof(tConsulta*));
    lista->consulta[lista->qtd - 1] = consulta;
}

void desalocaConsulta(tConsulta *c){
    if(c != NULL){
        desalocaListaLesao(c->listaLesao);
        free(c);
    }
}

int retornaQtdConsulta(tListaConsulta *lista){
    return lista->qtd;
}

int retornaQtdLesoesConsultas(tListaConsulta *lista){
    int lesoes = 0;
    for(int i = 0; i < lista->qtd; i++){
        lesoes += retornaNumeroLesoes(lista->consulta[i]->listaLesao);
    }
    return lesoes;
}

int retornaTamanhoLesoesConsultas(tListaConsulta *lista){
    int tamanho = 0;
    for(int i = 0; i < lista->qtd; i++){
        tamanho += retornaTamanhoLesoesLista(retornaConsultaLista(lista, i)->listaLesao);
    }
    return tamanho;
}

int retornaQtdLesoesParaCirurgiaConsultas(tListaConsulta *lista){
    int qtd = 0;
    for(int i = 0; i < lista->qtd; i++){
        qtd += retornaNumeroLesoesParaCirurgia(retornaConsultaLista(lista, i)->listaLesao);
    }
    return qtd;
}

int retornaQtdLesoesParaCrioterapiaConsultas(tListaConsulta *lista){
    int qtd = 0;
    for(int i = 0; i < lista->qtd; i++){
        qtd += retornaNumeroLesoesParaCrioterapia(retornaConsultaLista(lista, i)->listaLesao);
    }
    return qtd;
}

void desalocaListaConsulta(tListaConsulta *lista){
    if(lista != NULL){
        for(int i = 0; i < lista->qtd; i++){
            desalocaConsulta(lista->consulta[i]);
        }
        if(lista->consulta != NULL)
            free(lista->consulta);
        free(lista);
    }
}

tPessoa* pacienteCadastrado(char *CPF, tListaPessoas *lista){
    for(int i = 0; i < retornaQtdPesssoas(lista); i++){
        if(igualCPF(CPF, retornaPessoaLista(lista, i)))
            return retornaPessoaLista(lista, i);
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

    int i = retornaNumeroLesoes(lista) + 1;
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

int solicitaBiopsia(tFila *fila, tListaLesao *lista, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data){
    if(retornaNumeroLesoesParaCirurgia(lista)){
        tBiopsia *b = criaBiopsia(nomePaciente, CPF, lista, nomeMedico, CRM, data);
        insereDocumentoFila(fila, b, imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
        printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO.");
        return 1;
    }
    else
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA.");
        
    return 0;
}

void encaminhamento(tFila *fila, char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *data){
    printf("ENCAMINHAMENTO:\n");
    
    char especialidade[50];
    printf("ESPECIALIDADE ENCAMINHADA: ");
    scanf("%[^\n]%*c", especialidade);

    char motivo[300];
    printf("MOTIVO: ");
    scanf("%[^\n]%*c", motivo);

    tEncaminhamento *e = criaEncaminhamento(nomePaciente, CPF, especialidade, motivo, nomeMedico, CRM, data);
    insereDocumentoFila(fila, e, imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);
}

void RealizaConsulta(tFila *fila, tListaPessoas *listaPessoas, char *nomeMedico, char *CRM, tListaConsulta *listaConsulta){
    char CPF[15];
    printf("CPF DO PACIENTE: ");
    scanf("%s%*c", CPF);
    tPessoa *pessoa = pacienteCadastrado(CPF, listaPessoas);
    if(pessoa == NULL)
        return;
    atenderPessoa(pessoa);
    
    
    int dia = retornaDia(pessoa), mes = retornaMes(pessoa), ano = retornaAno(pessoa);
    printf("CPF DO PACIENTE: %s\n", CPF);
    printf("- NOME: %s\n", retornaNome(pessoa));
    printf("- DATA DE NASCIMENTO: %02d/%02d/%04d\n", dia, mes, ano);

    int d, m, a;
    char data[11], pele[4];
    int diabetes, fumante, alergia, cancer;
    printf("DATA DA CONSULTA: ");
    scanf("%s%*c", data);
    sscanf(data, "%d/%d/%d", &d, &m, &a);
    sprintf(data, "%d/%d/%d", d, m, a);

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


    /**
     * se ja solicitaram a biopsia
    */
    int biopsia = 0;

    int acao;
    tListaLesao *listaLesao = criaListaLesao();
    while(1){
        printf("ESCOLHA UMA OPCAO:\n(1) CADASTRAR LESAO\n(2) GERAR RECEITA MEDICA\n(3) SOLICITACAO DE BIOPSIA\n(4) ENCAMINHAMENTO\n(5) ENCERRAR CONSULTA\n");
        scanf("%d%*c", &acao);


        if(acao == 1){
            cadastraLesao(listaLesao);
        }
        if(acao == 2){
            cadastraReceita(fila, retornaNome(pessoa), nomeMedico, CRM, data);
        }
        if(acao == 3){
            biopsia = solicitaBiopsia(fila, listaLesao, retornaNome(pessoa), CPF, nomeMedico, CRM, data);
        }
        if(acao == 4){
            encaminhamento(fila, retornaNome(pessoa), CPF, nomeMedico, CRM, data);
        }
        if(acao == 5){
            break;
        }
        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        scanf("%*c");
    }

    tConsulta *c = calloc(1, sizeof(tConsulta));

    c->fumante = fumante;
    c->alergia = alergia;
    c->cancer = cancer;
    c->diabetes = diabetes;
    strcpy(c->pele, pele);
    strcpy(c->CRM, CRM);
    strcpy(c->CPFpaciente, CPF);
    strcpy(c->data, data);
    c->listaLesao = listaLesao;
    c->qtd = retornaNumeroLesoes(c->listaLesao);
    adicionaListaConsulta(listaConsulta, c);

}

void salvaConsultasBinario(tListaConsulta *lista, char *path){
  char diretorio[200];
  sprintf(diretorio, "%s/consultas.bin", path);
  FILE *arq = fopen(diretorio, "wb");
  sprintf(diretorio, "%s/lesoes.bin", path);
  FILE *arqL = fopen(diretorio, "wb");

  fwrite(&(lista->qtd), sizeof(int), 1, arq);

  for(int i = 0; i < lista->qtd; i++){
      fwrite(lista->consulta[i], sizeof(tConsulta), 1, arq);
      salvaBinarioLesoes(retornaConsultaLista(lista, i)->listaLesao, arqL);
  }

  fclose(arqL);
  fclose(arq);
}

void recuperaConsultasBinario(tListaConsulta *lista, char *path){
    char diretorio[200];
    sprintf(diretorio, "%s/consultas.bin", path);
    FILE *arq = fopen(diretorio, "rb");
    if(arq == NULL)
        return;
    sprintf(diretorio, "%s/lesoes.bin", path);
    FILE *arqL = fopen(diretorio, "rb");

    int qtd = 0;
    fread(&qtd, sizeof(int), 1, arq);

    lista->qtd = qtd;
    lista->consulta = realloc(lista->consulta, lista->qtd * sizeof(tConsulta*));
    for(int i = 0; i < lista->qtd; i++){
        tConsulta *c = malloc(sizeof(tConsulta));
        fread(c, sizeof(tConsulta), 1, arq);

        c->listaLesao = recuperaLesoesBinario(arqL, c->qtd);

        lista->consulta[i] = c;
    }

  fclose(arq);
  fclose(arqL);
}

tConsulta* retornaConsultaLista(tListaConsulta *lista, int i){
    return lista->consulta[i];
}