#include <stdio.h>
#include <stdlib.h>

#define MAXGrafo 20
#define MAXFila 20

struct listaAdj{
	int item;
	struct listaAdj *proxVerticeAdj;
};typedef struct listaAdj tipoListaAdj;

struct grafo{
	tipoListaAdj *vertices[MAXGrafo];
	short visitados[MAXGrafo];
};typedef struct grafo tipoGrafo;

tipoListaAdj* crialistaAdj(int item){

	tipoListaAdj *listaAdj = (tipoListaAdj*) malloc(sizeof(tipoListaAdj));
	listaAdj->item = item;
	listaAdj->proxVerticeAdj = NULL;

	return listaAdj;
}

tipoGrafo *criaGrafo(){

	tipoGrafo *grafo = (tipoGrafo*) malloc(sizeof(tipoGrafo));
	int i;

	for (i = 1; i <= MAXGrafo - 1; i++){
		grafo->vertices[i] = NULL;
		grafo->visitados[i] = 0;
	}

	return grafo;
}

void adicionaAresta(tipoGrafo *grafo, int verticeX, int verticeY){

	tipoListaAdj *vertice;
	vertice = crialistaAdj(verticeY);
	vertice->proxVerticeAdj = grafo->vertices[verticeX];
	grafo->vertices[verticeX] = vertice;

    /* Para grafos nao orientados :
	vertice = crialistaAdj(verticeX);
	vertice->proxVerticeAdj = grafo->vertices[verticeY];
	grafo->vertices[verticeY] = vertice;
    */
}

void buscaProfundidade(tipoGrafo *grafo, int vertice){

	grafo->visitados[vertice] = 1;
	printf("%d\n", vertice);
	tipoListaAdj *listaAdj = grafo->vertices[vertice];

	while (listaAdj != NULL){
		if (!grafo->visitados[listaAdj->item]){
			buscaProfundidade(grafo, listaAdj->item);
		}
		listaAdj = listaAdj->proxVerticeAdj;
	}
}


int main(){

	tipoGrafo *grafo = criaGrafo();
    printf("Inicializando o grafo...\n");
	adicionaAresta(grafo, 1, 2);
	adicionaAresta(grafo, 1, 3);
	adicionaAresta(grafo, 2, 3);
	adicionaAresta(grafo, 2, 4);
	adicionaAresta(grafo, 3, 5);
	adicionaAresta(grafo, 3, 6);
	adicionaAresta(grafo, 4, 7);
    adicionaAresta(grafo, 5, 4);
    adicionaAresta(grafo, 5, 7);
	adicionaAresta(grafo, 5, 6);
    adicionaAresta(grafo, 6, 7);
    printf("Resultado da busca em profundidade:\n");
    buscaProfundidade(grafo, 1);
	return 0;
}
