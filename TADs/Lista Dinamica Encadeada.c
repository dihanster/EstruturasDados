#include<stdio.h>
#include<stdlib.h>

struct dados{
    int info;
    struct dados *prox;
};typedef struct dados tipoDado;

struct lista{
    tipoDado *primeiro;
    tipoDado *ultimo;
    int tamanho;
};typedef struct lista tipoLDE;

void iniciaLista(tipoLDE *listaAux){
    listaAux->ultimo = NULL;
    listaAux->primeiro = NULL;
    listaAux->tamanho = 0;
}

void insereFinal(tipoLDE *listaAux, int n){
    tipoDado *novo = (tipoDado*) malloc(sizeof(tipoDado));
    novo->info = n;
    if(listaAux->tamanho == 0){
        novo->prox = NULL;
        listaAux->primeiro = novo;
        listaAux->ultimo = novo;
    }
    else{
        novo->prox = NULL;
        listaAux->ultimo->prox = novo;
        listaAux->ultimo = novo;
    }
    listaAux->tamanho++;
}

void imprimeLista(tipoLDE *listaAux){
    tipoDado *aux = listaAux->primeiro;
    printf("Os numeros digitados foram: \n");
    while(aux != NULL){
        printf("%d ",aux->info);
        aux = aux->prox;
    }
}

void imprimeRecursivo(tipoDado *aux){
    if(aux != NULL){
        printf("%d ",aux->info);
        imprimeRecursivo(aux->prox);
    }
}

void funcaoRemove(tipoLDE *listaAux, int n){
    tipoDado *aux = listaAux->primeiro;
    tipoDado *temp = aux;
    while(aux != NULL ){
        if(aux->info == n){
            break;
        }
        temp = aux; /*temp e sempre o anteriror */
        aux = aux->prox;
    }
    if(aux == listaAux->primeiro){ /*entao remover no inicio*/
        listaAux->primeiro = aux->prox;
        free(aux);
    }
    else if(aux == listaAux->ultimo){
        listaAux->ultimo = temp;
        temp->prox = NULL;
        temp = temp->prox;
        free(temp);
    }
        else{ /*no meio*/
            temp->prox = aux->prox;
            free(aux);
        }
}

int main(){
    int n, qtd;
    tipoLDE lista;
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
    tipoDado *aux = lista.primeiro;
    printf("Imprimindo recursivo... ");
    //imprimeRecursivo(aux);
    printf("Quem quer remover ? ");
    scanf("%d",&n);
    funcaoRemove(&lista,n);
    imprimeLista(&lista);
}
