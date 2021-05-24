#include<stdio.h>
#define LINHAS 100 //numero maximo de linhas da matriz
#define COLUNAS 100 //numero maximo de colunas da matriz
#define PALAVRAS 10 // numero maximo de palavras
#define CARACTERES 21 //numero maximo de letras de cada palavra

void copiar_matriz(char matriz_orinal[LINHAS][COLUNAS], char matriz_copia[LINHAS][COLUNAS], int n, int m)
//recebe 2 matrizes e faz a segunda ser uma cópia da primeira
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            matriz_copia[i][j] = matriz_orinal[i][j];
        }
    }
}

void montar_matriz(char matriz[LINHAS][COLUNAS],int n, int m)
//lê e armazena em uma matriz o puzzle
{
    char letra;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf(" %c", &letra);
            matriz[i][j] = letra;
        }
    }
}

void ler_palavras(char palavra[PALAVRAS][CARACTERES], int total)
//lê e armazena as palavras que serão buscadas em uma vetor de strings
{
    for(int i =0 ;i<total ;i++)
    {
        scanf("%s ", palavra[i]);
    }
}
int checagem_recursiva(char *palavra, int q, char matriz[LINHAS][COLUNAS], int i, int j,int n, int m)
//recebe uma posição e verfica recursivamente se o caracter da palavra está nessa posição e se o proximo está em algum vizinho
{
    char aux;
    int resultado =0;
    aux = matriz[i][j];
    if(*(palavra+q) == '\0')
    {
        return 1;
    }    
    if(j<(m-1) && aux == *(palavra+q))
    {
        matriz[i][j] = '\a';
        resultado = checagem_recursiva(palavra, q+1, matriz, i, j+1,n,m);
        if(resultado == 1)
        {
            return 1;
        }
    }
    if(i<(n-1) && aux == *(palavra+q))
    {
        matriz[i][j] = '\a';
        resultado = checagem_recursiva(palavra, q+1, matriz, i+1, j,n,m);
        if(resultado == 1)
        {
            return 1;
        }
    }
    if(i!=0 && aux == *(palavra+q))
    {
        matriz[i][j] = '\a';
        resultado = checagem_recursiva(palavra, q+1, matriz, i-1, j,n,m);
        if(resultado == 1)
        {
            return 1;
        }
    }
    if(j!=0 && aux == *(palavra+q))
    {
        matriz[i][j] = '\a';
       resultado = checagem_recursiva(palavra, q+1, matriz, i, j-1,n,m);
       if (resultado == 1)
       {
           return 1;
       }   
    }
    return 0;        
}
void buscar(char matriz[LINHAS][COLUNAS], char palavras[PALAVRAS][CARACTERES], int n, int m, int q)
// busca as palavras na matriz e chama a função recursiva para cada palavra
{
    for(int l = 0;l<q ; l++) //cada palavra
    {
        int caracter =0;
        int resultado =0;
        char matriz_copia[LINHAS][COLUNAS];
        for(int i =0; i<n ; i++) //cada linha
        {
            for(int j =0; j<m; j++) //cada coluna
            {
                
                if(matriz[i][j] == palavras[l][0]){
                    copiar_matriz(matriz,matriz_copia, n, m);
                    resultado = checagem_recursiva(&palavras[l][0],caracter,matriz_copia,i,j,n,m);  
                    if (resultado == 1)
                    {
                        printf("sim\n");
                        break;
                    }
            }
            }
            if(resultado == 1)
            {
                break;
            }
        }
        if(resultado == 0)
        {
            printf("nao\n");
            continue;
        }
    }
}

int main()
{
    int n,m,q;
    char enigma[LINHAS][COLUNAS];
    char palavras[PALAVRAS][CARACTERES];
    scanf("%d ", &n); //linhas
    scanf("%d ", &m); //colunas
    scanf("%d ", &q); //numero de palavras
    montar_matriz(enigma, n, m);
    ler_palavras(palavras, q);
    buscar(enigma, palavras, n,m,q);
    return 0;
}