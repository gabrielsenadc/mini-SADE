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
            if(igualUsuario(usuario, lista->pessoa[i])){
                if(igualSenha(senha, lista->pessoa[i])){
                    acesso = retornaCargo(lista->pessoa[i]);
                    existe = 1;
                    return lista->pessoa[i];
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
    printf("NOME DO PACIENTE: ");
    scanf("%[^\n]%*c", nome);
    tListaBusca *lista = criaListaBusca();
    for(int i = 0; i < retornaQtdPesssoas(listaPessoas); i++){
        if(igualNome(nome, listaPessoas->pessoa[i])){
            adicionaPessoaListaBusca(lista, listaPessoas->pessoa[i]);
        }
    }
    printf("PACIENTES ENCONTRADOS:\n");
    imprimeNaTelaListaBusca(lista);

    printf("SELECIONE UMA OPÇÃO:\n(1) ENVIAR LISTA PARA IMPRESSAO\n(2) RETORNAR AO MENU PRINCIPAL\n");
    int acao;
    scanf("%d%*c", &acao);
    if(acao == 1)
        insereDocumentoFila(fila, lista, imprimeNaTelaListaBusca, imprimeEmArquivoListaBusca, desalocaListaBusca);
}

void relatorioGeral(tFila *fila, tListaPessoas *listaPessoas, tListaConsulta *listaConsulta){
    tRelatorio *r = criaRelatorio(listaPessoas, listaConsulta);
    
    imprimeNaTela2Relatorio(r);

    printf("SELECIONE UMA OPÇÃO:\n(1) ENVIAR PARA IMPRESSAO\n(2) RETORNAR AO MENU PRINCIPAL\n");
    int acao;
    scanf("%d%*c", &acao);
    if(acao == 1){
        insereDocumentoFila(fila, r, imprimeNaTelaRelatorio, imprimeEmArquivoRelatorio, desalocaRelatorio);
        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        scanf("%*c");
    }

}

int main(int argc, char *argv[]){
    if(argc <=1){
  	printf("ERRO: O diretorio de arquivos de configuracao nao foi informado");
  	return 1;
    } //verificar se recebeu o diretorio
    char diretorio[1001];
    sprintf(diretorio, "%s/saida", argv[1]); //transormar o diretorio em uma string    

    char diretorioBinario[100];
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:");
    scanf("%s%*c", diretorioBinario);

    tListaPessoas *listaPessoas = criaListaPessoas();
    cadastraPessoa(listaPessoas, 1);

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
    while(1){
        if(retornaCargo(usuario) == 'A'){
            printf("\nESCOLHA UMA OPCAO:\n(1) CADASTRAR SECRETARIO\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        if(retornaCargo(usuario) == 'U'){
            printf("\nESCOLHA UMA OPCAO:\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        if(retornaCargo(usuario) == 'M'){
            printf("\nESCOLHA UMA OPCAO:\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        scanf("%d%*c", &acao);
        if(acao == 1 || acao == 2 || acao == 3){
            cadastraPessoa(listaPessoas, acao);
            printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
            scanf("%*c");
        }
        if(acao == 4)
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
            imprimeFila(fila, diretorio);
	        scanf("%d%*c", &acao);
	        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
            scanf("%*c");
	        scanf("%d%*c", &acao);
	    }
        
        if(acao == 8)
            break;
    }

    desalocaFila(fila);
    desalocaLista(listaPessoas);
    desalocaListaConsulta(listaConsulta);
}