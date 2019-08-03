#include<stdio.h>
#include<stdlib.h>

struct dados{
    int info;
    struct dados *prox;
};typedef struct dados tipoDado;

struct fila{
    tipoDado *primeiro;
    tipoDado *ultimo;
    int tamanho;
};typedef struct fila tipoFila;

void iniciaFila(tipoFila *filaAux){
    filaAux->primeiro = NULL;
    filaAux->ultimo == NULL;
    filaAux->tamanho = 0;
}

void insereFinal(tipoFila* filaAux, int n){
    tipoDado *novo = (tipoDado*) malloc(sizeof(tipoDado));
    novo->info = n;
    if(filaAux->tamanho == 0){
        novo->prox = NULL;
        filaAux->primeiro = novo;
        filaAux->ultimo = novo;
    }
    else{
    novo->prox = NULL;
    filaAux->ultimo->prox = novo;
    filaAux->ultimo = novo;
    }
    filaAux->tamanho++;
}


void removeFila(tipoFila *filaAux){
    tipoDado *aux = filaAux->primeiro;
    filaAux->primeiro = aux->prox;
    free(aux);
}

void imprimeFila(tipoFila *filaAux){
    tipoDado  *aux = filaAux->primeiro;
    while(aux != NULL){
        printf("%d",aux->info);
        aux = aux->prox;
    }
}


int main(){
    tipoFila fila;
    int qtd,n;
    iniciaFila(&fila);
    printf("Digite quantos elementos deseja inserir");
    scanf("%d",&qtd);
    while(qtd > 0){
        scanf("%d",&n);
        insereFinal(&fila,n);
        qtd--;
    }
    printf("Imprimindo...");
    imprimeFila(&fila);
    printf("Quantos quer remover?");
    scanf("%d",&qtd);
    while(qtd>0){
        removeFila(&fila);
        qtd--;
    }
    imprimeFila(&fila);
}
