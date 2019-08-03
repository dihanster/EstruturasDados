#include<stdio.h>
#include<stdlib.h>

void shellSort(int *v, int n, int *inc, int nInc){
    int i, j, h, incr, aux;
    for(incr=0;incr<nInc;incr++){
        h = inc[incr]; /*h vai comecar na ordem do vetor de incremento*/
        for(i=h;i<n;i++){
            aux = v[i];
            for(j=i-h;j>=0 && v[j] > aux;j-=h)
                v[j+h] = v[j];
            v[j+h] = aux;
        }
    }
}

int main() {
    int i, A[8]={8,7,6,5,4,3,2,1}, inc[3]={3,2,1};

    printf("Vetor original: ");
    for (i=0;i<8;i++)
        printf("%d ",A[i]);
    printf("\n");

    shellSort(A,8,inc,3);

    printf("\nVetor ordenado: ");
    for (i=0;i<8;i++)
        printf("%d ",A[i]);

    return 0;
}
