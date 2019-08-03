#include<stdio.h>
#include<stdlib.h>

#define INF 100

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
            grafo->v[i][j] = 0;
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

void INITIALIZE_SINGLE_SOURCE(tipoGrafo grafo, int s, int* d, int* pi){
    int i;

    for (i=0; i<grafo->numVertices; i++){
        d[i] = INF;
        pi[i] = -1;
    }

    d[s] = 0 ;

    return ;
}

void RELAX(tipoGrafo grafo, int u, int v, int* d, int* pi){

	if ((d[u] != INF) && (d[v] > d[u] + grafo->v[u][v])){
        d[v] = d[u] + grafo->v[u][v];
        pi[v] = u;
    }

    return ;
}

int BELLMANFORD(tipoGrafo grafo, int s, int* d, int* pi){

	 int i, j, l, cont = 0;

    INITIALIZE_SINGLE_SOURCE(grafo, s, d, pi);


    for (i = 0; i < (grafo->numVertices-1); i++){
        for (j = 0; j < grafo->numVertices; j++){
            for (l = 0; l < grafo->numVertices; l++){
                if (grafo->v[j][l] != 0){
                    cont++;
                    RELAX(grafo, j, l, d, pi);
                }
            }
        }
        cont = 0;
    }

     for (j = 0; j < grafo->numVertices; j++){
            for (l = 0; l < grafo->numVertices; l++){
                if (grafo->v[j][l] != 0){
                    if (d[l] > d[j] + grafo->v[j][l]){
                        printf("Nao deu... o grafo contem ciclos negativos :/ \n");
                        return 0;
                    }
                }
            }
        }

    printf("Sucesso! Resultado: \n");
    for (j = 0; j < grafo->numVertices; j++)
        printf("%d ", d[j]);

     return 1;
}

int main(){

    int *d, *pi;

    /*Pro grafo 1
    tipoGrafo grafo = criaGrafo(7);
    d = (int *) malloc (7 * sizeof(int));
    pi = (int *) malloc (7 * sizeof(int));
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

    printf("\nResultdo do Algoritmo de BELLMAN FORD\n");
    BELLMANFORD(grafo, 0, d, pi);

    */

     //Pro Grafo 2
    tipoGrafo grafo = criaGrafo(6);
    d = (int *) malloc (6 * sizeof(int));
    pi = (int *) malloc (6 * sizeof(int));

    adicionaAresta(grafo, 0, 4, -1);
	adicionaAresta(grafo, 1, 0, 1);
	adicionaAresta(grafo, 1, 3, 2);
	adicionaAresta(grafo, 2, 1, 2);
	adicionaAresta(grafo, 2, 5, -8);
	adicionaAresta(grafo, 3, 0, -4);
	adicionaAresta(grafo, 3, 4, 3);
	adicionaAresta(grafo, 4, 1, 7);
	adicionaAresta(grafo, 5, 1, 5);
    adicionaAresta(grafo, 5, 2, 10);

    printf("Matriz de adjacencia \n");
    imprimeGrafo(grafo);

    printf("\nResultdo do Algoritmo de BELLMAN FORD\n");
    BELLMANFORD(grafo, 5, d, pi);
   // */

    return 0;
}
