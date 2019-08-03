#include<stdio.h>
#include<stdlib.h>

struct dados{
    int info;
    struct dados *ant;
};typedef struct dados tipoDado;

struct pilha{
    tipoDado *topo;
    int tamanho;
};typedef struct pilha tipoPilha;

void iniciaPilha(tipoPilha *pilha){
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

void empilha(tipoPilha *pilha, int n){
    tipoDado *novo = (tipoDado*) malloc(sizeof(tipoDado));
    novo->info = n;
    if(pilha->topo == NULL){
        novo->ant = NULL;
        pilha->topo = novo;
    }
    else{
        novo->ant = pilha->topo;
        pilha->topo = novo;
    }
    pilha->tamanho++;
}

void desempilha(tipoPilha *pilha){
    tipoDado *aux = pilha->topo;
    pilha->topo = aux->ant;
    free(aux);
}

void imprimePilha(tipoPilha *pilha){
    tipoDado *aux = pilha->topo;
    printf("Imprimindo... :D \n");
    while(aux != NULL){
        printf("%d ",aux->info);
        aux = aux->ant;
    }
}

int main(){
    int n, qtd;
    tipoPilha pilha;
    iniciaPilha(&pilha);
    printf("Quantos elementos deseja inserir na pilha ?\n");
    scanf("%d",&qtd);
    printf("Digite os %d numeros\n",qtd);
    while(qtd > 0){
        scanf("%d",&n);
        empilha(&pilha, n);
        qtd--;
    }
    imprimePilha(&pilha);
    printf("\nQuanto quer remover ? :c \n");
    scanf("%d",&qtd);
    while(qtd > 0){
        desempilha(&pilha);
        qtd--;
    }
    printf("Nova pilha:\n");
    imprimePilha(&pilha);
}
