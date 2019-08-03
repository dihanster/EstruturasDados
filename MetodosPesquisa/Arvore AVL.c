#include<stdio.h>
#include<stdlib.h>

struct arvore{
    int info;
    int altura;
    struct arvore *esq;
    struct arvore *dir;
};typedef struct arvore tipoAVL;

int fatorBal(tipoAVL *aux){
    int fator;
    fator = (alturaNo(aux->esq) - alturaNo(aux->dir)); /*analisa e calcula a altura do no e calcula o fator*/
    if(fator < 0)
        fator = fator*(-1);
}

int alturaNo(tipoAVL *aux){
    if(aux == NULL)
        return -1;

    else
        return aux->altura;
}

int altura(tipoAVL *aux){
    int altEsq, altDir;
    if (aux == NULL)
        return 0;
    if (*aux == NULL)
        return 0;
    altEsq = altura(&((aux)->esq));
    altDir = altura(&((aux)->dir));
    if (altEsq > altDir)
        return (altEsq + 1);
    else
        return(altDir + 1);
}

int insereAVL(tipoABB *aux, int n){
    int ;
    if(aux == NULL){ /*se ta vazio*/
        tipoAVL *novo = (tipoAVL*) malloc(sizeof(tipoAVL));
        if(novo == NULL)
            return 0;
        novo->info = n;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    tipoAVL *temp = aux;
    if(n < temp->info){ /*se o numero é menor que o no atual, entao vamos pela esquerda*/
        if((res = insereAVL(&(atual->esq), valor)) == 1){
            if(fatorBal(temp) >= 2){ /*entao precisamos balancear*/
                if(n < aux->esq->info ){  /*entao rotaciona */
                    RotacaoLL(aux);
                }else{
                    RotacaoLR(aux);
                }
            }
        }
    }else{
        if(n > temp->info){
            if((res = insereAVL(&(temp->dir), valor)) == 1){
                if(fatorBal(temp) >= 2){
                    if(aux->dir->info < n){
                        RotacaoRR(aux);
                    }else{
                        RotacaoRL(aux);
                    }
                }
            }
        }else{
            return 0;
        }
    }
    temp->altura = maior(alturaAVL(temp->esq),alturaAVL(temp->dir)) + 1;
    return res;
}

void RotacaoLL(ArvAVL *A){
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
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

int main(){
    int i,qtd,n,testes, cont=0;
    scanf("%d",&testes);
    while(testes > 0){
        tipoABB *raiz = NULL;
        scanf("%d",&qtd);
        cont++;
        while(qtd > 0){
            scanf("%d",&n);
            if(raiz == NULL)
                raiz = insereNo(n);
            else
                insereABB(raiz, n);
            qtd--;
        }
        printf("\nCase %d:",cont);
        printf("\nPre.: ");
        preOrdem(raiz);
        printf("\nIn..: ");
        emOrdem(raiz);
        printf("\nPost: ");
        posOrdem(raiz);
	printf("\n");
	printf("\n");
        testes--;
    }
}
