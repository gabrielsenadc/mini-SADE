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
        printf("\nDIGITE SEU LOGIN:");
        scanf("%s%*c", usuario);

        printf("DIGITE SUA SENHA:");
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
        if(acao == 1 || acao == 2 || acao == 3)
            cadastraPessoa(listaPessoas, acao);
        if(acao == 4)
            RealizaConsulta(fila, listaPessoas, nomeMedico, CRM);
        if(acao == 5){
            
        }
        if(acao == 7)
            imprimeFila(fila, "saida");
        
        if(acao == 8)
            break;
    }


    /*char nome[100];
    for(int i = 0; i < retornaQtdPesssoas(listaPessoas); i++){
        strcpy(nome, retornaNome(listaPessoas->pessoa[i]));
        printf("%s\n", nome);
    }*/
}