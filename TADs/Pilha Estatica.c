#include<stdio.h>
#include<stdlib.h>

#define MAX 10

struct pilha{
    int elementos[MAX];
    int topo;
    int tamanho;
};typedef struct pilha tipoPilha;

void iniciaPilha(tipoPilha *pilha){
    int i;
    for(i=0;i<MAX;i++){
        pilha->elementos[i] = 0;
    }
    pilha->topo = -1;
    pilha->tamanho = 0;
}

void empilha(tipoPilha *pilha){
    pilha->topo++;
    scanf("%d",&pilha->elementos[pilha->topo]);
    pilha->tamanho++;
}

void imprimePilha(tipoPilha *pilha){
    int i;
    for(i=0;i<pilha->tamanho;i++)
        printf("%d ",pilha->elementos[i]);
}

void desempilha(tipoPilha *pilha){
    pilha->elementos[pilha->topo] = 0;
    pilha->topo--;
    pilha->tamanho--;
}

int main(){
    int n, qtd;
    tipoPilha pilha;
    iniciaPilha(&pilha);
    printf("Quantos quer inserir?\n");
    scanf("%d",&qtd);
    printf("Digite os %d numeros\n",qtd);
    while(qtd > 0){
        empilha(&pilha);
        qtd--;
    }
    printf("Imprimindo...\n");
    imprimePilha(&pilha);
    desempilha(&pilha);
    imprimePilha(&pilha);
}
