#include<stdio.h>
#include<stdlib.h>

enum Cor {VERMELHO, PRETO};

typedef struct No {
    int valor;
    int repeticao;
    enum Cor cor;
    struct No *esquerda;
    struct No *direita;
} No;

typedef No *p_no;

int ehVermelho(p_no x) //verifica se o no é vermelho
{
    if(x == NULL)
        return 0;
    return x->cor == VERMELHO;
}

int ehPreto(p_no x) //verifica se o nó é preto
{
    if(x == NULL)
        return 1;
    return x->cor == PRETO;
}

p_no rotacao_esquerda(p_no raiz) //rotaciona os nó para esquerda
{
    p_no movel = raiz->direita;
    raiz->direita = movel->esquerda;
    movel->esquerda = raiz;
    movel->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return movel;
}

p_no rotacao_direita(p_no raiz) //rotaciona os nó para direita
{
    p_no movel = raiz->esquerda;
    raiz->esquerda = movel->direita;
    movel->direita = raiz;
    movel->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return movel;
}

void subir_vermelho(p_no raiz) //sobe o nó vermelho
{
    raiz->cor = VERMELHO;
    raiz->esquerda->cor = PRETO;
    raiz->direita->cor = PRETO;
}

void corrigir(p_no *raiz) //recebe ponteiro pra raiz e faz verificação das propriedades rubro negro esquerdista
{
    if(ehVermelho((*raiz)->direita) && ehPreto((*raiz)->esquerda))
        (*raiz) = rotacao_esquerda(*raiz);
    if(ehVermelho((*raiz)->esquerda)&& ehVermelho((*raiz)->esquerda->esquerda))
        (*raiz) = rotacao_direita(*raiz);
    if(ehVermelho((*raiz)->esquerda)&& ehVermelho((*raiz)->direita))
        subir_vermelho(*raiz);
}

p_no inserir(p_no raiz, int valor) // inseri elemento na arvore seguindo as propriedades
{
    if(raiz == NULL)
    {
        p_no novo = malloc(sizeof(No));
        novo->esquerda = novo->direita = NULL;
        novo->valor = valor;
        novo->repeticao = 1;
        novo->cor = VERMELHO;
        return novo;
    }
    if(valor< raiz->valor)
    {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    }
    else if(valor == raiz->valor)
    {
        raiz->repeticao += 1;
    }
    else
    {
        raiz->direita = inserir(raiz->direita, valor);
    }
    corrigir(&raiz); //corrige a arvore binaria
    return raiz;
}

p_no adicionar(p_no raiz, int valor) //adiciona elemento a lista
{
    raiz = inserir(raiz, valor);
    raiz->cor = PRETO;
    return raiz;
}

int ler_repeticao(p_no raiz, int procurado) //encontra elemento na lista e devolve o numero da repeticao
{
    if(raiz == NULL)
    {
        return 0;
    }
    if (raiz->valor == procurado)
    {
        return raiz->repeticao;
    }
    if (raiz->valor > procurado)
        return ler_repeticao(raiz->esquerda, procurado);
    else
        return ler_repeticao(raiz->direita, procurado);
}

void contar_quanto_falta(p_no raiz, int *faltante) //conta quantos elementos falta para lista legal
{
    if(raiz != NULL)
    {
        contar_quanto_falta(raiz->esquerda, faltante);
        if(raiz->repeticao > raiz->valor)
        {
            *faltante += (raiz->repeticao - raiz->valor);
        }
        else if(raiz->repeticao < raiz->valor)
        {
            *faltante += raiz->repeticao;
        }
        contar_quanto_falta(raiz->direita,faltante);
    }
}

p_no Maior_esquerda(p_no *no) //encontra maior numero da subarvore esquerda
{
    if ((*no)->direita != NULL)
    {
        return Maior_esquerda(&(*no)->direita);
    }
    else
    {
        p_no movel = (*no);
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

void limpar_arvore(p_no raiz) //da free na arvore
{
    if (raiz != NULL)
    {
        limpar_arvore(raiz->esquerda);
        limpar_arvore(raiz->direita);
        free(raiz);
    }
}

int main()
{
    p_no raiz = NULL;
    int tamanho_lista, numero_operacoes;
    scanf("%d %d ", &tamanho_lista, &numero_operacoes);
    for(int i = 0; i< tamanho_lista; i++) //cria arvore balanceada com os numeros da lista legal
    {
        int chave;
        scanf("%d ", &chave);
        raiz = adicionar(raiz, chave); //adiciona a arvore
    }
    for(int j = 0; j< numero_operacoes; j++) //lê cada comando
    {
        short int comando;
        scanf("%hd ", &comando);
        if(comando == 1) //segue comando numero 1
        {
            int novo_elemento;
            scanf("%d ", &novo_elemento);
            raiz = adicionar(raiz,novo_elemento); //adiciona a arvore
        }
        if(comando == 2) //segue comando 2
        {
            int elemento_procurado;
            int repeticoes;
            scanf("%d ",&elemento_procurado);
            repeticoes = ler_repeticao(raiz, elemento_procurado); //acumula repetições
            printf("%d\n",repeticoes);
        }
        if(comando == 3) //segue comando 2
        {
            int *faltante = malloc(sizeof(int)); //acumulador de valores faltantes
            *faltante = 0;
            contar_quanto_falta(raiz, faltante); //conta quanto falta pra lista ficar legal
            printf("%d\n", *faltante);
            free(faltante);
        }
    }
    limpar_arvore(raiz); //apaga a arvore
    return 0;
}