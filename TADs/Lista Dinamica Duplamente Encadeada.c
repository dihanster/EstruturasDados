#include<stdio.h>
#include<stdlib.h>

struct dados{
    int info;
    struct dados *prox;
    struct dados *ant;
};typedef struct dados tipoDado;

struct lista{
    tipoDado *primeiro;
    tipoDado *ultimo;
    int tamanho;
};typedef struct lista tipoLDDE;

void iniciaLista(tipoLDDE *listaAux){
    listaAux->ultimo = NULL;
    listaAux->primeiro = NULL;
    listaAux->tamanho = 0;
}

void insereFinal(tipoLDDE *listaAux, int n){
    tipoDado *novo = (tipoDado*) malloc(sizeof(tipoDado));
    novo->info = n;
    if(listaAux->tamanho == 0){
        novo->prox = NULL;
        novo->ant = NULL;
        listaAux->primeiro = novo;
        listaAux->ultimo = novo;
    }
    else{
        novo->ant = listaAux->ultimo;
        novo->prox = NULL;
        listaAux->ultimo->prox = novo;
        listaAux->ultimo = novo;
    }
    listaAux->tamanho++;
}

void imprimeLista(tipoLDDE *listaAux){
    tipoDado *aux = listaAux->primeiro;
    printf("Os numeros digitados foram: \n");
    while(aux != NULL){
        printf("%d ",aux->info);
        aux = aux->prox;
    }
    printf("\nImprimindo ao contrario\n");
    aux = listaAux->ultimo;
    while(aux != NULL){
        printf("%d ",aux->info);
        aux = aux->ant;
    }
}

void funcaoRemove(tipoLDDE *listaAux, int n){
    tipoDado *aux = listaAux->primeiro;
    while(aux != NULL){ /*achando o no*/
        if(aux->info == n)
            break;
        else
            aux = aux->prox;
    }
    if(aux == listaAux->primeiro){
        listaAux->primeiro = aux->prox;
        aux->prox->ant = NULL;
        free(aux);
    }
    else if(aux == listaAux->ultimo){
            listaAux->ultimo = aux->ant;
            aux->ant->prox = NULL;
            free(aux);
        }
        else{
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
        }
    }

int main(){
    int n, qtd;
    tipoLDDE lista;
    iniciaLista(&lista);
    printf("Quantos numeros deseja inserir? ");
    scanf("%d",&qtd);
    printf("Digite os numeros\n");
    while(qtd > 0){
        scanf("%d",&n);
        insereFinal(&lista,n);
        qtd--;
    }
    imprimeLista(&lista);
    //tipoDado *aux = lista.primeiro;
    //printf("Imprimindo recursivo... ");
    //imprimeRecursivo(aux);
    printf("Quem quer remover ? ");
    scanf("%d",&n);
    funcaoRemove(&lista,n);
    imprimeLista(&lista);
}
