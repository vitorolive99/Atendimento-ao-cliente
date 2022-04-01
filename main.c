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
}tipoFila;

void inicializa(tipoFila *lista){
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->quant = 0;
    printf("1");
}

int insereFilaVazia(tipoFila *listaEnc, char *nome, int senha, int priori){
    tipoNo *novoNo;
    novoNo = (tipoNo*) malloc(sizeof(tipoNo));
    if(novoNo == NULL)
        return 0;
    strcpy(novoNo->nome, nome);
    novoNo->senha = senha;
    printf("\n%dvazio\n", novoNo->senha);
    novoNo->priori = priori;
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

int insereNoFim(tipoFila *listaEnc, char *nome, int senha, int priori){
    tipoNo *novoNo;
    if(listaEnc->inicio == NULL)
        insereFilaVazia(listaEnc, nome, senha, priori);
    else{
        novoNo = (tipoNo*) malloc(sizeof(tipoNo));
        if(novoNo == NULL)
            return 0;
        strcpy(novoNo->nome, nome);
        novoNo->senha = senha;
        printf("\n%dfim\n", senha);
        novoNo->priori = priori;
        novoNo->proxNo=NULL;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
    }
    return 1;
}

void exibeFila (tipoFila *listaEnc)
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

void divideFila (tipoFila *filaUnica, tipoFila *fila1, tipoFila *fila2)
{
    tipoNo *atual;
    tipoNo *novoNo1;
    tipoNo *novoNo2;
    atual = filaUnica->inicio;
    printf("%d", atual->senha);
    printf("passsou");
    while (1)
    {
        if(atual == NULL)break;
        novoNo1 = (tipoNo*) malloc(sizeof(tipoNo));
        strcpy(novoNo1->nome, atual->nome);
        insereNoFim(fila1, atual->nome, atual->senha, atual->priori);
        atual = atual->proxNo;
        if(atual == NULL)break;
        novoNo2 = (tipoNo*) malloc(sizeof(tipoNo));
        insereNoFim(fila2, atual->nome, atual->senha, atual->priori);
        atual = atual->proxNo;

        printf("passsou");
    }
}

int main()
{
    tipoFila *filaUnica;
    tipoFila *fila1;
    tipoFila *fila2;
    inicializa(&filaUnica);
    inicializa(&fila1);
    inicializa(&fila2);
    int senha;
    char nome[50];
    int op, priori;

    do{
        printf("\n\tAtendimento ao Cliente");
        printf("\n\t1 - Cadastrar cliente na fila original.");
        printf("\n\t2 - Exibir previs�o de atendimento do cliente na fila original.");
        printf("\n\t3 - Dividir a fila de clientes entre os dois caixas.");
        printf("\n\t4 - Exibir previs�o de atendimento do cliente nas duas filas que foram divididas.");
        printf("\n\t5 - Atender cliente.");
        printf("\n\t0 - Encerra o programa");
        printf("\n\tDigite sua op��o: ");
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\n ---Digite o nome do cliente: ");
            scanf("%s", nome);
            printf("\n ---Atendimento prioritario?\n ---1-SIM\n ---0-NAO\n");
            scanf("%d",&priori);
            printf("\nDigite a senha de atendimento: ");
            scanf("%d", &senha);
            insereNoFim(&filaUnica, nome, senha, priori);
            break;
        case 2:
            exibeFila(&filaUnica);
            break;
        case 3:
            divideFila(&filaUnica, &fila1, &fila2);
            printf("voltou");
            break;
        case 4:
            printf("\nFila 1:\n");
            exibeFila(&fila1);
            printf("\nFila 2:\n");
            exibeFila(&fila2);
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
