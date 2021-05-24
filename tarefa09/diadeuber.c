#include<stdlib.h>
#include<stdio.h>
#include<string.h>
enum estado {LIVRE, OCUPADO};

typedef struct coordenada
{
    int x;
    int y;
}coordenada;

typedef struct uber //dados do motorista
{
    enum estado estado;
    int km_rodados;
    double rendimento_bruto;
    coordenada local;
    //redimento liquido = rendimento_bruto*0,75 - despesas

} uber;

typedef struct passageiro
{
    char nome[15];
    double nota;
    int em_transporte;
    coordenada inicio;
    coordenada fim;
}passageiro;

typedef struct passageiro *p_passageiro; //ponteiro para passageiros

typedef struct heap //heap de ponteiros para passageiros
{
    p_passageiro vetor;
    int tamanho;
    int n;
} heap;

typedef struct heap *p_heap; //ponteiro para heap

void trocar(p_passageiro pessoa1, p_passageiro pessoa2) // troca duas pessoas em um vetor
{
    passageiro auxiliar = *pessoa1;
    *pessoa1 = *pessoa2;
    *pessoa2 = auxiliar;
}

#define F_ESQ(i) (2*i+1) //define o indice do filho esquerdo
#define F_DIR(i) (2*i+2) // define o indice do filho direito 

void corrige_descendo(p_heap fila_ordenada, int indice) //corrige o heap enquanto desce ele
{
    int maior_filho;
    if(F_ESQ(indice) < fila_ordenada->n)
    {
        maior_filho = F_ESQ(indice);
        if(F_DIR(indice)< fila_ordenada->n && fila_ordenada->vetor[F_ESQ(indice)].nota< fila_ordenada->vetor[F_DIR(indice)].nota)
        {
            maior_filho = F_DIR(indice);
        }
        if(fila_ordenada->vetor[indice].nota < fila_ordenada->vetor[maior_filho].nota && fila_ordenada->vetor[indice].em_transporte <=  fila_ordenada->vetor[maior_filho].em_transporte)
        {
            trocar(&fila_ordenada->vetor[indice], &fila_ordenada->vetor[maior_filho]);
            corrige_descendo(fila_ordenada, maior_filho);
        }
    }
}

#define PAI(i) ((i-1)/2) //define o indice do pai

void corrige_subindo(p_heap clientes, int m) //corrige o heap enquanto sobe ele
{
    if (m >0 && clientes->vetor[PAI(m)].nota < clientes->vetor[m].nota && clientes->vetor[PAI(m)].em_transporte == clientes->vetor[m].em_transporte)
    {
        trocar(&clientes->vetor[PAI(m)],&clientes->vetor[m]);
        corrige_subindo(clientes, PAI(m));
    }
}

int distancia_manhatam(int x, int y, int xf, int yf) //calcula e retorna distancia manhatam entre 2 pontos
{
    int distancia;
    distancia = abs(x-xf) + abs(y-yf);
    return distancia;
}

double gasto_por_km(int distancia) //calcula e retorna gasto por km
{
    double preco_por_km = 0.4104;
    double custo;
    custo = distancia * preco_por_km;
    return custo;
}

double ganho_por_km(int distancia) //calcula e retorna ganho por km
{
    double preco_por_km = 1.40;
    double ganho;
    ganho = distancia * preco_por_km;
    return ganho;
}

void atender(uber *motorista, p_heap lista_prioridade) //atende passageiro deslocando motorista até a posição
{
    lista_prioridade->vetor[0].em_transporte +=1;
    motorista->km_rodados += distancia_manhatam(motorista->local.x, motorista->local.y, lista_prioridade->vetor[0].inicio.x, lista_prioridade->vetor[0].inicio.y);
    motorista->local = lista_prioridade->vetor[0].inicio;
    motorista->estado = OCUPADO;
}

void insere(p_heap fila_prioridade, p_passageiro pessoa) //insere passageiro no heap de maneira ordenada
{
    fila_prioridade->vetor[fila_prioridade->n] = *pessoa;
    fila_prioridade->n +=1;
    corrige_subindo(fila_prioridade, fila_prioridade->n-1);
    free(pessoa);
}

void remover_primeiro(p_heap lista_prioridades) //remove o primeiro do heap
{
    trocar(&lista_prioridades->vetor[0],&lista_prioridades->vetor[lista_prioridades->n-1]);
    lista_prioridades->n --;
    corrige_descendo(lista_prioridades, 0);
}

int encontrar_indice(char nome[15], p_heap lista_prioridade) // encotra e retorna indidce do passageiro desejado
{
    for(int i = 0 ; i< lista_prioridade->n; i++)
    {
        if(strcmp(nome, lista_prioridade->vetor[i].nome) == 0)
        {
            return i;
        }
    }
    return -1; // caso não encontre
}

void remover_passageiro(p_heap lista_prioridades, int i) //remove passageiro do reap
{
    trocar(&lista_prioridades->vetor[i],&lista_prioridades->vetor[lista_prioridades->n-1]);
    lista_prioridades->n --;
    corrige_descendo(lista_prioridades, i);
}

void imprimir_dados(uber *motorista) //imprime dados do motorista
{
    double despesas = 57 + (motorista->km_rodados * 0.4104);
    double rendimento_liquido = (motorista->rendimento_bruto*0.75) - despesas;
    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", motorista->km_rodados);
    printf("Rendimento bruto: %.2lf\n", motorista->rendimento_bruto);
    printf("Despesas: %.2lf\n", despesas);
    printf("Rendimento liquido: %.2lf\n", rendimento_liquido);
}

int main()
{
    int contador = 0; // contador que garante que quem já está no carro não será retirado
    uber *motorista = malloc(sizeof(uber)); //inicializa motorista
    motorista->rendimento_bruto = 0;
    motorista->estado = LIVRE;
    motorista->km_rodados = 0;
    motorista->local.x = 0;
    motorista->local.y = 0;
    char comando; //lê comando
    p_heap lista_prioridade = malloc(sizeof(heap));
    lista_prioridade->vetor = malloc(500 * sizeof(passageiro)); //vetor com pessoas
    lista_prioridade->tamanho = 500;
    lista_prioridade->n = 0; // numero de passageiros nos vetor
    while(1)
    {
        scanf("%c ", &comando);
        if(comando == 'A') //lê dados do cliente e adiciona ao heap
        {
            p_passageiro pessoa = malloc(sizeof(passageiro));
            scanf("%s ", pessoa->nome);
            scanf("%lf ", &pessoa->nota);
            scanf("%d %d ", &pessoa->inicio.x, &pessoa->inicio.y);
            scanf("%d %d ",&pessoa->fim.x, &pessoa->fim.y);
            pessoa->em_transporte = contador;
            printf("Cliente %s foi adicionado(a)\n",pessoa->nome);
            insere(lista_prioridade, pessoa); //adiciona ao heap
        }
        if(comando == 'F') //termina a viagem atual
        {
            printf("A corrida de %s foi finalizada\n", lista_prioridade->vetor->nome);
            motorista->km_rodados += distancia_manhatam(motorista->local.x, motorista->local.y, lista_prioridade->vetor[0].fim.x, lista_prioridade->vetor[0].fim.y);
            motorista->rendimento_bruto += ganho_por_km(distancia_manhatam(lista_prioridade->vetor[0].inicio.x, lista_prioridade->vetor[0].inicio.y, lista_prioridade->vetor[0].fim.x, lista_prioridade->vetor[0].fim.y));
            motorista->local = lista_prioridade->vetor[0].fim;
            remover_primeiro(lista_prioridade); //remove primeiro do heap
            motorista->estado = LIVRE; //deixa motorista livre
        }
        if(comando == 'C') // cancela e viagem do passageiro
        {
            int indice = 0;
            char nome[15];
            scanf("%s ",nome);
            indice = encontrar_indice(nome, lista_prioridade); // encontra posição do passageiro no heap
            remover_passageiro(lista_prioridade, indice);// remove passageiro do heap
            printf("%s cancelou a corrida\n", nome);
            motorista->rendimento_bruto += 7;
        }
        if(comando == 'T') // encerra o programa
        {
            break;
        }
        if(motorista->estado == LIVRE && lista_prioridade->n != 0) // garante que motorista não vai atender quando o heap estiver vazio
        {
            atender(motorista,lista_prioridade);
        }
    }
    imprimir_dados(motorista); // imprime informações da jornada do dia
    free(motorista);
    free(lista_prioridade->vetor);
    free(lista_prioridade);
    return 0;
}