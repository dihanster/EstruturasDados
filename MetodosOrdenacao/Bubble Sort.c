#include<stdio.h>

void bubbleSort(int *v){
    int i, j, aux;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

int main(){
    int i, v[10] = {0,9,3,5,4,2,8,1,7,6};
    printf("O vetor desordenado eh\n");
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    bubbleSort(v);
    printf("\nO vetor ordenado eh\n");
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
