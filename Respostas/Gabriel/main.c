#include "tBiopsia.h"
#include "tDocumento.h"
#include "tEncaminhamento.h"
#include "tFila.h"
#include "tLesao.h"
#include "tListaBusca.h"
#include "tPessoa.h"
#include "tReceita.h"
#include "tConsulta.h"

int main(){
    char diretorioBinario[100];
    printf("DIGITE O CAMINHO DO BANCO DE DADOS:");
    scanf("%s%*c", diretorioBinario);

    tListaPessoas *listaPessoas = criaListaPessoas();
    cadastraPessoa(listaPessoas, 1);

    char usuario[20], senha[20];
    printf("\nDIGITE SEU LOGIN:");
    scanf("%s%*c", usuario);

    printf("DIGITE SUA SENHA:\n");
    scanf("%s%*c", senha);

    for(int i = 0; i < )
}