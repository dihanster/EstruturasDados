#include<stdio.h>
#include<stdlib.h>

#define MAX 5

struct filaCircular{
    int primeiro;
    int ultimo;
    int elementos[MAX];
};typedef struct filaCircular tipoFC;

void iniciaFila(tipoFC *fila){
    int i;
    fila->primeiro = -1;
    fila->ultimo   = -1;
    for(i=0;i<MAX;i++){
        fila->elementos[i] = 0;
    }
}

int filaVazia(tipoFC *fila){
    if(fila->ultimo  == fila->primeiro && fila->ultimo == -1){
        printf("Fila Vazia\n");
        return 1;
    }
    else
        return 0;
}

int filaCheia(tipoFC *fila){
    if(((fila->ultimo + 1) % MAX) == fila->primeiro){
        printf("Fila Cheia\n");
        return 1;
    }
    else
        return 0;
}

void filaInsere(tipoFC *fila){
    int pos,n;
    pos = (fila->ultimo + 1)%MAX;
    scanf("%d",&n);
    if(filaVazia(fila) == 1 ){
        fila->primeiro = 0;
        fila->ultimo = 0;
        fila->elementos[0] = n;
    }
    else if(filaCheia(fila) != 1){
            fila->elementos[pos] = n;
            fila->ultimo = pos;
    }
          else
            printf("Cheia, não pode mais inserir ");
}

void imprime(tipoFC *fila){
    int i;
    for(i=fila->primeiro;i<=fila->ultimo;i++){
        printf("%d ",fila->elementos[i]);
    }
}

void removeFila(tipoFC *fila){
    fila->elementos[fila->primeiro] = 0;
    fila->primeiro = fila->primeiro + 1;
}

void imprimeReverso(tipoFC *fila){
    int i;
    printf("\nImprimindo Reverso\n");
    for(i=MAX-1;i>=fila->primeiro;i--){
        printf("%d ",fila->elementos[i]);
    }
}

void buscaMaior(tipoFC *fila){
    int i,maior=0,pos;
    for(i=fila->primeiro;i<fila->ultimo+1;i++){
        if(fila->elementos[i] > maior){
            maior = fila->elementos[i];
            pos = i;}
    }
    printf("\nMaior elemento esta na posicao %d \n",pos+1);
}

void removePrioridade(tipoFC *fila){
    int i,maior=0,pos;
    for(i=fila->primeiro;i<MAX;i++){
        if(fila->elementos[i] > maior){
            maior = fila->elementos[i];
            pos = i;
        }
    }
    if(pos == fila->primeiro){ /*primeiro e o proximo agora*/
        fila->elementos[pos] = 0;
        fila->primeiro = (pos+1) % MAX;
        printf("\nNovo primeiro eh %d\n",fila->primeiro);
    }
    else
        if(pos == fila->ultimo){  /*ultimo e o anterior agora */
            fila->elementos[pos] = 0;
            fila->ultimo = ((MAX+pos)-1) % MAX;
            printf("\nNovo ultimo eh %d\n",fila->elementos[fila->ultimo]);
        }
    else{ /*vamos ter que deslocar e o ultimo e o ant dps de deslocar tudo*/
        for(i=pos;i<=fila->ultimo;i++){
            fila->elementos[i] = fila->elementos[i+1];
        }
        fila->ultimo = ((MAX+ fila->ultimo)-1) % MAX;
    }
}

int main(){
    tipoFC fila;
    iniciaFila(&fila);
    filaCheia(&fila);
    filaVazia(&fila);
    int qtd = MAX;
    while(qtd > 0 ){
        filaInsere(&fila);
        qtd--;
    }
    imprime(&fila);
    //removeFila(&fila);
    //imprime(&fila);
    //filaInsere(&fila);
    //imprime(&fila);
    imprimeReverso(&fila);
    buscaMaior(&fila);
    removePrioridade(&fila);
    imprime(&fila);
}
