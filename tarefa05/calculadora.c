#include<stdlib.h>
#include<stdio.h>
#define ALGARISMO 26

typedef struct No //nó de lista  dupla ligada
{
    int valor; //valor do nó
    struct No *prox; //ponteiro proximo nó
    struct No *anterior; //acabei não usando a lista dupla, só lista simples mas deixei implementado para poder reutilizar o código
} No;

typedef struct No *p_no; //ponteiro pra nó

int contar_digitos(p_no numero) //conta quantos digitos tem o numero armazenado na lista ligada
{
    p_no movel;
    movel = numero;
    int digitos = 0;
    while(movel != NULL)
    {
        digitos++;
        movel = movel->prox;
    }
    return digitos;
}

void apagar_lista(p_no lista) //libera a lista ligada
{
    if(lista != NULL)
    {
        apagar_lista(lista->prox);
        free(lista);
    }
    
}

p_no inserir_lista(p_no inicio_lista, int x) //adcionar elemento no inicio da lista ligada
{
    p_no Novo_elemento = malloc(sizeof(No));
    Novo_elemento->valor = x;
    Novo_elemento->prox = inicio_lista;
    Novo_elemento->anterior = NULL;
    if(inicio_lista != NULL)
    {
        inicio_lista->anterior = Novo_elemento;
    }
    return Novo_elemento;
}

void imprimir_lista(p_no lista) //imprimi lista ligada
{
    p_no ponteiro_movel = lista;
    int lixo=0;
    while (lixo == 0 && ponteiro_movel != NULL) //elimina os zeros a esquerda
    {
        if(ponteiro_movel->valor == 0)
        {
            ponteiro_movel = ponteiro_movel->prox;
        }
        else
        {
            lixo = 1;
        }    
    }
    while(ponteiro_movel!= NULL && lixo == 1)
    {
        printf("%d",ponteiro_movel->valor);
        ponteiro_movel = ponteiro_movel->prox;
    }
    if(lixo == 0) // se numero igual a 0, imprimi somente um 0
    {
        printf("0");
    }
    printf("\n");
}

p_no criar_lista(char numero[ALGARISMO],p_no inicio) //cria lista ligada
{
    p_no Novo_no;
    Novo_no = inicio;
    for(int j = 0; numero[j]!= '\0'; j++)
    {
        Novo_no = inserir_lista(Novo_no,(int)numero[j]-'0');
    }
    return Novo_no;
}

p_no converter(char numero[ALGARISMO]) //converte string para lista ligada
{
    p_no inicio = NULL;
    inicio = criar_lista(numero, inicio);
    return inicio;    
}

p_no inverter(p_no lista) //inverte a ordem da lista ligada
{
    p_no lista_invertida =NULL, movel;
    movel = lista;
    while (movel != NULL)
    {
        lista_invertida = inserir_lista(lista_invertida, movel->valor);
        movel = movel->prox;
    }
    apagar_lista(lista);
    return lista_invertida;
}

p_no comparar(p_no num1, p_no num2, int parametro) //comapara duas listas ligadas e devolve a que tem o maior numero
{
    p_no movel, movel_2, ultimo1, ultimo2;
    movel = num1;
    movel_2 = num2;
    p_no nova_lista= NULL, nova_lista2 = NULL;
    while(movel!= NULL && movel_2 != NULL)
    {
        nova_lista = inserir_lista(nova_lista,movel->valor);
        movel = movel->prox;
        nova_lista2 = inserir_lista(nova_lista2, movel_2->valor);
        movel_2 = movel_2->prox;
    }
    ultimo1 = nova_lista;
    ultimo2 = nova_lista2;
    if(parametro == 0)
    {
        while(ultimo1 != NULL)
        {   
            if(ultimo1->valor>ultimo2->valor)
            {
                apagar_lista(nova_lista);
                apagar_lista(nova_lista2);
                return num1;
            }
            else if(ultimo2->valor > ultimo1->valor)
            {
                apagar_lista(nova_lista);
                apagar_lista(nova_lista2);
                return num2;
            }
            ultimo1 = ultimo1->prox;
            ultimo2 = ultimo2->prox;
        }
    }

    if(parametro == 1)
    {
        while(ultimo1 != NULL)
        {   
            if(ultimo1->valor>ultimo2->valor)
            {
                apagar_lista(nova_lista);
                apagar_lista(nova_lista2);
                return num2;
            }
            else if(ultimo2->valor > ultimo1->valor)
            {
                apagar_lista(nova_lista);
                apagar_lista(nova_lista2);
                return num1;
            }
            ultimo1 = ultimo1->prox;
            ultimo2 = ultimo2->prox;
        }
    }
    apagar_lista(nova_lista);
    apagar_lista(nova_lista2);
    return num1;
}

p_no multiplicar_int(p_no lista, int x, int multiplicador) //multlipica lista ligada por um int
{
    int aux = 0, acumulador = 0, contador = 0;
    p_no nova_lista = NULL, movel;
    movel = lista;
    while(movel!= NULL)
    {
        acumulador = (x*movel->valor) + aux;
        aux = 0;
        if(acumulador>9)
        {
            aux = acumulador/10;
            acumulador = acumulador%10;
        }
        nova_lista = inserir_lista(nova_lista,acumulador);
        movel = movel->prox;
        contador ++;
    }
    if(aux !=0)
    {
        nova_lista = inserir_lista(nova_lista, aux);
    }
    nova_lista = inverter(nova_lista);
    while(multiplicador != 0)
    {
        nova_lista = inserir_lista(nova_lista,0);
        multiplicador -= 1;
    }
    return nova_lista;
}

p_no soma(p_no numero, p_no numero_2) //recebe duas listas ligadas e soma
{
    int digito1, digito2, aux =0; //aux é valor que é incrementado no proximo numero da soma
    p_no maior_p, menor_p;
    if(numero_2 == NULL)
    {
        return inverter(numero); //caso base pra realizar a multiplicação
    }
    digito1 = contar_digitos(numero);
    digito2 = contar_digitos(numero_2);
    if(digito1<digito2) //encontra qual o numero com mais algarismos
    {
        menor_p = numero;
        maior_p = numero_2;
    }
    else if(digito1 > digito2)
    {
        menor_p = numero_2;
        maior_p = numero;
    }
    else
    {
        menor_p = numero;
        maior_p = numero_2;
    }
    p_no resultado = NULL;
    while(maior_p != NULL) //soma prorpiamente dita
    {
        int soma = maior_p->valor+aux;
        maior_p = maior_p->prox;
        aux = 0;
        if(menor_p != NULL)
        {
            soma += menor_p->valor;
            if(soma > 9) //icrementa valor no proximo numero
            {
                aux = soma/10;
                soma = soma%10;
            }
            menor_p = menor_p->prox;
        }
        resultado = inserir_lista(resultado, soma);
    }
    if(aux!=0)
    {
        resultado = inserir_lista(resultado, aux);
    }
    apagar_lista(numero);
    apagar_lista(numero_2);
    return resultado;
}

void subtrair(char numero[ALGARISMO], char numero_2[ALGARISMO]) //recebe duas strings, transforma em lista ligada e subtrai, devolvendo o modulo da subtração
{
    int digito1, digito2;
    p_no num1, num2, maior_p, menor_p;
    num1 = converter(numero);
    num2 = converter(numero_2);
    digito1 = contar_digitos(num1);
    digito2 = contar_digitos(num2);
    if(digito1<digito2) //define qual o maior e o menor numero
    {
        menor_p = num1;
        maior_p = num2;
    }
    else if(digito1 > digito2)
    {
        menor_p = num2;
        maior_p = num1;
    }
    else
    {
        maior_p = comparar(num1,num2,0);
        menor_p = comparar(num1,num2,1);
    }
    p_no resultado = NULL;
    while(maior_p != NULL) //subtração propriamente dita
    {
        int subtracao = maior_p->valor;
        if(menor_p != NULL)
        {
            subtracao -= menor_p->valor;
            menor_p = menor_p->prox;
            if(subtracao < 0)
            {
                subtracao += 10;
                maior_p->prox->valor -=1;
            }
        }
        maior_p = maior_p->prox;
        resultado = inserir_lista(resultado, subtracao);
    }
    imprimir_lista(resultado);
    apagar_lista(num1);
    apagar_lista(num2);
    apagar_lista(resultado);
}

void multiplicar(char numero[ALGARISMO], char numero_2[ALGARISMO]) // recebe duas strings, transforma em lista ligada, e faz a multiplicação;
{
    p_no num, num_2, menor_p, maior_p, acumulador =NULL;
    int digito1, digito2, multiplicador = 0; //multiplicador controla a ordem do numero que será multiplicado
    num = converter(numero);
    num_2 = converter(numero_2);
    digito1 = contar_digitos(num);
    digito2 = contar_digitos(num_2);
    if(digito1<digito2) //encontra numero com mais digitos
    {
        menor_p = num;
        maior_p = num_2;
    }
    else if(digito1 > digito2)
    {
        menor_p = num_2;
        maior_p = num;
    }
    else
    {
        menor_p = num;
        maior_p = num_2;
    }
    while(menor_p != NULL) //multiplicação propriamente dita
    {
        p_no auxiliar, auxiliar1;
        auxiliar = multiplicar_int(maior_p, menor_p->valor, multiplicador); //subvalor obtido da multiplicação de 1 digito
        auxiliar1 = inverter(acumulador);
        acumulador = soma(auxiliar,auxiliar1); //soma final de cada multiplicação
        menor_p = menor_p->prox;
        multiplicador += 1; //incremente o multiplicador aumento a ordem do próximo numero que será multiplicado
    }
    imprimir_lista(acumulador);
    apagar_lista(acumulador);
    apagar_lista(num);
    apagar_lista(num_2);
}

int main()
{
    p_no resultado, num1, num2;
    int numero_de_operacoes;
    char operador;
    char numero[ALGARISMO], numero_2[ALGARISMO];
    
    scanf("%d ", &numero_de_operacoes);
    for(int i = 0; i<numero_de_operacoes; i++)
    {
        scanf(" %c", &operador);
        scanf("%s", numero);
        scanf("%s", numero_2);

        if(operador == '+') //caso da soma
        {
            num1 = converter(numero);
            num2 = converter(numero_2);
            resultado = soma(num1, num2);
            imprimir_lista(resultado);
            apagar_lista(resultado);
        }
        if(operador == '-') //caso da subtração
        {
            subtrair(numero, numero_2);
        }
        if(operador =='*') //caso da multiplicação
        {
            multiplicar(numero, numero_2);
        }
    }
    return 0;
}