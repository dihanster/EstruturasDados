#include<stdio.h>
#include<stdlib.h>

struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
};typedef struct arvore tipoABB;

tipoABB* insereNo(int n){
    tipoABB *novo = (tipoABB*) malloc(sizeof(tipoABB));
    novo->info = n;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void insereABB(tipoABB *aux, int n){
    if(aux->info > n){
        if(aux->esq == NULL)
            aux->esq = insereNo(n);
        else
            insereABB(aux->esq,n);
    }
    else if(aux->info < n){
            if(aux->dir == NULL)
                aux->dir = insereNo(n);
            else
                insereABB(aux->dir,n);
    }
}


tipoABB* funcaoRemove(tipoABB *aux, int n){
    if(aux == NULL)
        return NULL;
    else if(aux->info < n)
            aux->dir = funcaoRemove(aux->dir, n);
        else if(aux->info > n)
            aux->esq = funcaoRemove(aux->esq,n);
    else{
        if(aux->dir == NULL && aux->esq == NULL){
            free(aux);
            aux = NULL;
        }
        else if(aux->dir != NULL && aux->esq != NULL){ /*entao tem dois filhos*/
                /*vamos procurar o maior da direita*/
                tipoABB *temp = aux->esq;
                while(temp->dir != NULL){
                    temp = temp->dir;
                }
                aux->info = temp->info;
                temp->info = n;
                aux->esq = funcaoRemove(aux->esq,n);}
            else{ /*entao tem uma filho*/
                tipoABB *temp = aux;
                if(aux->dir == NULL){ /*entao tem filho na esquerda*/
                    temp = aux->esq;
                    aux->info = temp->info;
                    temp->info = n;
                    aux->esq = funcaoRemove(aux->esq,n);
                }
                else if(aux->esq == NULL){
                        temp = aux->dir;
                        aux->info = temp->info;
                        temp->info = n;
                        aux->dir = funcaoRemove(aux->dir,n);
                     }
            }
        }
    return aux;
}

void imprimeABB(tipoABB *raiz){
    if(raiz != NULL){
        imprimeABB(raiz->esq);
        printf("%d ",raiz->info);
        imprimeABB(raiz->dir);
    }
}

int main(){
    int i,qtd,n;
    tipoABB *raiz = NULL;
    printf("Quantos elementos  deseja inserir?");
    scanf("%d",&qtd);
    printf("Digite os %d numeros ",qtd);
    while(qtd>0){
        scanf("%d",&n);
        if(raiz == NULL)
            raiz = insereNo(n);
        else
            insereABB(raiz, n);
        qtd--;
    }
    printf("Imprimindo... :D ");
    imprimeABB(raiz);
    printf("Quem quer remover ? :/ ");
    scanf("%d",&n);
    raiz = funcaoRemove(raiz,n);
    imprimeABB(raiz);
}


