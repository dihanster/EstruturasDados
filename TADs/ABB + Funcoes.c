#include<stdio.h>
#include<stdlib.h>

struct arvore{
int info;
struct arvore *esq;
struct arvore *dir;
};typedef struct arvore tipoABB;

void inicializa(int n, tipoABB *arvore){
    arvore->info = n;
    arvore->esq = NULL;
    arvore->dir = NULL;
}

tipoABB *iniciaRaiz(){
    return NULL;
}

tipoABB *criaNo(int n){
    tipoABB *novo = (tipoABB*) malloc(sizeof(tipoABB));
    novo->info = n;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void iniciaNo(tipoABB *aux,int n){
    if(n < aux->info){
    if(aux->esq == NULL)
        aux->esq = criaNo(n);
    else
        iniciaNo(aux->esq,n);
    }else
    if(n > aux->info){
        if(aux->dir == NULL)
            aux->dir = criaNo(n);
        else
            iniciaNo(aux->dir,n);
    }
}

void emOrdem(tipoABB *aux){
    if(aux != NULL ){
        emOrdem(aux->esq);
        printf("%d ",aux->info);
        emOrdem(aux->dir);
    }
}

void posOrdem(tipoABB *aux){
    if(aux != NULL ){
        posOrdem(aux->esq);
        posOrdem(aux->dir);
        printf("%d ",aux->info);
    }
}

void preOrdem(tipoABB *aux){
    if(aux != NULL ){
        printf("%d ",aux->info);
        preOrdem(aux->esq);
        preOrdem(aux->dir);
    }
}

tipoABB *buscaMenor(tipoABB *ABB){ /*while*/
    tipoABB *aux;
    while(ABB != NULL){
        aux = ABB;
        ABB = ABB->esq;
    }
        printf("\nMenor eh %d ",aux->info);
}

tipoABB *buscaMaior(tipoABB *ABB){ /*while*/
    tipoABB *aux;
    while(ABB->dir != NULL){
        ABB = ABB->dir;
    }
        printf("\nMaior eh %d ",ABB->info);
}

int contaFolha(tipoABB *arvore){
    if(arvore == NULL)
        return 0;
    if(arvore->esq == NULL && arvore->dir == NULL)
        return 1;
    return contaFolha(arvore->esq) + contaFolha(arvore->dir);
}

int contaNo(tipoABB *arvore){
    if(arvore == NULL)
        return 0;
    else
        return 1 + contaNo(arvore->esq) + contaNo(arvore->dir);
}

main(){
    tipoABB *raiz;
    raiz = criaNo(10);
    int qtd,n,cont=0;
    scanf("%d",&qtd);
    while(qtd>0){
        scanf("%d",&n);
        iniciaNo(raiz,n);
        qtd--;
    }
    printf("Em Ordem \n");
    emOrdem(raiz);
    printf("\nPos Ordem \n");
    posOrdem(raiz);
    printf("\nPreOrdem \n");
    preOrdem(raiz);
    buscaMenor(raiz);
    buscaMaior(raiz);
    int contFolha = contaFolha(raiz);
    printf("\nTem %d folhas ",contFolha);
    int nos = contaNo(raiz);
    printf("\nA Arvore tem %d nos ",nos);
}
