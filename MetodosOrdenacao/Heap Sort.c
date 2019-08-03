#include<stdio.h>
#include<stdlib.h>

void rearranjarHeap(int *v, int i, int tamanhoHeap){
    int esq, dir, maior, aux;
    esq = 2*i + 1; /*calculando o filho da esquerda*/
    dir = 2*i + 2;
    if((esq < tamanhoHeap) && (v[esq] > v[i])) /*se o elemento é menor que seu filho da esq*/
        maior = esq;
    else
        maior = i;
    if((dir < tamanhoHeap) && v[dir] > v[maior]) /*se o filho da direita é maior que o antigo maior ou o pai*/
        maior = dir;
    if(maior !=  i){ /*caso o pai era menor que um dos filhos, temos que trocar pelo maior*/
        aux = v[i];
        v[i] = v[maior];
        v[maior] = aux;
        rearranjarHeap(v,maior,tamanhoHeap);
    }
}

void constroiHeap(int *v, int n){
    int i;
    for(i=n/2-1;i>=0;i--){
        rearranjarHeap(v,i,n);
    }
}

void heapsort(int *v, int n){
    int i, aux, tamanhoHeap;
    constroiHeap(v,n); /*construindo o heap*/
    tamanhoHeap = n;
    for(i=n-1;i>0;i--){ /*dps do heap feito, devemos trocar o 1o elemento com o ultimo e decrementarn o tamannho*/
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        tamanhoHeap--;
        rearranjarHeap(v,0,tamanhoHeap);
    }
}

int main() {
    int i, A[8]={4,3,2,1,8,7,6,5};

    printf("Vetor original: ");
    for (i=0;i<8;i++)
        printf("%d ",A[i]);
    printf("\n");

    heapsort(A,8);

    printf("\nVetor ordenado: ");
    for (i=0;i<8;i++)
        printf("%d ",A[i]);

    return 0;
}
