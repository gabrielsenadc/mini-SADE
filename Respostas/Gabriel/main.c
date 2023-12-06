#include "tBiopsia.h"
#include "tDocumento.h"
#include "tEncaminhamento.h"
#include "tFila.h"
#include "tLesao.h"
#include "tListaBusca.h"
#include "tPessoa.h"
#include "tReceita.h"
#include "tConsulta.h"

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
                    printf("SENHA INCORRETA");
                    acesso = 'E';
                }
            }
        }
        if(!existe){
            printf("USUARIO INEXISTENTE");
            acesso = 'E';
        }
    }
}

void buscaPaciente(tFila *fila, tListaPessoas *listaPessoas){
    char nome[100];
    printf("NOME DO PACIENTE: ");
    scanf("%[\n]%*c", nome);
    tListaBusca *lista = criaListaBusca();
    for(int i = 0; i < retornaQtdPesssoas(listaPessoas); i++){
        if(igualNome(nome, listaPessoas->pessoa[i])){
            adicionaPessoaListaBusca(lista, listaPessoas->pessoa[i]);
        }
    }
    printf("PACIENTES ENCONTRADOS:\n");
    imprimeNaTelaListaBusca(lista);

    printf("SELECIONE UMA OPÇÃO:\n(1) ENVIAR LISTA PARA IMPRESSAO\n(2) RETORNAR AO MENU PRINCIPAL");
    int acao;
    scanf("%d%*c", &acao);
    if(acao == 1)
        insereDocumentoFila(fila, lista, imprimeNaTelaListaBusca, imprimeEmArquivoListaBusca, desalocaListaBusca);
}

int main(){
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
    char teste;
    while(1){
        if(retornaCargo(usuario) == 'A'){
            printf("ESCOLHA UMA OPCAO:\n(1) CADASTRAR SECRETARIO\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        if(retornaCargo(usuario) == 'U'){
            printf("ESCOLHA UMA OPCAO:\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        if(retornaCargo(usuario) == 'M'){
            printf("ESCOLHA UMA OPCAO:\n");
            printf("(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8)FINALIZAR O PROGRAMA\n");
        }
        scanf("%d%*c", &acao);
        if(acao == 1 || acao == 2 || acao == 3){
            cadastraPessoa(listaPessoas, acao);
            printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
            scanf("%c", &teste);
            printf("%c", teste);
        }
        if(acao == 4)
            RealizaConsulta(fila, listaPessoas, nomeMedico, CRM);
        if(acao == 5)
            buscaPaciente(fila, listaPessoas);
        if(acao == 6)
            scanf("%d%*c", &acao);
        if(acao == 7)
            imprimeFila(fila, "saida");
        
        if(acao == 8)
            break;
    }


}