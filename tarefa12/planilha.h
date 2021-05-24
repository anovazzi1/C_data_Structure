#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM_INDICE 30 //tamanho maximo de caracteres dentro de uma célula
#define TAM_NOME 30 //tamanho max do nome do arquivo
#define TAM_MATRIZ 50 //tamanho maximo de linhas e colunas (matriz 50*50)
#define TAM_LINHA 500 //tamanho maximo de 1 linha da matriz

enum ref {soma,subtracao};

typedef struct No //lista ligada simples
{
    char *resultado;
    struct No *prox;
}No;

typedef struct No *p_no;

typedef struct planilha //estrutura da planilha
{
    char adj[TAM_MATRIZ][TAM_MATRIZ][TAM_INDICE];
    int colunas;
    int linhas;
}planilha;

typedef struct planilha *p_planilha;
