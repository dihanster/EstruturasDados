#include<stdio.h>
#include<stdlib.h>

#define MAXFila 100
#define INF 100

struct grafo{
    int **v;
    int numVertices;
};typedef struct grafo *tipoGrafo;

struct fila{
	int dado;
	int prioridade;
	struct fila  *prox;
};typedef struct fila tipoFila;

tipoFila* inicializa(){
    return NULL;
}

int vazia (tipoFila* f){
    return (f==NULL);
}

void imprime(tipoFila* f){
    if (!vazia(f)){
       tipoFila* t = f;
       printf("%d(%d) - ", t->dado, t->prioridade);

       while(t->prox != NULL){
          t = t->prox;
          printf("%d(%d) - ", t->dado, t->prioridade);
       }
    }
    else
       printf("");

    return;
}

tipoFila* cria(int v, int prioridade){
     tipoFila* p = (tipoFila*) malloc (sizeof(tipoFila));
     p->dado = v;
     p->prioridade = prioridade;
     return p;
}

tipoFila* enfileira(tipoFila* f, int dado, int prioridade){
     tipoFila* novo = cria(dado, prioridade);
     tipoFila* ant = NULL;
     tipoFila* p = f;

     while (p!=NULL && p->prioridade < prioridade){
         ant = p;
         p = p->prox;
     }

     if (ant == NULL){
         novo->prox = f;
         f = novo;
     }
     else{
         novo->prox = ant->prox;
         ant->prox = novo;
     }

     return f;
}

tipoFila* desenfileira(tipoFila* f, int v){
     tipoFila* ant = NULL;
     tipoFila* p = f;

     while (p != NULL && p->dado != v){
         ant = p;
         p = p->prox;
     }

     if (p == NULL)
         return f;

     if (ant == NULL)
         f= p->prox;
     else
         ant->prox = p->prox;

     free(p);

     return f;

}

int proxFila(tipoFila* f){
    if (f != NULL){
        tipoFila* temp = f;
        return temp->dado;
    }
    else
       return -1;

}

int busca (tipoFila *f, int letra){
    tipoFila* p;

    for(p = f; p != NULL; p = p->prox)
        if(p->dado == letra)
           return 1;

    return 0;
}


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

    /*
    for (i=0; i<grafo->numVertices; i++){
        printf("%d\t%d\t%d\n\n", i, d[i], pi[i]);
    }
    */
    return ;
}

void RELAX(tipoGrafo grafo, int u, int v, int* d, int* pi){

	if ((d[u] != INF) && (d[v] > d[u] + grafo->v[u][v])){
        d[v] = d[u] + grafo->v[u][v];
        pi[v] = u;
    }

    return ;
}

int DIJKSTRA(tipoGrafo grafo, int r, int* d, int* pi){

	int i, x;
    int j, y, aux[grafo->numVertices];

    INITIALIZE_SINGLE_SOURCE(grafo, 0, d, pi);

    tipoFila* S = inicializa();
    tipoFila* Q = inicializa();

    for (i=0; i<grafo->numVertices; i++){
        Q = enfileira(Q, i, d[i]);
    }

    //imprime(Q);

    while (!vazia(Q)){
        j=0;

        x = proxFila(Q);

        S = enfileira(S, x, d[x]);

        Q = desenfileira(Q, x);

        for (i=0; i < grafo->numVertices; i++){
            if ( grafo->v[x][i] != 0){
                aux[j] = i;
                j++;
            }
        }

        i=0;
		y=j;
		j=0;

        do{
            RELAX(grafo, x, aux[i], d, pi);
            i++;
			j++;
        }while(i<y);
    }

     return 0;

}

int main(){
	int i;
    tipoGrafo grafo = criaGrafo(7);
    int *d, *pi;

	d = (int *) malloc (7 * sizeof(int));
    pi = (int *) malloc (7 * sizeof(int));

	adicionaAresta(grafo, 0, 1, 5);
	adicionaAresta(grafo, 0, 2, 1);
	adicionaAresta(grafo, 1, 4, 5);
	adicionaAresta(grafo, 1, 2, 1);
	adicionaAresta(grafo, 2, 3, 1);
	adicionaAresta(grafo, 2, 5, 1);
    adicionaAresta(grafo, 3, 4, 1);
    adicionaAresta(grafo, 3, 5, 5);
	adicionaAresta(grafo, 3, 6, 5);
    adicionaAresta(grafo, 4, 6, 5);
    adicionaAresta(grafo, 5, 6, 5);
    printf("Matriz de adjacencia \n");
    imprimeGrafo(grafo);

    printf("\nResultdo do Algoritmo de Dijkstra\n");
    DIJKSTRA(grafo, 0, d, pi);

	printf("i\td[i]\tpi[i]\n\n");
    for (i=0; i<7; i++){
        printf("%d\t%d\t%d\t>>>>>>\t", i, d[i], pi[i]);

        if(pi[i] != -1)
           printf("arestas sombreadas(%d, %d)", pi[i], i);

        printf("\n\n");
     }


}
