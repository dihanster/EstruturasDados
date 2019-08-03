#include<stdio.h>
#include<stdlib.h>

#define INF 1000

struct grafo{
    int **v;
    int numVertices;
};typedef struct grafo *tipoGrafo;

tipoGrafo criaGrafo(int numVertices){
    int i, j;

    tipoGrafo grafo = (tipoGrafo) malloc(sizeof(tipoGrafo));
    grafo->numVertices = numVertices;

    grafo->v = (int **) malloc(numVertices * sizeof(int*));

    if(grafo->v == NULL)
        return NULL;

    for(i = 0; i < numVertices; i++){
        grafo->v[i] = (int *) malloc(numVertices * sizeof(int));
        if(grafo->v[i] == NULL)
            return NULL;
        for(j = 0; j < numVertices; j++)
            grafo->v[i][j] = INF;
    }
    return grafo;
}

int adicionaAresta(tipoGrafo grafo, int origem, int destino, int peso){

    grafo->v[origem][destino] = peso;

}

void imprimeGrafo(tipoGrafo grafo){
    int i, j;

    for(i = 0; i < grafo->numVertices; i++){
        for(j = 0; j < grafo->numVertices; j++){
            printf("%d ", grafo->v[i][j]);
        }
        printf("\n");
    }

}

int FLOYDWARSHALL(tipoGrafo grafo){
    int i, j, k, distancia[grafo->numVertices][grafo->numVertices];

    for(i = 0; i < grafo->numVertices; i++)
        for(j = 0; j < grafo->numVertices; j++){
            distancia[i][j] = grafo->v[i][j];
            if(i == j)
                distancia[i][j] = 0;
        }

    for(k = 0; k < grafo->numVertices; k++)
        for(i = 0; i < grafo->numVertices; i++)
            if(i != k && grafo->v[i][k] < INF)
                for(j = 0; j < grafo->numVertices; j++)
                    if( distancia[i][j] > (distancia[i][k] + distancia[k][j]) )
                        distancia[i][j] = (distancia[i][k] + distancia[k][j] );


	for(i = 0; i < grafo->numVertices; i++){
        for(j = 0; j < grafo->numVertices; j++)
            printf("%d ", distancia[i][j]);
        printf("\n");
    }
}

int main(){
    tipoGrafo grafo = criaGrafo(7);

	adicionaAresta(grafo, 0, 1, 5);
	adicionaAresta(grafo, 0, 2, 1);
	adicionaAresta(grafo, 1, 3, -5);
	adicionaAresta(grafo, 1, 2, 1);
	adicionaAresta(grafo, 2, 4, 1);
	adicionaAresta(grafo, 2, 5, -1);
    adicionaAresta(grafo, 3, 6, 5);
    adicionaAresta(grafo, 4, 3, 1);
	adicionaAresta(grafo, 4, 5, 5);
    adicionaAresta(grafo, 4, 6, -5);
    adicionaAresta(grafo, 5, 6, 5);

    printf("Matriz de adjacencia \n");
    imprimeGrafo(grafo);

    printf("\nResultdo do Algoritmo de FLOYD WARSHALL\n");
    FLOYDWARSHALL(grafo);

    return 0;
}
