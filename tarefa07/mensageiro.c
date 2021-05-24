#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct mensagem
{
    int id;
    char *strg;
} msg;

typedef struct No
{
    msg *cartao;
    struct No *esquerda;
    struct No *direita;

} No;

typedef struct triade
{
    int num1;
    int num2;
    int num3;
} tri;

typedef struct No *p_No;

void inordem(p_No raiz) //printa arvore em inordem
{
    if (raiz != NULL)
    {
        inordem(raiz->esquerda);
        printf("%s", raiz->cartao->strg);
        inordem(raiz->direita);
    }
}
p_No Maior_esquerda(p_No *no) //encontra maior numero da subarvore esquerda
{
    if ((*no)->direita != NULL)
    {
        return Maior_esquerda(&(*no)->direita);
    }
    else
    {
        p_No movel = (*no);
        if ((*no)->esquerda != NULL)
        {
            *no = (*no)->esquerda;
        }
        else
        {
            *no = NULL;
        }
        return movel;
    }
}
void remover_elemento(p_No *raiz, int k) //remove elemento da arvore
{
    if (*raiz == NULL)
    {
        return;
    }
    if (k < (*raiz)->cartao->id)
    {
        remover_elemento(&(*raiz)->esquerda, k);
    }
    else if (k > (*raiz)->cartao->id)
    {
        remover_elemento(&(*raiz)->direita, k);
    }
    else
    {
        p_No movel = *raiz;
        if (((*raiz)->esquerda == NULL) && ((*raiz)->direita == NULL))
        {
            free((*raiz)->cartao->strg);
            free((*raiz)->cartao);
            free(movel);
            (*raiz) = NULL;
        }
        else if ((*raiz)->esquerda == NULL) //só filho da direita
        {
            (*raiz) = (*raiz)->direita;
            movel->direita = NULL;
            free(movel->cartao->strg);
            free(movel->cartao);
            free(movel);
            movel = NULL;
        }
        else if ((*raiz)->direita == NULL) //só filho da esquerda
        {
            (*raiz) = (*raiz)->esquerda;
            movel->esquerda = NULL;
            free(movel->cartao->strg);
            free(movel->cartao);
            free(movel);
            movel = NULL;
        }
        else
        {
            movel = Maior_esquerda(&(*raiz)->esquerda); //ambos os filhos
            movel->esquerda = (*raiz)->esquerda;
            movel->direita = (*raiz)->direita;
            (*raiz)->esquerda = NULL;
            (*raiz)->direita = NULL;
            free((*raiz)->cartao->strg);
            free((*raiz)->cartao);
            free((*raiz));
            *raiz = movel;
            movel = NULL;
        }
    }
}
void limpar_arvore(p_No raiz) //da free na arvore
{
    if (raiz != NULL)
    {
        limpar_arvore(raiz->esquerda);
        limpar_arvore(raiz->direita);
        remover_elemento(&raiz, raiz->cartao->id);
    }
}
int buscar_int(p_No raiz, int busca) // procura int na arvore binaria
{
    while (raiz != NULL && busca != raiz->cartao->id)
    {
        if (busca < raiz->cartao->id)
            raiz = raiz->esquerda;
        else
            raiz = raiz->direita;
    }
    if (raiz == NULL)
    {
        return -1;
    }
    return raiz->cartao->id;
}
p_No buscar_cartao(p_No r, int k) //econtra cartão com id passado
{
    if (r == NULL || r->cartao->id == k)
    {
        return r;
    }
    if (r->cartao->id > k)
        return buscar_cartao(r->esquerda, k);
    else
        return buscar_cartao(r->direita, k);
}
void adicionar_arvore(No **t, msg *cartao) // cria nó e adiciona a arvore com o cartão
{
    if (*t == NULL)
    {
        *t = (No *)malloc(sizeof(No));
        (*t)->direita = NULL;
        (*t)->esquerda = NULL;
        (*t)->cartao = cartao;
    }
    else
    {
        if (cartao->id < (*t)->cartao->id)
        {
            adicionar_arvore(&(*t)->esquerda, cartao);
        }
        if (cartao->id > (*t)->cartao->id)
        {
            adicionar_arvore(&(*t)->direita, cartao);
        }
    }
}
p_No achar_maior(p_No raiz) //encontra maior numero
{
    while (raiz->direita != NULL)
    {
        raiz = raiz->direita;
    }
    return raiz;
}
void achar_no(p_No raiz, int referencia, int *acumulador) //encontra o maior numero menor que a referencia passada
{
    if (raiz != NULL)
    {
        achar_no(raiz->direita, referencia, acumulador);
        if (raiz->cartao->id < referencia && raiz->cartao->id > *acumulador)
        {
            (*acumulador) = raiz->cartao->id;
        }
        achar_no(raiz->esquerda, referencia, acumulador);
    }
}
p_No achar_menor(p_No raiz) //encontra menor
{
    while (raiz->esquerda != NULL)
    {
        raiz = raiz->esquerda;
    }
    return raiz;
}
tri encontrar(p_No raiz, int autoridade) // econtra os cartões pra troca
{
    int *acumulador = malloc(sizeof(int)); //acumulador de valor para comparação
    int *acumulador2 = malloc(sizeof(int));
    int int_encontrado, primeira_vez = 1, primeira_vez2 = 1; //controle pra encontrar o maior e segundo maior
    tri res;
    while (1) //encontra e varia o primeiro maior
    {
        (*acumulador) = 0;
        int ref;
        primeira_vez2 = 1;
        if (primeira_vez == 1)
        {
            primeira_vez = 0;
            p_No maior = achar_maior(raiz);
            ref = maior->cartao->id;
            (*acumulador) = maior->cartao->id;
        }
        else
        {
            achar_no(raiz, ref, acumulador);
            ref = *acumulador;
        }
        if(ref >= autoridade) //salvou o tempo do codigo :)
            continue;
        p_No menor = achar_menor(raiz);
        while (1) //encontra e varia o segundo maior
        {
            int ref2 = primeira_vez2 == 1 ? *acumulador : *acumulador2;
            (*acumulador2) = 0;
            achar_no(raiz, ref2, acumulador2);
            primeira_vez2 = 0;
            int objetivo = autoridade - (*acumulador + *acumulador2);
            if (objetivo > 0)
                int_encontrado = buscar_int(raiz, objetivo);
            else
                int_encontrado = -1;
            if (int_encontrado > 0 || *acumulador2 == menor->cartao->id)
                break;
        }
        if (int_encontrado < 0)
            continue;
        res.num1 = int_encontrado;
        res.num2 = *acumulador2;
        res.num3 = *acumulador;
        free(acumulador2);
        free(acumulador);
        return res;
    }
}
void concatenar(p_No raiz, tri triade, msg *novo_cartao) //concatena as strings em uma só
{
    int tamanho_maior, tamanho_meio, tamanho_menor, multiplicador, i, j, k;
    No *maior, *meio, *menor;
    novo_cartao->id = triade.num1 + triade.num2 + triade.num3;
    maior = buscar_cartao(raiz, triade.num3);
    meio = buscar_cartao(raiz, triade.num2);
    menor = buscar_cartao(raiz, triade.num1);
    tamanho_maior = strlen(maior->cartao->strg);
    tamanho_meio = strlen(meio->cartao->strg);
    tamanho_menor = strlen(menor->cartao->strg);
    multiplicador = tamanho_maior + tamanho_meio + tamanho_menor + 1;
    novo_cartao->strg = malloc(multiplicador * sizeof(char));
    for (i = 0; i < tamanho_menor; i++)
    {
        novo_cartao->strg[i] = menor->cartao->strg[i];
    }
    for (k = 0; k < tamanho_meio; k++)
    {
        novo_cartao->strg[i + k] = meio->cartao->strg[k];
    }
    for (j = 0; j < tamanho_maior; j++)
    {
        novo_cartao->strg[i + k + j] = maior->cartao->strg[j];
    }
    novo_cartao->strg[i + k + j] = '\0';
}
p_No fazer_troca(p_No raiz, int autoridade) // faz a troca de três cartões por um
{
    msg *novo_cartao = malloc(sizeof(msg));
    novo_cartao->id = autoridade; // pega id do novo cartão
    tri triade;
    triade = encontrar(raiz, autoridade); // encontra os cartões equivalentes
    concatenar(raiz, triade, novo_cartao); //concatena as strings
    remover_elemento(&raiz, triade.num1); //remove_elementos
    remover_elemento(&raiz, triade.num2);
    remover_elemento(&raiz, triade.num3);
    adicionar_arvore(&raiz, novo_cartao); //adiciona novo elemento a arvore
    return raiz;
}
int main()
{

    while (1)
    {
        p_No raiz = NULL;
        int numero_cartao, numero_autoridade;
        int saida = 0;
        saida = scanf("%d %d", &numero_cartao, &numero_autoridade); // lê numero de cartões e autoridades
        if (saida != 2) //verifica o eof
            break;
        for (int i = 0; i < numero_cartao; i++) //lê cartão e adiciona na arvore
        {
            msg *cartao = malloc(sizeof(msg));
            cartao->strg = malloc(5 * sizeof(char));
            scanf("%d \"%[^\"]\"", &cartao->id, cartao->strg);
            adicionar_arvore(&raiz, cartao); // adiciona cartão a arvore
        }
        for (int j = 0; j < numero_autoridade; j++) //lê cada autoridade
        {
            int autoridade;
            scanf("%d\n", &autoridade);
            raiz = fazer_troca(raiz, autoridade); // faz a troca do cartão com a autoridade
        }
        inordem(raiz); // printa a frase
        printf("\n");
        limpar_arvore(raiz); // limpa a arvore
    }
    return 0;
}
