#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define TAM_MATRIZ 1000 //tamanho maximo da matriz de grafos
#define TAM_PALAVRA 10

enum local {vazio,pokestop,raid};

typedef struct grafo
{
    double adj[TAM_MATRIZ][TAM_MATRIZ];
    int n;
}grafo;

typedef struct grafo *p_grafo;

typedef struct coordenada
{
    double x;
    double y;
    int descricao;
}cord;

int classificar(char tipo[TAM_PALAVRA]) //classifica se é pokestpo ou raid
{
    if(strlen(tipo) == 8)
    {
        return pokestop;
    }
    else
    {
        return raid;
    }    
}

double calcular_distancia(cord primeiro, cord segundo) //calcula a distancia entre 2 pontos
{
    double x = primeiro.x-segundo.x, y = primeiro.y-segundo.y;
    return sqrt(x*x+y*y);
}

int busca(p_grafo matriz, int *acessados, int v,int dist_max, double restricao, int *raids) //faz uma busca em profundidade
{
    // considerando uma restricao de tamanho
    if(raids[v] ==1)
    {
        return dist_max;
    }
    acessados[v] = 1;
    for(int k =0;k<matriz->n;k++)
    {
        if(acessados[k]!=1)
        {
            if(matriz->adj[v][k]>= restricao)
            {
                continue;
            }
            if(dist_max < matriz->adj[v][k])
                dist_max = matriz->adj[k][v];

            dist_max = busca(matriz, acessados, k,dist_max,restricao,raids);
            
            if(dist_max != -1)
                return ceil(dist_max);
        }
    }
    return -1;
}
int fazer_percurso(p_grafo matriz,int *raids) // testa caminhos com uma limitação de distancia
{
    int dist_max =0;
    double maior = INFINITY;
    int *acessados = malloc(matriz->n*sizeof(int)); //vetor pra guardar quais indices foram acessados
    for(int i =0;i<matriz->n;i++)
        acessados[i] = -1;
    double menor_max_dist = busca(matriz,acessados,0,0,maior, raids);
    while(dist_max != -1)
    {
        for(int i =0;i<matriz->n;i++)
            acessados[i] = -1;
        dist_max = busca(matriz, acessados,0, 0,menor_max_dist, raids);
        if(dist_max !=-1)
        {
            menor_max_dist = dist_max;
        }
    }
    free(acessados);
    return ceil(menor_max_dist+1);
}

int main()
{
    grafo matriz; //cria grafo
    char palavra[TAM_PALAVRA];
    int t, contador=1;
    cord inicio;
    cord enderecos[TAM_MATRIZ];
    t = scanf("%lf %lf ", &inicio.x, &inicio.y); //le inicio
    inicio.descricao = -1;
    enderecos[0] = inicio;
    while(t == 2) //le ate eof
    {
        cord entrada;
        t = scanf("%lf %lf ", &entrada.x, &entrada.y);
        if(t !=2)
            break;
        scanf("%s ", palavra);
        entrada.descricao = classificar(palavra); //associo raid e pokestop a ints
        enderecos[contador] = entrada;
        contador++;
    }
    int *raids = calloc(contador,sizeof(int)); //guardo quais os indices das raids
    for(int i = 0;i<contador;i++)
    {
        for(int j=0;j<contador;j++)
        {
            matriz.adj[i][j] = calcular_distancia(enderecos[i], enderecos[j]);
            if(enderecos[j].descricao == raid)
            {
                raids[j] = 1;
            }
        }
    }
    matriz.n = contador;
    int resultado = fazer_percurso(&matriz, raids);
    printf("%d\n",resultado);
    free(raids);
    return 0;
}