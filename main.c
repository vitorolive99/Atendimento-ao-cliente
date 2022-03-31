#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char *nome[50];
    int senha;
    int priori;
    struct no *proxNo;
}tipoNo;

typedef struct fila{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
}tipoFilaUnica;

void inicializa(tipoFilaUnica *lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->quant = 0;
}

int insereFilaVazia(tipoFilaUnica *listaEnc, char *nome, int senha, int priori){
    tipoNo *novoNo;
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    if(novoNo == NULL)
        return 0;
    strcpy(novoNo->nome, nome);
    novoNo->senha = senha;
    printf("\n%d\n", novoNo->senha);
    novoNo->priori = priori;
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

int insereNoFim(tipoFilaUnica *listaEnc, char *nome, int senha, int priori){
    tipoNo *novoNo;
    if(listaEnc->inicio == NULL)
        insereFilaVazia(listaEnc, nome, senha, priori);
    else{
        novoNo = (tipoNo*) malloc(sizeof(tipoNo));
        if(novoNo == NULL)
            return 0;
        strcpy(novoNo->nome, nome);
        novoNo->senha = senha;
        printf("\n%d\n", senha);
        novoNo->priori = priori;
        novoNo->proxNo=NULL;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
    }
    return 1;
}

void exibeFila (tipoFilaUnica *listaEnc)
{
    tipoNo *atual;
    atual = listaEnc->inicio;
    printf("\n   Previsao de atendimento\n");
    while(atual != NULL)
    {
        printf("\n Cliente: %s\n Senha: %d", atual->nome, atual->senha);
        atual = atual->proxNo;
    }
}

int main()
{
    tipoFilaUnica *fila;
    char nome[50];
    int op, priori;
    inicializa(&fila);
    int senha = 1;
    do{
        printf("\n       Atendimento ao Cliente");
        printf("\n1 - Cadastrar cliente na fila original.");
        printf("\n2 - Exibir previsão de atendimento do cliente na fila original.");
        printf("\n3 - Dividir a fila de clientes entre os dois caixas.");
        printf("\n4 - Exibir previsão de atendimento do cliente nas duas filas que foram divididas.");
        printf("\n5 - Atender cliente.");
        printf("\n0 - Encerra o programa");
        printf("\nDigite sua opção: ");
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\n ---Digite o nome do cliente: ");
            scanf("%s", nome);
            printf("\n ---Atendimento prioritario?\n ---1-SIM\n ---0-NAO\n");
            scanf("%d",&priori);
            //scanf("%d", &aux);
            printf("\n%d\n", senha);
            insereNoFim(&fila, nome, senha,priori);
            senha++;
            break;
        case 2:
            exibeFila(&fila);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            printf("\nEncerrando Programa!!!");
        default:
            printf("Opcao invalida!!!");
        }
    }while(op != 0);

    return 0;
}
