#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100 //tamanho do heap
#define TAMANHO_PALAVRA 30 //numero de characters maximo da palavra

typedef struct No //struct do nó com a palavra
{
    char palavra[TAMANHO_PALAVRA];
    struct No *prox;
}No;

typedef struct No *p_no; //ponteiro para o nó

typedef struct hash
{
    p_no vetor[MAX]; //vetor de ponteiros para nó
}hash;

typedef struct hash *p_hash;

void apagar_lista(p_no lista) //libera a lista ligada
{
    if(lista != NULL)
    {
        apagar_lista(lista->prox);
        free(lista);
    }
}

void limpar_tabela(p_hash tabela) //libera tabela
{
    for(int i = 0 ;i<MAX; i++)
    {
        apagar_lista(tabela->vetor[i]);
    }
    free(tabela);
}

int verificar_troca(char referencia[TAMANHO_PALAVRA], char comparativo[TAMANHO_PALAVRA]) //verifica se ocorreu uma permutação ou mais
{
    int contador =0;
    for(int i = 0;referencia[i]!= '\0';i++)
    {
        if(contador>1)
        {
            return 2;
        }
        if(referencia[i] != comparativo[i])
            contador ++;
    }
    return contador;
}

int verificar_adicao(char referencia[TAMANHO_PALAVRA], char comparativo[TAMANHO_PALAVRA]) //verifica se ocorreu uma adição ou mais
{
    int contador =0, i;
    for(i =0;comparativo[i] != '\0'; i++)
    {
        if(referencia[i]!= comparativo[i])
        {
            contador ++;
            break;
        }
    }
    for(int j = i;comparativo[j]!= '\0'; j++)
    {
        if(referencia[j] != comparativo[j+1])
            contador ++;
        if(contador>1)
            return 2;
    }
    return contador;
}

int verificar_remocao(char referencia[TAMANHO_PALAVRA], char comparativo[TAMANHO_PALAVRA]) //verifica se ocorreu uma remocao ou mais
{
    int contador = 0, i;
    for(i =0; referencia[i] != '\0';i++)
    {
        if(referencia[i] != comparativo[i])
        {
            contador ++;
            break;
        }
    }
    for(int j = i+1; referencia[j] != '\0'; j++)
    {
        if(referencia[j] != comparativo[j-1])
            contador++;
        if(contador>1)
            return 2;   
    }
    return contador;
}

int contar_erros(char referencia[TAMANHO_PALAVRA], char comparativo[TAMANHO_PALAVRA]) //conta numero de erros podendo ser 1 ou 2
{
    int resultado = 0;
    int tamanho_p, tamanho_s;
    tamanho_p = strlen(referencia);
    tamanho_s = strlen(comparativo);
    if(tamanho_p == tamanho_s)
    {
        resultado = verificar_troca(referencia, comparativo); //troca
        if(resultado == 1)
            return 1;
    }
    if(tamanho_p == tamanho_s -1 ) //adicao
    {
        resultado = verificar_adicao(referencia, comparativo);
        if(resultado == 1)
            return 1;
    }
    else if(tamanho_p == tamanho_s +1) // remoção
    {
        resultado = verificar_remocao(referencia, comparativo);
        if(resultado == 1)
            return 1;
    }
    return 2;
}

int calcular_indice(char palavra[TAMANHO_PALAVRA]) //calcula indice do hash
{
    int i, n = 0;
    for( i = 0;i < strlen(palavra); i++)
    {
        n = (256*n + palavra[i]) % MAX;
    }
    return n;
}

void adicionar_tabela(int indice, char palavra[TAMANHO_PALAVRA], p_hash tabela) //adiciona a palavra a tabela hash
{
    if(tabela->vetor[indice] == NULL)
    {
        p_no novo = malloc(sizeof(No));
        tabela->vetor[indice] = novo;
        strcpy(tabela->vetor[indice]->palavra, palavra);
        tabela->vetor[indice]->prox = NULL;
    }
    else
    {
        p_no movel = tabela->vetor[indice];
        while (movel->prox != NULL)
        {
            movel = movel->prox;
        }
        p_no novo = malloc(sizeof(No));
        movel->prox = novo;
        strcpy(novo->palavra, palavra);
        novo->prox = NULL;
    }
}

int verificar_erros(char buscada[TAMANHO_PALAVRA], p_hash tabela) //verifica se a palavra esta correta ou errada
{
    int indice, resultado;
    indice = calcular_indice(buscada);
    p_no movel;
    //verifica se a palavra está correta
    movel = tabela->vetor[indice];
    if(movel != NULL)
    {
        resultado = strcmp(movel->palavra, buscada);
        while(resultado !=0 && movel->prox != NULL)
        {
            movel = movel->prox;
            resultado = strcmp(buscada,movel->palavra);
            if(resultado == 0)
                break;
        }
        if(resultado ==0)
        {
            return 0;
        }
    }
    //verifica se tem apenas 1 erro
    for(int j = 0;j< 100;j++)
    {
        movel = tabela->vetor[j];
        if(movel != NULL)
        {
            resultado = contar_erros(movel->palavra, buscada); //conta erros
            if(resultado == 1)
                return 1;
            while (resultado != 1 && movel->prox != NULL) //cas a tabela esteja degenerada
            {
                movel = movel->prox;
                resultado = contar_erros(movel->palavra, buscada);
                if(resultado ==1)
                    break;  
            }
            if(resultado == 1)
                return 1;
        }
    }
    return 2; //tem mais de 1 erro retorna vermelho
}

int main()
{
    int n, q;
    scanf("%d %d ",&n,&q); //lê numero de palavras pro dicionario e numero de palavras buscadas 
    p_hash tabela = malloc(sizeof(hash));
    for(int k = 0; k<100; k++) //coloca todos os ponteiros para NULL
    {
        tabela->vetor[k] = NULL;
    }
    for(int i = 0;i<n;i++) // lê e adiciona palavra na tabela hash
    {
        int indice;
        char palavra[TAMANHO_PALAVRA];
        scanf("%s ", palavra);
        indice = calcular_indice(palavra);
        adicionar_tabela(indice, palavra, tabela);
    }
    for(int j =0; j<q; j++) //faz a busca da palavra e imprime a cor associada a palavra
    {
        int num_erros = 0;
        char buscada[30];
        scanf("%s ", buscada);
        num_erros = verificar_erros(buscada, tabela);
        if(num_erros == 0)
        {
            printf("verde\n");
        }
        if(num_erros == 1)
        {
            printf("amarelo\n");
        }
        else if(num_erros == 2)
        {
            printf("vermelho\n");
        }
    }
    limpar_tabela(tabela); //libera memoria alocada na tabela
    return 0;
}