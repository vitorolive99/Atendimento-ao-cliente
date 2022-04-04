#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    char nome[50];
    int senha;
    char priori[3];
    struct no *proxNo;
} tipoNo;

typedef struct fila
{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoFila;

void printChamada (tipoNo *atual, int caixa)
{
    printf("\n\tCliente do caixa %d atendido com sucesso!\n",caixa);
    printf("\n\tCliente: %s\n\tSenha: %d\n\tPrioridade: %s\n\tCAIXA %d\n", atual->nome, atual->senha, atual->priori, caixa);

}

void inicializa(tipoFila *lista)
{
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->quant = 0;
}

int insereFilaVazia(tipoFila *listaEnc, char *nome, int senha, char *priori)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;
    strcpy(novoNo->nome, nome);
    novoNo->senha = senha;
    strcpy(novoNo->priori, priori);
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

int insereNoFim(tipoFila *listaEnc, char *nome, int senha, char *priori)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
        insereFilaVazia(listaEnc, nome, senha, priori);
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
            return 0;
        strcpy(novoNo->nome, nome);
        novoNo->senha = senha;
        strcpy(novoNo->priori, priori);
        novoNo->proxNo = NULL;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
    }
    return 1;
}

void exibeFila(tipoFila *listaEnc)
{
    tipoNo *atual;
    atual = listaEnc->inicio;
    printf("\n\tPrevisao de atendimento\n");
    while (atual != NULL)
    {
        printf("\n\tCliente: %s\n\tSenha: %d\n\tPrioridade: %s\n", atual->nome, atual->senha, atual->priori);
        atual = atual->proxNo;
    }
}

void divideFila(tipoFila *filaUnica, tipoFila *fila1, tipoFila *fila2)
{
    tipoNo *atual;
    atual = filaUnica->inicio;
    while (1)
    {
        if (atual == NULL)
            break;
        insereNoFim(fila1, atual->nome, atual->senha, atual->priori);
        atual = atual->proxNo;
        if (atual == NULL)
            break;
        insereNoFim(fila2, atual->nome, atual->senha, atual->priori);
        atual = atual->proxNo;
    }
}

void removeDoInicio(tipoFila *listaEnc){
    tipoNo *atual;
    atual = listaEnc->inicio;
    listaEnc->inicio = atual->proxNo;
    listaEnc->quant--;
    free(atual);
}

void removeFilaUnica(tipoFila *filaUnica, int senha)
{
    tipoNo *atual, *anterior;
    anterior = NULL;
    atual = filaUnica->inicio;
    if(atual->senha == senha){
        removeDoInicio(filaUnica);
        return;
    }
    while(atual->senha != senha){
        anterior = atual;
        atual = atual->proxNo;
    }
    anterior->proxNo = atual->proxNo;
    free(atual);
}
int estarVazia(tipoFila* list ){
    if(list -> inicio == NULL){
        return 1;
    }
        return 0;
}



int atendeCliente (tipoFila *fila, tipoFila *filaUnica, int caixa, char *priori)
{
    int senha;
    tipoNo *atual, *anterior;
    anterior = NULL;
    atual = fila->inicio;
    if(!strcmp(atual->priori, priori) || fila->inicio == fila->fim){
        senha = atual->senha;
        removeFilaUnica(filaUnica, senha);
        printChamada(atual, caixa);
        removeDoInicio(fila);
        return 1;
    }

    while(atual != NULL){
        if (!strcmp(atual->priori, priori)){
            break;
        }
        anterior = atual;
        atual = atual->proxNo;
    }if(atual == NULL){
        atual = fila->inicio;
        senha = atual->senha;
        removeFilaUnica(filaUnica, senha);
        printChamada(atual, caixa);
        removeDoInicio(fila);
    }else{
    senha = atual->senha;
    removeFilaUnica(filaUnica, senha);
    printChamada(atual, caixa);
    anterior->proxNo = atual->proxNo;
    free(atual);
    return 1;
    }

}

int main()
{
    tipoFila filaUnica;
    tipoFila fila1;
    tipoFila fila2;
    inicializa(&filaUnica);
    int senha=1000;
    char nome[50];
    int op, priori,aux,cont=0;

    do
    {
        printf("\n\n\tAtendimento ao Cliente");
        printf("\n\n\t1 - Cadastrar cliente na fila original.");
        printf("\n\t2 - Exibir previsao de atendimento do cliente na fila original.");
        printf("\n\t3 - Dividir a fila de clientes entre os dois caixas.");
        printf("\n\t4 - Exibir previsao de atendimento do cliente nas duas filas que foram divididas.");
        printf("\n\t5 - Atender cliente.");
        printf("\n\n\t0 - Encerra o programa");
        printf("\n\n\tDigite sua opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\n\t---Digite o nome do cliente: ");
            scanf("%s", nome);
            printf("\n\t---Atendimento prioritario?\n\t---1-SIM\n\t---0-NAO\n");
            printf("\n\tDigite sua escolha: ");
            scanf("%d", &priori);
            if(priori == 1)
                insereNoFim(&filaUnica, nome, senha, "SIM");
            else
                insereNoFim(&filaUnica, nome, senha, "NAO");
            senha++;
            break;
        case 2:
            exibeFila(&filaUnica);
            break;
        case 3:
            inicializa(&fila1);
            inicializa(&fila2);
            divideFila(&filaUnica, &fila1, &fila2);
            printf("\n\t--Fila dividida com sucesso--\n");
            break;
        case 4:
            printf("\n\tFila 1:\n");
            exibeFila(&fila1);
            printf("\n\tFila 2:\n");
            exibeFila(&fila2);
            break;
        case 5:
            printf("\n\t1 - Caixa 1");
            printf("\n\t2 - Caixa 2\n");
            printf("\n\tEscolha: ");
            scanf("%d", &aux);
            if(aux == 1){
                if(cont == 2){
                   if(!estarVazia(&fila1)){
                    atendeCliente(&fila1, &filaUnica, aux, "NAO");
                    cont=0;
                   }
                    else{
                        printf("\n\tTodos os clientes desta fila foram atendidos com sucesso!");
                        }

                }
                else{
                    if(!estarVazia(&fila1)){
                    atendeCliente(&fila1, &filaUnica, aux, "SIM");
                    cont=0;
                   }
                    else{
                        printf("\n\tTodos os clientes desta fila foram atendidos com sucesso!");
                        }
                }
            }
            if(aux == 2)
            {
                if(cont == 2){
                    if(!estarVazia(&fila2)){
                    atendeCliente(&fila2, &filaUnica, aux, "NAO");
                    cont=0;
                   }
                    else{
                        printf("\n\tTodos os clientes desta fila foram atendidos com sucesso!");
                        }
                }
                else{
                   if(!estarVazia(&fila2)){
                    atendeCliente(&fila2, &filaUnica, aux, "SIM");
                    cont=0;
                   }
                    else{
                        printf("\n\tTodos os clientes desta fila foram atendidos com sucesso!");
                        }
                }
            }
            break;
        case 0:
            printf("\n\tEncerrando Programa!!!");
            break;
        default:
            printf("\n\tOpcao invalida!!!\n");
        }
    } while (op != 0);

    return 0;
}
