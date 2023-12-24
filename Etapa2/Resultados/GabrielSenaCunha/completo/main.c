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

void printaUmPaciente(tPessoa *pessoa, tListaConsulta *lista, FILE *arq){
  int fumante = 0, diabetes = 0, cancer = 0, alergia = 0;
  int pele = 0, consulta = 0;

  for(int i = 0; i < retornaQtdConsulta(lista); i++){
    if(igualCPF(retornaCPFConsulta(retornaConsultaLista(lista, i)), pessoa)){
      fumante = retornaFumanteConsulta(retornaConsultaLista(lista, i));
      alergia = retornaAlergiaConsulta(retornaConsultaLista(lista, i));
      diabetes = retornaDiabtesConsulta(retornaConsultaLista(lista, i));
      cancer = retornaCancerConsulta(retornaConsultaLista(lista, i));
      pele = i;
      consulta++;
    }
  }

  fprintf(arq, "NOME: %s\n", retornaNome(pessoa));
  fprintf(arq, "CPF: %s\n", retornaCPF(pessoa));
  fprintf(arq, "DATA DE NASCIMENTO: %d/%d/%d\n", retornaDia(pessoa), retornaMes(pessoa), retornaAno(pessoa));
  fprintf(arq, "TELEFONE: %s\n", retornaTelefone(pessoa));
  fprintf(arq, "GENERO: ");
  if(retornaGenero(pessoa) == 'M')
    fprintf(arq, "MASCULINO\n");
  if(retornaGenero(pessoa) == 'F')
    fprintf(arq, "FEMININO\n");
  if(retornaGenero(pessoa) == 'O')
    fprintf(arq, "OUTROS\n");

  if(!consulta)
    fprintf(arq, "DIABETES: -\n");
  else if(diabetes)
    fprintf(arq, "DIABETES: SIM\n");
  else{
    fprintf(arq, "DIABETES: NAO\n");
  }

  if(!consulta)
    fprintf(arq, "FUMANTE: -\n");
  else if(fumante)
    fprintf(arq, "FUMANTE: SIM\n");
  else{
    fprintf(arq, "FUMANTE: NAO\n");
  }

  if(!consulta)
    fprintf(arq, "ALERGIA: -\n");
  else if(alergia)
    fprintf(arq, "ALERGIA: SIM\n");
  else{
    fprintf(arq, "ALERGIA: NAO\n");
  }

  if(!consulta)
    fprintf(arq, "HISTORICO DE CANCER: -\n");
  else if(cancer)
    fprintf(arq, "HISTORICO DE CANCER: SIM\n");
  else{
    fprintf(arq, "HISTORICO DE CANCER: NAO\n");
  }
 
  if(!consulta)
    fprintf(arq, "TIPO DE PELE: -\n");
  else 
    fprintf(arq, "TIPO DE PELE: %s\n", retornaPeleConsulta(retornaConsultaLista(lista, pele)));


  fprintf(arq, "QUANTIDADE DE CONSULTAS: %d\n", consulta);
  if(consulta)
  for(int i = 0; i < retornaQtdConsulta(lista); i++){
    if(igualCPF(retornaCPFConsulta(retornaConsultaLista(lista, i)), pessoa)){
    fprintf(arq, "- - -\n");
    fprintf(arq, "DATA DA CONSULTA: %s\n", retornaDataConsulta(retornaConsultaLista(lista, i)));
    fprintf(arq, "QUANTIDADE DE LESOES GERADAS: %d\n", retornaQtdLesaoConsulta(retornaConsultaLista(lista, i)));
    PrintaListaLesao(retornaListaLesao(retornaConsultaLista(lista, i)), arq);
    }
  }

  fprintf(arq, "- - - - - -\n- - - - - -\n");

}

void printaPacientes(tListaPessoas *lista, tListaConsulta *listaConsulta, char *path){
  char diretorio[200];
  sprintf(diretorio, "%s/pacientes.txt", path);
  FILE *arq = fopen(diretorio, "a");

  for(int i = 0; i < retornaQtdPesssoas(lista); i++){
    if(retornaCargo(retornaPessoaLista(lista, i)) == 'P')
      printaUmPaciente(retornaPessoaLista(lista, i), listaConsulta, arq);
    
  }

  fclose(arq);
}

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

    //caso nao tenha nenhum paciente com esse nome
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

    //criando os arquivos de saida
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

    char pathI[215];
    sprintf(pathI, "%s/inicio.bin", pathB);



    //se tiver algo salvo no banco de dados, le o arquivo; caso nao tenha, cadastra um secretario
    FILE *arqP = fopen(pathP, "rb");
    FILE *arqI = fopen(pathI, "rb");
    if(arqP == NULL && arqI == NULL)
        cadastraPessoa(listaPessoas, 1);
    else{
        if(arqP != NULL)
            recuperaBinarioPessoas(listaPessoas, arqP);
        if(arqI != NULL && arqP == NULL)
            recuperaInicio(listaPessoas, arqI);
    }
    if(arqI != NULL)
        fclose(arqI);
    tPessoa *usuario = login(listaPessoas);

    tFila *fila = criaFila();

    //caso a pessoa logada nao seja um medico, deixa o CRM e o nome do medico vazio
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
        
        if(acao == 6)
          relatorioGeral(fila, listaPessoas, listaConsulta);  	
	    
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

    printaMedicos(listaPessoas, diretorio);
    printaSecretarios(listaPessoas, diretorio);
    printaPacientes(listaPessoas, listaConsulta, diretorio);
    salvaBinarioPessoas(listaPessoas, pathB);
    salvaConsultasBinario(listaConsulta, pathB);
    desalocaFila(fila);
    desalocaListaPessoas(listaPessoas);
    desalocaListaConsulta(listaConsulta);
}