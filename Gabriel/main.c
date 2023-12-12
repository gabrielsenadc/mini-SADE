#include "tBiopsia.h"
#include "tDocumento.h"
#include "tEncaminhamento.h"
#include "tFila.h"
#include "tLesao.h"
#include "tListaBusca.h"
#include "tPessoa.h"
#include "tReceita.h"
#include "tConsulta.h"
#include "tRelatorio.h"

#include <stdio.h>

//realiza o login e retorna a pessoa logada
tPessoa* login(tListaPessoas *lista){
    int existe;
    char acesso = 'E';
    while(acesso == 'E'){
        existe = 0;
        char usuario[20], senha[20];
        printf("\nDIGITE SEU LOGIN: ");
        scanf("%s%*c", usuario);

        printf("DIGITE SUA SENHA: ");
        scanf("%s%*c", senha);

        for(int i = 0; i < retornaQtdPesssoas(lista); i++){
            if(igualUsuario(usuario, retornaPessoaLista(lista, i))){
                if(igualSenha(senha, retornaPessoaLista(lista, i))){
                    acesso = retornaCargo(retornaPessoaLista(lista, i));
                    existe = 1;
                    return retornaPessoaLista(lista, i);
                }
                else{
                    printf("SENHA INCORRETA\n");
                    acesso = 'E';
                }
            }
        }
        if(!existe){
            printf("USUARIO INEXISTENTE\n");
            acesso = 'E';
        }
    }
}

void buscaPaciente(tFila *fila, tListaPessoas *listaPessoas){
    char nome[100];
    int total = 0;
    printf("NOME DO PACIENTE: ");
    scanf("%[^\n]%*c", nome);

    for(int i = 0; i < retornaQtdPesssoas(listaPessoas); i++){
        if(igualNome(nome, retornaPessoaLista(listaPessoas, i))){
           total++;
        }
    }
    if(total == 0)
        return;
        
    tListaBusca *lista = criaListaBusca();
    for(int i = 0; i < retornaQtdPesssoas(listaPessoas); i++){
        if(igualNome(nome, retornaPessoaLista(listaPessoas, i))){
            adicionaPessoaListaBusca(lista, retornaPessoaLista(listaPessoas, i));
        }
    }
    printf("PACIENTES ENCONTRADOS:\n");
    imprimeNaTelaListaBusca(lista);

    printf("SELECIONE UMA OPÇÃO:\n(1) ENVIAR LISTA PARA IMPRESSAO\n(2) RETORNAR AO MENU PRINCIPAL\n");
    int acao;
    scanf("%d%*c", &acao);
    if(acao == 1)
        insereDocumentoFila(fila, lista, imprimeNaTelaListaBusca, imprimeEmArquivoListaBusca, desalocaListaBusca);
    else 
        desalocaListaBusca(lista);
    
}

void relatorioGeral(tFila *fila, tListaPessoas *listaPessoas, tListaConsulta *listaConsulta){
    tRelatorio *r = criaRelatorio(listaPessoas, listaConsulta);
    
    imprimeNaTelaRelatorio(r);

    printf("SELECIONE UMA OPÇÃO:\n(1) ENVIAR PARA IMPRESSAO\n(2) RETORNAR AO MENU PRINCIPAL\n");
    int acao;
    scanf("%d%*c", &acao);
    if(acao == 1){
        insereDocumentoFila(fila, r, imprimeNaTelaRelatorio, imprimeEmArquivoRelatorio, desalocaRelatorio);
        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        scanf("%*c");
    }
    else
        desalocaRelatorio(r);

}

int main(int argc, char *argv[]){
    if(argc <=1){
  	printf("ERRO: O diretorio de arquivos de configuracao nao foi informado");
  	return 1;
    } //verificar se recebeu o diretorio
    char diretorio[100];
    sprintf(diretorio, "%s/saida", argv[1]); //transormar o diretorio em uma string    

    char arquivo[121];
    sprintf(arquivo, "%s/receita.txt", diretorio);
    FILE *arq = fopen(arquivo, "a");
    fclose(arq);

    sprintf(arquivo, "%s/lista_busca.txt", diretorio);
    FILE *arq2 = fopen(arquivo, "a");
    fclose(arq2);

    sprintf(arquivo, "%s/relatorio_geral.txt", diretorio);
    FILE *arq3 = fopen(arquivo, "a");
    fclose(arq3);

    sprintf(arquivo, "%s/encaminhamento.txt", diretorio);
    FILE *arq4 = fopen(arquivo, "a");
    fclose(arq4);

    sprintf(arquivo, "%s/biopsia.txt", diretorio);
    FILE *arq5 = fopen(arquivo, "a");
    fclose(arq5);

    char diretorioBinario[100], pathB[200];
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:");
    scanf("%s%*c", diretorioBinario);

    sprintf(pathB, "%s/%s", argv[1], diretorioBinario);

    tListaPessoas *listaPessoas = criaListaPessoas();
    char pathP[215];

    sprintf(pathP, "%s/pessoas.bin", pathB);

    FILE *arqP = fopen(pathP, "rb");
    if(arqP == NULL)
        cadastraPessoa(listaPessoas, 1);
    else{
        recuperaBinarioPessoas(listaPessoas, arqP);
    }
    
    tPessoa *usuario = login(listaPessoas);

    tFila *fila = criaFila();

    char CRM[12], nomeMedico[100];
    if(retornaCargo(usuario) == 'M'){
        strcpy(CRM, retornaCRM(usuario));
        strcpy(nomeMedico, retornaNome(usuario));
    }
    if(retornaCargo(usuario) == 'A' || retornaCargo(usuario) == 'U'){
        CRM[0] = '\0';
        nomeMedico[0] = '\0';
    }

    int acao;
    tListaConsulta *listaConsulta = criaListaConsulta();
    recuperaConsultasBinario(listaConsulta, pathB);
    char cargo = retornaCargo(usuario);
    while(1){
        if(retornaCargo(usuario) == 'A'){
            printf("\nESCOLHA UMA OPCAO:\n(1) CADASTRAR SECRETARIO\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        if(retornaCargo(usuario) == 'U'){
            printf("\nESCOLHA UMA OPCAO:\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n");
            printf("(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        if(retornaCargo(usuario) == 'M'){
            printf("\nESCOLHA UMA OPCAO:\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        scanf("%d%*c", &acao);
        if((acao == 1 && cargo == 'A') || (acao == 2 && (cargo == 'A' || cargo == 'U')) || (acao == 3 && (cargo == 'A' || cargo == 'U'))){
            if(cadastraPessoa(listaPessoas, acao)){
            printf("PRESSIONE QUALQUER TECLA PARA RTORNAR AO MENU ANTERIOR\n");
            scanf("%*c");
            }
        }
        if(acao == 4 && cargo != 'U')
            RealizaConsulta(fila, listaPessoas, nomeMedico, CRM, listaConsulta);
        if(acao == 5){
            buscaPaciente(fila, listaPessoas);
	        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
            scanf("%*c");
        }
        if(acao == 6){
          relatorioGeral(fila, listaPessoas, listaConsulta);  	
	    }
        if(acao == 7){
            while(acao != 2){
                printf("ESCOLHA UMA OPCAO:\n(1) EXECUTAR FILA DE IMPRESSAO\n(2) RETORNAR AO MENU ANTERIOR\n");
                scanf("%d%*c", &acao);
                if(acao == 1){
                    imprimeFila(fila, diretorio);
                    printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                    scanf("%*c");
                }
            }
	    }
        
        if(acao == 8)
            break;
    }

    salvaBinarioPessoas(listaPessoas, pathB);
    salvaConsultasBinario(listaConsulta, pathB);
    desalocaFila(fila);
    desalocaListaPessoas(listaPessoas);
    desalocaListaConsulta(listaConsulta);
}