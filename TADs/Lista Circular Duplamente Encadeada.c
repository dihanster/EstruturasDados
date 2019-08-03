#include<stdio.h>
#include<stdlib.h>

struct dados{
    int info;
    struct dados *prox;
    struct dados *ant;
};typedef struct dados tipoDado;

struct lista{
    tipoDado *primeiro;
    tipoDado *ultimo;
    int tamanho;
};typedef struct lista tipoLCDDE;

void iniciaLista(tipoLCDDE *lista){
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
}

void inserefinal(tipoLCDDE *lista, int n ){
    tipoDado *novo = (tipoDado*) malloc(sizeof(tipoDado));
    novo->info = n;
    if(lista->tamanho == 0){
        novo->ant = novo;
        novo->prox = novo;
        lista->primeiro = novo;
        lista->ultimo = novo;
    }
    else{
        novo->ant = lista->ultimo;
        lista->ultimo->prox = novo;
        lista->primeiro->ant = novo;
//        novo->ant = lista->primeiro->ant->prox;
        lista->ultimo = novo;
        novo->prox = lista->primeiro;
    }
    lista->tamanho++;
}

void imprimeLista(tipoLCDDE *lista){
    tipoDado *aux = lista->primeiro;
    int i;
    if(aux == NULL)
        printf("Lista Vazia :( \n ");
    for(i=0;i<lista->tamanho;i++){
        printf("%d ",aux->info);
        aux = aux->prox;
    }
}

void remocao(tipoLCDDE *lista, int n){
    int i;
    tipoDado *aux = lista->primeiro;

    while (aux != NULL){
        if (aux->info == n)
            break;
        else
            aux = aux->prox;
    }

    if(aux == lista->primeiro){ /*remocao do primeiro*/
        lista->primeiro = aux->prox;
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }
    if(aux == lista->primeiro->ant){ /*remocao do ultimo*/
        lista->primeiro->ant = aux->ant;
        aux->ant->prox;
    }
    free(aux);
    lista->tamanho--;
}


void remocao2(tipoLCDDE *lista, int n){
    int i;
    tipoDado *aux = lista->primeiro;
    tipoDado *auxUltimo = lista->primeiro->ant;

    while (aux != NULL){
        if (aux->info == n)
            break;
        else
            aux = aux->prox;
    }

    if (aux == lista->primeiro){ /*Remocao do primeiro*/
        auxUltimo->prox = aux->prox;
        lista->primeiro = aux->prox;
        aux->prox->ant = auxUltimo;
    }
    else{
        if (aux == lista->ultimo){ /*Remocao do ultimo*/
        //printf("to aqui");
        //lista->primeiro->ant = auxUltimo;
        lista->primeiro->ant = lista->ultimo->ant;
        lista->ultimo->prox = lista->primeiro;
//        auxUltimo->ant->prox = lista->primeiro;
        //lista->primeiro->ant = aux->ant;
        //aux->ant->prox = lista->primeiro;
        //lista->primeiro->ant = aux->ant;
    }
        else { /*Meio */
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
        }
    }
    free(aux);
    lista->tamanho--;
}

int main(){
    int n, qtd;
    tipoLCDDE lista;
    iniciaLista(&lista);
    printf("Quantos numeros deseja inserir ? :D \n");
    scanf("%d",&qtd);
    printf("Digite os %d numeros \n",qtd);
    while(qtd > 0){
        scanf("%d",&n);
        inserefinal(&lista,n);
        qtd--;
    }
    printf("Imprimindo ...\n");
    imprimeLista(&lista);
    printf("Quem deseja remover ?\n");
    scanf("%d",&n);
    remocao2(&lista,n);
    printf("Imprimindo ...\n");
    imprimeLista(&lista);
    //printf("\n");
    //inserefinal(&lista, 10);
    //imprimeLista(&lista);
}
