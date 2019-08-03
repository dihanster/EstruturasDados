#include<stdio.h>

void particao(int *v, int esq, int dir, int *i, int *j){
    int aux;
    *i = esq;
    *j = dir;
    int pivo = v[(*i+*j)/2];
    do{
        while(v[*i] < pivo )
            (*i)++;
        while(v[*j] > pivo)
            (*j)--;
        if(*i <= *j){
            aux = v[*i];
            v[*i] = v[*j];
            v[*j] = aux;
            (*i)++;
            (*j)--;
        }
    }while(*i <= *j);
}

void quickSort(int *v, int esq, int dir){
    int i, j;
    particao(v, esq, dir, &i, &j);
    if(esq < j)
        quickSort(v, esq, j);
    if(i < dir )
        quickSort(v, i, dir);
}

int main(){
    int i, v[10] = {1,10,8,9,5,3,6,7,4,0};
    quickSort(v,0,9);
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
