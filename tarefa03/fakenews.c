#include <stdio.h>
#include <math.h>
#include<stdlib.h>

#define NUMERO_CARCTERES 26

typedef struct tipo
{
    int bot;
    int surpreendente;
    int normal;
    int local;
    int irrelevante;
} Tipo;

typedef struct dados
{
    char nome[NUMERO_CARCTERES];
    double max;
    double min;
    double media;
    double desvio;
    Tipo situacao;
}Dados;

double calcular_media(double *ponteiro, int numero_de_dados)
{
    double soma = 0.0, media;
    for(int i = 0; i< numero_de_dados; i++)
    {
        soma += *(ponteiro+ i);
    }
    media = (soma / (numero_de_dados*1.0));
    return media;
}

double calcular_desvio(double *ponteiro, int numero_de_dados, double media)
{
    double desvio, soma = 0;
    for(int i=0; i<numero_de_dados; i++)
    {
        soma += pow((*(ponteiro+i)-media),2.0)/(numero_de_dados *1.0);
    }
    desvio = sqrt(soma);
    return desvio;

}

double calcular_minimo(double *ponteiro, int numero_de_dados)
{
    double minimo;
    minimo = *ponteiro;
    for(int i =0; i<numero_de_dados; i++)
    {
        if(minimo >= *(ponteiro+i))
        {
            minimo = *(ponteiro + i);
        }
    }
    return minimo;
}
double calcular_maximo(double *ponteiro, int numero_de_dados)
{
    double maximo;
    maximo = *ponteiro;
    for(int i =0; i<numero_de_dados; i++)
    {
        if(maximo <= *(ponteiro+i))
        {
            maximo = *(ponteiro + i);
        }
    }
    return maximo;
}

void ler_dados(Dados *pessoa, int Numero_dias)
{
    double *popularidade;
    popularidade = malloc((Numero_dias * sizeof(double))); //free linha 89
    scanf("%s ", pessoa->nome);
    for(int i=0; i< Numero_dias; i++)
    {
        scanf(" %lf ", (popularidade+i));
    }
    pessoa->media = calcular_media(popularidade, Numero_dias);
    pessoa->desvio = calcular_desvio(popularidade, Numero_dias, pessoa->media);
    pessoa->min = calcular_minimo(popularidade, Numero_dias);
    pessoa->max = calcular_maximo(popularidade, Numero_dias);
    free(popularidade); //malloc linha 79
}

void checar_situacao(Dados *pessoa)
{
    if(pessoa->media>= 60 && pessoa->desvio >15)
    {
        pessoa->situacao.bot = 1;
        pessoa->situacao.irrelevante = 0;
        pessoa->situacao.local = 0;
        pessoa->situacao.normal = 0;
        pessoa->situacao.surpreendente = 0;
    }
    else if(pessoa->media>=60 && pessoa->desvio <= 15)
    {
        pessoa->situacao.surpreendente = 1;
        pessoa->situacao.bot = 0;
        pessoa->situacao.irrelevante = 0;
        pessoa->situacao.local = 0;
        pessoa->situacao.normal = 0;
    }
    else if(pessoa->media<60 && pessoa->min>20 && pessoa->max >=80)
    {
        pessoa->situacao.normal = 1;
        pessoa->situacao.bot = 0;
        pessoa->situacao.irrelevante = 0;
        pessoa->situacao.local = 0;
        pessoa->situacao.surpreendente = 0;
    }
    else if(pessoa->media<60 && pessoa->min<= 20 && pessoa->max>=80)
    {
        pessoa->situacao.local = 1;
        pessoa->situacao.bot = 0;
        pessoa->situacao.irrelevante = 0;
        pessoa->situacao.normal = 0;
        pessoa->situacao.surpreendente = 0;
    }
    else if(pessoa->media<60 && pessoa->max<80)
    {
        pessoa->situacao.irrelevante =1;
        pessoa->situacao.bot = 0;
        pessoa->situacao.local = 0;
        pessoa->situacao.normal = 0;
        pessoa->situacao.surpreendente = 0;
    }
}

int main()
{
    
    Dados *pesquisas;
    int N, M;
    scanf("%d %d ", &N, &M);
    pesquisas = malloc((N*sizeof(Dados)));
    for(int i= 0; i<N; i++)
    {
        ler_dados((pesquisas+i), M);
    }
    for(int p = 0; p<N; p++)
    {
        checar_situacao(pesquisas+p);
        printf("%s ",(pesquisas+p)->nome);
        printf("%.2lf %.2lf %.2lf %.2lf ", (pesquisas+p)->max, (pesquisas+p)->min, (pesquisas+p)->media, (pesquisas+p)->desvio);
        printf("\n");

    }
    printf("\n");
    printf("RESULTADO: \n");
    int bot =0, surpreeendente =0, normal= 0, local =0, irrelevante =0;
    for(int u = 0; u< N; u++)
    {
        checar_situacao(pesquisas+u);
        if((pesquisas+u)->situacao.bot ==1)
        {
           bot ++;
            
        }
        else if((pesquisas+u)->situacao.surpreendente ==1)
        {
            surpreeendente ++;
        }
        else if((pesquisas+u)->situacao.normal ==1)
        {
            normal ++;
        }
        else if((pesquisas+u)->situacao.local ==1)
        {
            local ++;
        }
        else if((pesquisas+u)->situacao.irrelevante ==1)
        {
            irrelevante ++;
        }
    }
    printf("Bot (%d): ", bot);
    for(int g =0; g<N; g++)
    {
        if((pesquisas+g)->situacao.bot == 1)
        {
            printf("%s ", (pesquisas+g)->nome);
        }
    }
    printf("\n");
    printf("Surpreendente (%d): ", surpreeendente);
    for(int p =0; p<N; p++)
    {
        if((pesquisas+p)->situacao.surpreendente == 1)
        {
            printf("%s ", (pesquisas+p)->nome);
        }
    }
    printf("\n");
    printf("Normal (%d): ", normal);
    for(int o =0; o<N; o++)
    {
        if((pesquisas+o)->situacao.normal == 1)
        {
            printf("%s ", (pesquisas+o)->nome);
        }
    }
    printf("\n");
    printf("Local (%d): ", local);
    for(int y =0; y<N; y++)
    {
        if((pesquisas+y)->situacao.local == 1)
        {
            printf("%s ", (pesquisas+y)->nome);
        }
    }
    printf("\n");
    printf("Irrelevante (%d): ", irrelevante);
    for(int h =0; h<N; h++)
    {
        if((pesquisas+h)->situacao.irrelevante == 1)
        {
            printf("%s ", (pesquisas+h)->nome);
        }
    }
    free(pesquisas);
}