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

struct fila{
    int tamanho;
    int primeiro;
    int ultimo;
    int items[MAXFila];
};typedef struct fila tipoFila;

tipoFila *criaFila(){

    tipoFila *fila = (tipoFila*) malloc(sizeof(tipoFila));
    fila->primeiro = 0;
    fila->ultimo = MAXFila-1;
    fila->tamanho = 0;

    return fila;
}

int vazia(tipoFila *fila){

    if(fila->tamanho == 0)
        return 1;
    else
        return 0;
}

void enfileira(tipoFila *fila, int item){

    if(fila->tamanho >= MAXFila)
        printf("Cheia!\n");
    else{
        fila->ultimo = (fila->ultimo+1) % MAXFila;
        fila->items[fila->ultimo] = item;
        fila->tamanho++;
    }
}

int desenfileira(tipoFila *fila){

    if(vazia(fila)){
        printf("Vazia!\n");
        return -1;
    }
    else{
        int desenfileira = fila->items[fila->primeiro];
        fila->primeiro = (fila->primeiro + 1) % MAXFila;
        fila->tamanho--;
        return desenfileira;
    }
}

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

void buscaLargura(tipoGrafo *grafo, int vertice){

	tipoFila *fila = criaFila();
	int tira;
	tipoListaAdj *listaAdj = grafo->vertices[vertice];
	grafo->visitados[vertice] = 1;
	enfileira(fila, vertice);

	while (!vazia(fila)){
		tira = desenfileira(fila);
		listaAdj = grafo->vertices[tira];
		while (listaAdj != NULL){
			if (grafo->visitados[listaAdj->item] == 0){
				printf("%d ", listaAdj->item);
				grafo->visitados[listaAdj->item] = 1;
				enfileira(fila, listaAdj->item);
			}
			listaAdj = listaAdj->proxVerticeAdj;
		}
	}
}

int main(){

	tipoGrafo *grafo = criaGrafo();
    /*printf("Inicializando o grafo...\n");
    printf("\nLegenda:");
    printf("\n1 - Paulinia\n2 - Piracicaba\n3 - Campinas\n4 - Sorocaba\n5 - Itu\n6 - Jundiai\n7 - Sao Paulo\n");
	adicionaAresta(grafo, 1, 2);
	adicionaAresta(grafo, 1, 3);
	adicionaAresta(grafo, 2, 3);
	adicionaAresta(grafo, 2, 4);
	adicionaAresta(grafo, 3, 5);
	adicionaAresta(grafo, 3, 6);
	adicionaAresta(grafo, 4, 7);
    adicionaAresta(grafo, 5, 4);
    adicionaAresta(grafo, 5, 6);
	adicionaAresta(grafo, 5, 7);
    adicionaAresta(grafo, 6, 7);*/
    adicionaAresta(grafo, 1, 1);
	adicionaAresta(grafo, 2, 2);
	adicionaAresta(grafo, 3, 3);
	adicionaAresta(grafo, 4, 4);
	adicionaAresta(grafo, 5, 5);
    printf("\nResultado da busca em largura:\n1 ");
    buscaLargura(grafo, 1);
	return 0;
}
