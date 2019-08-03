#include<stdio.h>

void insertionSort(int *v){
    int i, j, temp, sort;
    for(i=1;i < 3;i++){
        temp = v[i];
        j = i - 1;
        while(v[j] > temp && j >= 0){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = temp;
    }
}

int main(){
    int i; //v[10] = {0,9,3,5,4,2,8,1,7,6};
    int v[3] = {9, 12, 5};
    printf("O vetor desordenado eh\n");
    for(i=0;i<3;i++)
        printf("%d ",v[i]);
    insertionSort(v);
    printf("\nO vetor ordenado eh\n");
    for(i=0;i<3;i++)
        printf("%d ",v[i]);
    return 0;
}
