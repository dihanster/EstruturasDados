/*
/  Willian Dihanster Gomes de Oliveira  RA: 112269
/  Trabalho 02: Recuperacao de imagens usando Arvores B
/  Curso: Algoritmos e Estrutura de Dados II Profª Lilian Berton
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define t 4
#define minChaves 3
#define maxChaves 7
#define minFilhos 4
#define maxFilhos 8

typedef struct categoria{
    char nome[40];
}categoria;

typedef struct noAB *tipoAB;
typedef struct noAB{
    short numChaves; /*qtd de chaves no no*/
    categoria chaves[maxChaves]; /*as chaves*/
    tipoAB filhos[maxFilhos]; /*ponteiros para os filhos*/
}noAB;

void inicializa(tipoAB *dicionario){
    *dicionario = NULL;
}

int ehInterno(tipoAB no){
    return (no != NULL) && (no->filhos[0] != NULL);
}

int ehExterno(tipoAB no){
    return (no != NULL) && (no->filhos[0] == NULL);
}

int buscaBinaria(tipoAB no, char *nome){
    int tam = strlen(nome);
    int meio, i, f;
    i = 0;
    f = no->numChaves-1;
    while (i <= f){
        meio = (i + f)/2;
        if (strncmp(no->chaves[meio].nome, nome, tam) == 0)
            return meio;
        else
            if (strcmp(no->chaves[meio].nome, nome) > 0)
                f = meio - 1;
            else
                i = meio + 1;
    }
    return i;
}

void insereChave(tipoAB raiz, categoria nome, tipoAB filhoDir){
    short nAchou;
    int k = raiz->numChaves;
    nAchou = (k > 0);
    while(nAchou ){
        if(strcmp(nome.nome, raiz->chaves[k-1].nome) >= 0){
           nAchou = 0;
           break;
        }
        raiz->chaves[k] = raiz->chaves[k-1];
        raiz->filhos[k+1] = raiz->filhos[k];
        k--;
        if(k < 1)
            nAchou = 0;
    }
    raiz->chaves[k] = nome;
    raiz->filhos[k+1] = filhoDir;
    raiz->numChaves++;
}

void *insereNo(tipoAB raiz, categoria nome, short *cresceu, categoria *infoRetorno, tipoAB *auxRetorno){
    long i = 1, j;
    tipoAB temp;
    if(raiz == NULL){ /*eh uma folha*/
        *cresceu = 1;
        *infoRetorno =  nome;
        (*auxRetorno) = NULL;
        return;
    }
    while(i < raiz->numChaves && strcmp(nome.nome, raiz->chaves[i-1].nome) > 0 )
        i++;
    if(strcmp(nome.nome, raiz->chaves[i-1].nome) == 0){
        printf("Repetido ");
        *cresceu = 0;
        return;
    }
    if(strcmp(nome.nome, raiz->chaves[i-1].nome) < 0)
        i--;
    insereNo(raiz->filhos[i], nome, cresceu, infoRetorno, auxRetorno);
    if(!*cresceu)
        return;
    if(raiz->numChaves < maxChaves){ /*se ainda tem espaco*/
        insereChave(raiz, *infoRetorno, *auxRetorno);
        *cresceu = 0;
        return;
    }
    temp = (tipoAB) malloc(sizeof(noAB)); /*entao precisa dividir*/
    temp->numChaves = 0;
    temp->filhos[0] = NULL;
    if(i < minChaves+1){
        insereChave(temp, raiz->chaves[maxChaves-1], raiz->filhos[maxChaves]);
        raiz->numChaves--;
        insereChave(raiz, *infoRetorno, *auxRetorno);
    }
    else
        insereChave(temp, *infoRetorno, *auxRetorno);
    for (j = minChaves + 2; j <= maxChaves; j++)
        insereChave(temp, raiz->chaves[j-1], raiz->filhos[j]);
    raiz->numChaves = minChaves;
    temp->filhos[0] = raiz->filhos[minChaves+1];
    *infoRetorno = raiz->chaves[minChaves];
    *auxRetorno = temp;
}

void insereAB(tipoAB *raiz, categoria nome){
    short cresceu;
    categoria infoRetorno;
    noAB *auxRetorno, *novaRaiz;
    insereNo(*raiz, nome, &cresceu, &infoRetorno, &auxRetorno);
    if(cresceu){
        novaRaiz = (noAB*) malloc(sizeof(noAB));
        novaRaiz->numChaves = 1;
        novaRaiz->chaves[0] = infoRetorno;
        novaRaiz->filhos[0] = *raiz;
        novaRaiz->filhos[1] = auxRetorno;
        *raiz = novaRaiz;
    }
}

void emOrdem(tipoAB raiz){
    int i;
    if (raiz != NULL){
        for (i = 0; i < raiz->numChaves; i++){
            emOrdem(raiz->filhos[i]);
            printf("\n");
            printf("%s", raiz->chaves[i].nome);
        }
        emOrdem(raiz->filhos[i]);
    }
}

void imprimeI(tipoAB  p, int nivel){
    long i;
    if (p == NULL)
        return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->numChaves; i++)
        printf("%s ",p->chaves[i].nome);
    printf("\n");
    nivel++;
    for (i = 0; i <= p->numChaves; i++)
        imprimeI(p->filhos[i], nivel);
}

void imprimeNivel(tipoAB p){
    int  n = 0;
    imprimeI(p, n);
}

int emprestaDireita(int i, int m, tipoAB esq, tipoAB raiz, tipoAB dir){
    int j;

    for (j = 1; j < m; j++)
        insereChave(esq, dir->chaves[j - 1], dir->filhos[j]);
    raiz->chaves[i] = dir->chaves[m - 1];
    dir->filhos[0] = dir->filhos[m];
    for (j = m; j < dir->numChaves; j++) {
        dir->chaves[j - m] = dir->chaves[j];
        dir->filhos[j - m + 1] = dir->filhos[j + 1];
    }
    dir->numChaves -= m;

    return 0;
}

int emprestaEsquerda(int i, int m, tipoAB esq, tipoAB raiz, tipoAB dir){
    int j;

    for (j = 1; j < m; j++)
        insereChave(dir, esq->chaves[esq->numChaves - j], esq->filhos[esq->numChaves - j + 1]);
    raiz->chaves[i - 1] = esq->chaves[esq->numChaves - m];
    dir->filhos[0] = esq->filhos[esq->numChaves - m + 1];
    esq->numChaves -= m;

    return 0;
}

int intercala(int i, tipoAB esq, tipoAB raiz, tipoAB dir){
    int j;

    for (j = 1; j <= minChaves; j++)
        insereChave(esq, dir->chaves[j - 1], dir->filhos[j]);
    free(dir);
    for (j = i + 1; j < raiz->numChaves; j++) {
        raiz->chaves[j - 1] = raiz->chaves[j];
        raiz->filhos[j] = raiz->filhos[j + 1];
    }
    raiz->numChaves--;

    return (raiz->numChaves < minChaves);
}

int reconstitui(int i, tipoAB raiz){
    tipoAB esq, dir;
    int j, m;

    if (i < raiz->numChaves) {
        esq = raiz->filhos[i];
        dir = raiz->filhos[i + 1];
        insereChave(esq, raiz->chaves[i], dir->filhos[0]);
        m = (dir->numChaves - minChaves + 1) / 2;
        if (m > 0)     /*se tem, podemos pegar emprestado*/
            return emprestaDireita(i, m, esq, raiz, dir);
        else         /*se nao, faz a fusao dos dois*/
            return intercala(i, esq, raiz, dir);
    }
    else {
        esq = raiz->filhos[i - 1];
        dir = raiz->filhos[i];
        insereChave(dir, raiz->chaves[i - 1], dir->filhos[0]);
        m = (esq->numChaves - minChaves + 1) / 2;
        if (m > 0)     /*se tem, podemos pegar emprestado, da esquerda*/
            return emprestaEsquerda(i, m, esq, raiz, dir);
        else           /*se nao, faz a fusao dos dois*/
            return intercala(i, esq, raiz, dir);
    }
}

int predecessor(int i, tipoAB q, tipoAB r){
    if (r->filhos[r->numChaves] != NULL) {
        if (predecessor(i, q, r->filhos[r->numChaves]))
            return reconstitui(r->numChaves, r);
        return 0;
    }
    else {
        q->chaves[i] = r->chaves[r->numChaves - 1];
        r->numChaves--;
        return (r->numChaves < minChaves);
    }
}

int removeInterno(int i, tipoAB no){
    if (predecessor(i, no, no->filhos[i]))
        return reconstitui(i, no);
    return 0;
}

int removeExterno(int i, tipoAB no){
    int j;

    for (j = i + 1; j < no->numChaves; j++) {
        no->chaves[j - 1] = no->chaves[j];
        no->filhos[j]   = no->filhos[j + 1];
    }
    no->numChaves--;

    return (no->numChaves < minChaves);
}

int removeRecursivo(tipoAB no, char *nome, int *testeRemove){
    int i, tam = strlen(nome);

    *testeRemove = *testeRemove + 1;
    if (no != NULL) {
        i = buscaBinaria(no, nome);
        if ((i < no->numChaves) && (strncmp(nome, no->chaves[i].nome, tam) == 0)) {
            if (ehExterno(no))
                return removeExterno(i, no);
            else
                return removeInterno(i, no);
            *testeRemove = *testeRemove + 1;
        }
        else if (removeRecursivo(no->filhos[i], nome, testeRemove)) /*se a altura diminuiu*/
            return reconstitui(i, no);
        *testeRemove = *testeRemove + 1;
    }
    *testeRemove = 0;
    return 0;  /*nao achou*/
}

int removeNome(tipoAB *raiz, char *nome, int *testeRemove){
    tipoAB no = *raiz;
    if (removeRecursivo(no, nome, testeRemove) && (no->numChaves == 0)) { /*se a altura diminuiu*/
        *raiz = no->filhos[0];
        free(no);
    }
}

int buscaEmOrdem(tipoAB raiz, char *nome, int *testeBusca){
    int i, tamNom, tam;
    tam = strlen(nome);
    if (raiz != NULL){
        for (i = 0; i < raiz->numChaves; i++){
            buscaEmOrdem(raiz->filhos[i], nome, testeBusca);
            if(strncmp(raiz->chaves[i].nome, nome, tam) == 0){
                tamNom = strlen(raiz->chaves[i].nome);
                if(tam == tamNom-1){
                    printf("\n");
                    printf("%s", raiz->chaves[i].nome);
                    *testeBusca = *testeBusca + 1;
                }
            }
        }
        buscaEmOrdem(raiz->filhos[i], nome, testeBusca);
    }
}

void imprimeImagem(char *nome){
    ALLEGRO_DISPLAY *janela = NULL;

    ALLEGRO_BITMAP *imagem1 = NULL;
    ALLEGRO_BITMAP *imagem2 = NULL;
    ALLEGRO_BITMAP *imagem3 = NULL;
    ALLEGRO_BITMAP *imagem4 = NULL;
    ALLEGRO_BITMAP *imagem5 = NULL;

    char auxNome[100];
    strcpy(auxNome, nome);

    al_init();
    al_init_image_addon();
    janela = al_create_display(600, 400);

    strcat(nome,"1.jpg");
    imagem1 = al_load_bitmap(nome);

    strcpy(nome, auxNome);
    strcat(nome,"2.jpg");
    imagem2 = al_load_bitmap(nome);

    strcpy(nome, auxNome);
    strcat(nome,"3.jpg");
    imagem3 = al_load_bitmap(nome);

    strcpy(nome, auxNome);
    strcat(nome,"4.jpg");
    imagem4 = al_load_bitmap(nome);

    strcpy(nome, auxNome);
    strcat(nome,"5.jpg");
    imagem5 = al_load_bitmap(nome);

    al_draw_bitmap(imagem1, 0, 0, 0);
    al_draw_bitmap(imagem2, 200, 0, 0);
    al_draw_bitmap(imagem3, 400, 0, 0);
    al_draw_bitmap(imagem4, 0, 200, 0);
    al_draw_bitmap(imagem5, 200, 200, 0);

    al_flip_display();
    al_rest(5.0);
    al_destroy_display(janela);

}

int main(){
    int op = 0, qtd = 5, inseriu = 0, testeBusca=0, testeRemove=0;
    categoria nome, procurado;
    noAB *raiz;
    FILE *arquivo;
    inicializa(&raiz);
    arquivo = fopen("nomes.txt", "r");
    printf("Bem vind@!!!\nDigite:\n1 - Inserir os elementos na arvore\n2 - Buscar um elemento \n3 - Impressao\n4 - Remocao de um elemento\n5 - Ver as opcoes novamente\n6 - Encerrar\n");
    while(op != 6){
        qtd = 5;
        testeBusca = 0;
        testeRemove = 1;
        scanf(" %d", &op);
        if(op == 1){
            if(inseriu == 0){
                printf("\nInserindo... :D \n");
                while(fscanf(arquivo, "%s", nome.nome) != EOF){
                    //printf("%s\n", nome.nome);
                    insereAB(&raiz, nome);
                }
                fclose(arquivo);
                printf("Insercao Concluida!\n");
            }
            else
                printf("Os elementos ja foram adicionados a arvore");
            inseriu = 1;
        }
        if(op == 2){
            if(inseriu == 1){
                printf("\nDigite o Rotulo a ser procurado\n");
                scanf("%s",procurado.nome);
                printf("Todos nos com o rotulo digitado ");
                buscaEmOrdem(raiz, procurado.nome, &testeBusca);
                printf("\n");
                if(testeBusca > 0)
                    imprimeImagem(procurado.nome);
                else
                    printf("Nao achou");
            }
            else
                printf("Primeiro, insira os elementos na arvore ...\n");
        }
        if(op == 3){
            if(inseriu == 1){
                printf("\nImprimindo em Ordem :D...");
                emOrdem(raiz);
            }
            else
                printf("Primeiro, insira os elementos na arvore ...\n");
        }
        if(op == 4){
            if(inseriu == 1){
                printf("Digite o rotulo a ser removido\n");
                scanf("%s", procurado.nome);
                buscaEmOrdem(raiz, procurado.nome, &testeBusca);
                if(testeBusca > 0){
                    printf("\nRemovendo... :c\n");
                    while(qtd > 0){
                        removeNome(&raiz, procurado.nome, &testeRemove);
                        qtd--;
                    }
                    printf("...Remocao concluida!\n");
                }
                else
                    printf("O elemento nao foi encontrado :o\n");
            }
            else
            printf("\nPrimeiro, insira os elementos na arvore ...\n");
        }
        if(op == 5)
            printf("\nDigite:\n1 - Inserir os elementos na arvore\n2 - Buscar um elemento \n3 - Impressao\n4 - Remocao de um elemento\n5 - Ver as opcoes novamente\n6 - Encerrar\n");
        if(op == 6)
            break;
        printf("\nO que deseja fazer agora? :) \n");
    }
    printf("\nEncerrando... At+ :D \n");
    imprimeNivel(raiz);
    return 0;
}
