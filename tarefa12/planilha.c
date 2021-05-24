#include"planilha.h"

void limpar_lista(p_no lista) //apaga lista ligada de strings
{
    if(lista == NULL)
        return;
    p_no movel = lista, aux;
    while(movel !=NULL)
    {
        aux = movel;
        movel = movel->prox;
        free(aux->resultado);
        free(aux);
    }
}

void adicionar_lista(p_no *lista, char *resultado) //adiciona string a lista ligada de strings
{
    p_no novo = malloc(sizeof(No));
    novo->resultado =NULL;
    if(*lista == NULL)
    {
        novo->resultado = resultado;
        *lista = novo;
        (*lista)->prox = NULL;
        return;
    }
    p_no movel = NULL;
    novo->resultado = resultado;
    movel = *lista;
    while(movel->prox != NULL)
    {
        movel = movel->prox;
    }
    movel->prox = novo;
    novo->prox = NULL;
}

char *encontrar_ref(p_planilha matriz, char *celula, p_no *lista)
{
    //funcao recebe matriz de strings, a celula a ser buscada, e uma lista ligada
    //retorna o valor numero em string
    char descartavel[TAM_INDICE], valor_um[TAM_INDICE], valor_dois[TAM_INDICE];
    strcpy(descartavel,celula);
    int ref_simples=0, contador = 0, parametro=0, controlador =0;
    if(strlen(celula)<7) //verifica se a celula é uma operacao ou uma referencia simples
    {
        ref_simples = 1;
    }
    char *intermedio = strtok(descartavel, " "); //separa a celula usando os espacos
    while(intermedio)
    {
        intermedio = strtok(NULL, " ");
        if(ref_simples == 1)
        {
            break;
        }
        if(strlen(intermedio)>=2 && contador == 0)
        {
            strcpy(valor_um,intermedio); //pega primeira coordenada da operacao
            contador++;
            controlador = 1;
        }
        if(intermedio[0]=='-')
        {
            parametro = subtracao;
        }
        if(intermedio[0]== '+')
        {
            parametro = soma;
        }
        if(strlen(intermedio)>=2 && controlador == 1) //pega segunda coordenada da operacao
        {
            strcpy(valor_dois,intermedio);
            contador++;
        }
        if(intermedio[0]== ')')
        {
            break;
        }
    }
    if(ref_simples ==1)
    {
        char letra = intermedio[0]; //converte coordenada de planilha pra coordenada de matriz
        int coluna_b = letra-65;
        int linha = atoi((intermedio+1));
        linha--;
        //chamada recursiva caso a célula encontrada não seja um inteiro
        if(matriz->adj[linha][coluna_b][0]== '=')
            return(encontrar_ref(matriz,matriz->adj[linha][coluna_b],lista));
        else
        {
            return(matriz->adj[linha][coluna_b]);
        }
    }
    else
    {
        char *resposta = malloc(100*sizeof(char));
        int resultado = 0;
        char *num1, *num2, adaptador_um[TAM_INDICE] = {"= "}, adaptador_dois[TAM_INDICE] = {"= "};
        strcat(adaptador_um,valor_um);
        strcat(adaptador_dois,valor_dois);
        //busca valores na matriz recursivamente
        num1 = encontrar_ref(matriz, adaptador_um,lista);
        num2 = encontrar_ref(matriz, adaptador_dois,lista);
        if(parametro == soma)
        {
            resultado = atoi(num1) + atoi(num2);
        }
        else
        {
            resultado = atoi(num1) - atoi(num2);
        }
        sprintf(resposta," %d",resultado);
        adicionar_lista(lista, resposta); //adiciona a lista ligada para poder dar free depois
        return(resposta);
    }
}

void imprimir(p_planilha matriz, p_no *lista) //recebe a matriz e uma lista
{
    //lê coordenadas e converte para coordenada de matriz
    char letra, *novo;
    int linha;
    scanf("%c%d ",&letra,&linha);
    linha--;
    int coluna_b = letra-65;
    if(matriz->adj[linha][coluna_b][0]== '=') //chama a busca recursiva e printa resultado
    {
        novo = encontrar_ref(matriz,matriz->adj[linha][coluna_b],lista);
        printf("%c%d:%s\n",letra,linha+1,novo);
    }
    else
        printf("%c%d:%s\n",letra,linha+1,matriz->adj[linha][coluna_b]);
}

void atualizar(p_planilha matriz) //atualiza valor na planilha
{
    char letra, novo_valor[TAM_INDICE], movel[TAM_INDICE] = {" "};
    int linha, new;
    scanf("%c%d ",&letra,&linha);
    scanf("%d",&new);
    sprintf(novo_valor,"%d ",new);
    linha--;
    int coluna_b = letra-65;
    printf("%c%d:%s-> ",letra,linha+1,matriz->adj[linha][coluna_b]);
    printf("%s\n",novo_valor);
    strcat(movel,novo_valor);
    strcpy(matriz->adj[linha][coluna_b],movel); //atualiza valor na matriz
}

void preencher(p_planilha matriz, char *string, int i) //preenche a matriz uma linha por vez
{
    char *celula;
    celula = strtok(string,",");
    for(int j =0; j< matriz->colunas;j++)
    {
        strcpy(matriz->adj[i][j],celula);
        celula = strtok(NULL, ",|\n");
    }
}

int main()
{
    p_no lista = NULL;
    char acao;
    char file[TAM_NOME], valor[TAM_LINHA];
    int colunas, linhas, t, i=0;
    planilha matriz;
    scanf("%s ",file);
    scanf("%d %d ",&colunas,&linhas); //le numero de linhas e colunas
    matriz.colunas = colunas;
    matriz.linhas = linhas;
    FILE *arquivo = fopen(file, "r");
    for(i =0;i<matriz.linhas;i++) //Le linha por linha da matriz
    {
        fgets(valor,TAM_LINHA,arquivo);
        preencher(&matriz,valor,i);
    }
    while(1) //lê os comandos da entrada
    {
        t = scanf("%c ",&acao);
        if(t == EOF)
            break;
        if(acao == 'G')
        {
            imprimir(&matriz, &lista);
        }
        else if( acao == 'S')
        {
            atualizar(&matriz);
        }
    }
    limpar_lista(lista); //libera a memoria alocada
    fclose(arquivo);
    return 0;
}