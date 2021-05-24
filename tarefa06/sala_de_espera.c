#include<stdio.h>
#include<stdlib.h>
#include "sala_de_espera.h"
#define NORMAL 1
#define PREFERENCIAL 0

void apagar_lista(p_no lista) //libera a lista ligada
{
    if(lista != NULL)
    {
        apagar_lista(lista->prox);
        free(lista);
    }
}

void saida(char pessoa[50], int relogio) //imprime horario de saida do paciente
{
    int hora, minuto;
    hora = relogio/60;
    minuto = relogio %60;
    printf("%02d:%02d %s\n", hora,minuto, pessoa);
}

void preencher_vetor(MED *vetor) //preenche vetor de medicos com os medicos e suas caracteristicas basicas
{
    int capacidade[9] = {10,2,5,3,4,7,2,1,4};
    for(int i =0; i<9; i++)
    {
        p_deck deki =malloc(sizeof(deck));
        deki->cabeca = NULL;
        deki->fim = NULL;
        MED medico;
        medico.fila = NULL;
        medico.indentificador = i+1;
        medico.maximo = capacidade[i];
        medico.deck_medico = deki;
        vetor[i] = medico;
    }
}

p_no_paciente remover(p_no_paciente pop, p_no_paciente cabeca,deck *fila) //remove o paciente da fila sem quebra-la e da free nos ponteiros alocados
{
    if(pop->prox ==NULL && pop->anterior == NULL) //unico
    {
        free(pop->pessoa);
        free(pop);
        fila->cabeca = NULL;
        fila->fim = NULL;
        return NULL;
    }

    if(pop->prox == NULL) //ultimo
    {
        fila->fim = fila->fim->anterior;
        pop->anterior->prox = NULL;
        free(pop->pessoa);
        free(pop);
        return cabeca;
    }
    if(pop->anterior == NULL) //primeiro
    {
        p_no_paciente head = pop->prox;
        head->anterior = NULL;
        fila->cabeca = fila->cabeca->prox;
        free(pop->pessoa);
        free(pop);
        return head;
    } //do meio
    pop->anterior->prox = pop->prox;
    pop->prox->anterior = pop->anterior;
    free(pop->pessoa);
    free(pop);
    return cabeca;
}

p_no_paciente adicionar_lista_fim(p_no_paciente cabeca, paciente *humano, deck *deki) //adiciona paciente ao fim da lista, retornando cabeçaa da lista e atualizando o deck
{
    p_no_paciente final = malloc(sizeof(No_paciente));
    final->pessoa = humano;
    if(cabeca == NULL)
    {
        final->anterior = NULL;
        final->prox = NULL;
        deki->fim = final;
        deki->cabeca = final;
        return final;
    }
    final->anterior =deki->fim;
    deki->fim->prox = final;
    final->anterior = deki->fim;
    final->prox = NULL;
    deki->fim = final;
    return cabeca;

}

p_no_paciente adicionar_lista_inicio(p_no_paciente cabeca, paciente *humano, deck *decki) //adiciona paciente no inicio da fila
{
    p_no_paciente inicio = malloc(sizeof(No_paciente));
    inicio->pessoa = humano;
    if(cabeca == NULL) //fila vazia
    {
        inicio->prox = NULL;
        inicio->anterior = NULL;
        decki->cabeca = inicio;
        decki->fim = inicio;
        return inicio;
    } //fila não vazia
    inicio->prox = cabeca;
    inicio->anterior = NULL;
    cabeca->anterior = inicio;
    decki->cabeca = inicio;
    return inicio;
}

p_no remover_inicio(p_no lixo) //remove nó do inicio da lista ligada
{
    p_no novo;
    novo = lixo->prox;
    if(novo != NULL)
        novo->anterior = NULL;
    free(lixo);
    return novo;
}

void fila_atendimento(int atual,p_no_paciente individuo, MED *vetor_med) //adiciona paciente a fila do medico e atualiza deck do medico
{
    individuo->pessoa->ocupado =1;
    if(individuo->pessoa->carteira == PREFERENCIAL)
    {
        vetor_med[atual-1].fila =  adicionar_lista_inicio(vetor_med[atual-1].fila,individuo->pessoa, vetor_med[atual-1].deck_medico); //adiciona paciente prioritario
    }
    if(individuo->pessoa->carteira == NORMAL)
    {
        vetor_med[atual-1].fila =  adicionar_lista_fim(vetor_med[atual-1].fila,individuo->pessoa, vetor_med[atual-1].deck_medico); //adiciona paciente normal
    }
}

int comprimento_palavra(char palavra[13]) //conta tamanho da palavra
{
    int contador=0;
    for(int i =0; palavra[i] != '\0' ;i++)
    {
        contador++;
    }
    return contador;
}

int avaliar_prioridade(char estado[13]) //transforma normal e preferencial em inteiros arbitrários
{
    int parametro;
    parametro = comprimento_palavra(estado);
    if(parametro == 6)
    {
        return NORMAL;
    }
    return PREFERENCIAL;
}

p_no inserir_lista(p_no inicio_lista, int x) //adcionar elemento no inicio da lista ligada
{
    if(x ==0)
    {
        return inicio_lista;
    }
    p_no Novo_elemento = malloc(sizeof(No)); // dar free dps
    Novo_elemento->valor = x;
    Novo_elemento->prox = inicio_lista;
    Novo_elemento->anterior = NULL;
    if(inicio_lista != NULL)
    {
        inicio_lista->anterior = Novo_elemento;
    }
    return Novo_elemento;
}

p_no inverter(p_no lista) //inverte a ordem da lista ligada
{
    p_no lista_invertida =NULL, paciente_atual;
    paciente_atual = lista;
    while (paciente_atual != NULL)
    {
        lista_invertida = inserir_lista(lista_invertida, paciente_atual->valor);
        paciente_atual = paciente_atual->prox;
    }
    apagar_lista(lista);
    return lista_invertida;
}

void atender(MED *vetor_medicos)
{
    for(int i =0; i<9; i++) //percorre todos os medicos do vetor de medico
    {
        if(vetor_medicos[i].fila != NULL) // garante que fila do médico não está vazia
        {
            p_no_paciente paciente_atual = vetor_medicos[i].fila;
            int parametro = 0; //contador de paciente atendidos pelo medico
            while(paciente_atual != NULL && paciente_atual->pessoa->atendimento != NULL && parametro <vetor_medicos[i].maximo) //garante que o médico pode atender mais paciente e que eles existem
            {
                paciente_atual->pessoa->ocupado = 0; //paciente liberado
                paciente_atual->pessoa->atendimento= remover_inicio(paciente_atual->pessoa->atendimento); //tira consulta dos atendimentos do paciente
                p_no_paciente lixo = paciente_atual; //cria nó para poder ser liberado sem quebrar o código
                paciente_atual = paciente_atual->prox; //atualiza paciente
                vetor_medicos[i].fila = paciente_atual; //atualiza fila médico
                free(lixo); //libera paciente
                parametro++; //  incrementa parametro
            }
        }
    }
}

void recepcionista(MED *vetor_medicos ,p_no_paciente fila_ordenada_pacientes, deck *fila) //recepciona pacientes encaminhando para os médicos, dando saida, e incrementando o horário
{
    int horario = 480; //horario inicial em minutos
    while (fila_ordenada_pacientes != NULL) //percorre enquanto houverem pacientes no hospital
    {
        p_no_paciente paciente_movel = fila_ordenada_pacientes; //ponteiro movel recebe inicio da fila
        while (paciente_movel != NULL) //enquanto a fila não chega ao fim
        {
            p_no atendimento = paciente_movel->pessoa->atendimento; //fila dde atendimentos de 1 paciente
            if (atendimento == NULL) //se ja foi atendido
            {
                saida(paciente_movel->pessoa->nome, horario);
                p_no_paciente lixo = paciente_movel; //cria ponteiro para poder apagar paciente sem quebrar o código
                paciente_movel = paciente_movel->prox; //atualiza ponteiro movel
                fila_ordenada_pacientes = remover(lixo,fila_ordenada_pacientes, fila); //remove paciente da fila do hospital
            }
            else if (paciente_movel->pessoa->ocupado != 1) //se paciente não estiver ocupado
            {
                fila_atendimento(atendimento->valor, paciente_movel, vetor_medicos); //adiciona a fila do médico
                paciente_movel = paciente_movel->prox; //atualiza ponteiro movel
            }
            else
            {
                paciente_movel = paciente_movel->prox; //atualiza ponteiro movel
            }
        }
        atender(vetor_medicos); //todos os médicos atendem os pacientes que estão na sua fila, respeitando a limitação de atendimentos
        horario += 10; //incrementa 10 minutos
    }
}

int main()
{
    p_deck deck_pacientes =malloc(sizeof(deck)); //deck da fila geral de pacientes
    deck_pacientes->cabeca = NULL;
    deck_pacientes->fim = NULL;
    MED *vetor_med = malloc(9*sizeof(MED)); //vetor de medicos
    preencher_vetor(vetor_med);
    char carteira[13];
    int prioridade;
    p_no_paciente cabeca =NULL; //primeiro nó da lista de pacientes do hospital
    while (1){ //leitura dos dados do paciente
        paciente *pessoa = malloc(sizeof(paciente));
        scanf("\"%[^\"]\" %s",pessoa->nome, carteira);
        prioridade = avaliar_prioridade(carteira);
        pessoa->carteira = prioridade;
        pessoa->ocupado = 0;
        int saida = 0;
        pessoa->atendimento = NULL;
        while(1)
        {
            int profissional = 0;
            saida = scanf("%d ", &profissional);
            pessoa->atendimento = inserir_lista(pessoa->atendimento,profissional); // adiciona numero a lista ligada de ints
            //Adiciona o profissional que o cliente atual necessita
            if (saida != 1)
                break;
        }
        pessoa->atendimento = inverter(pessoa->atendimento); //iverte a lista de numeros
        cabeca = adicionar_lista_fim(deck_pacientes->cabeca, pessoa,deck_pacientes); //adiciona pessoa lista do hospital
        deck_pacientes->cabeca = cabeca;
        if (saida == EOF)
            break;
    }
    recepcionista(vetor_med, cabeca, deck_pacientes); //gerencia fila geral do hospital
    for(int i = 0; i<9;i++)
    {
        free(vetor_med[i].deck_medico); //libera deck dos medicos
    }
    free(vetor_med); //libera os medicos
    free(deck_pacientes); //libera o deck
    return 0;
}