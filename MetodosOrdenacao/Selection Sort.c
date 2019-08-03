#include<stdio.h>

void selectionSort(int *v){
    int i, j, min, aux;
    for(i=0;i<10;i++){
        min = i;  /*min eh a posicao atual do i*/
        for(j=i+1;j<10;j++){
            if(v[min] > v[j])  /*para achar o novo minimo*/
                min = j;
        }
        aux = v[i];         /*entao troca*/
        v[i] = v[min];
        v[min] = aux;
    }
}

int main(){
    int i, v[10] = {0,9,3,5,4,2,8,1,7,6};
    printf("O vetor desordenado eh\n");
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    selectionSort(v);
    printf("\nO vetor ordenado eh\n");
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
