#include<stdio.h>
#define max 6000

void cartao(int tabela[max][15], int o){ //le o cartão de 1 jogador e armazena escolhas em 1 vetor
    int escolhido_n = -1; //sincroniza a contagem com o index do arranjo
    short int numero_jogadores = 0;
    for(int i=0;i<60;i++){
        scanf("%hd ",&numero_jogadores);
        if(numero_jogadores == 1){
            escolhido_n ++;
            tabela[o][escolhido_n] = i+1;        
        }
    }
}

void ler_resultado(int corretos[6]){ // lê resultados sorteados
    int correto, i;
    for(i= 0; i<6; i++){
        scanf("%d",& correto );
        corretos[i] = correto;
    }
}


void verificar(int tabela_resultados[max][15], int corretos[6], int numero_jogadores, int numero_acertos[max]){
    for(int i = 0; i<numero_jogadores; i++){
        int acertos=0;
        for(int o = 0; o<15; o++){
            for(int j = 0; j<6; j++){
                if(tabela_resultados[i][o] == corretos[j]){
                    acertos ++;

                }
            }
        }
        numero_acertos[i] = acertos;
    }
}

void calcular_printar_valor(int numero_acertos[max], int numero_jogadores, double premio){
    int classes[3]={0,0,0};
    double sena, quina, quadra;
    for(int k=6;k>3;k--){
        for(int i = 0; i<numero_jogadores;i++){
            if(numero_acertos[i]==k){
                classes[6-k] += 1;
            }
        }
    }
       
    for(int j=0;j<numero_jogadores;j++){
        if(numero_acertos[j] == 6){
            sena = (premio * 0.62)/(classes[0]*1.0);
            printf("%.2lf\n", sena);
        }
        else if(numero_acertos[j] == 5){
            quina = (premio*0.19)/(classes[1]*1.0);
            printf("%.2lf\n", quina);
        }
        else if(numero_acertos[j] == 4){
            quadra =(premio*0.19)/(classes[2]*1.0);
            printf("%.2lf\n", quadra);
        }
        else
        {
            printf("0.00\n");
        }
        
    }
}

int main(void) //função principal
{
    int numero_jogadores, resultados_corretos; // numero_jogadores: numero de jogadores; i controlador; 6 numeros sorteados
    double premio; //valor do premio
    int corretos[6], tabela_resultados[max][15], numero_acertos[max]; //valores escolhidos; sorteados;matriz com valores escolhidos; acertos de cada jogador
    scanf("%d %lf\n",& numero_jogadores, &premio);
    for(int o= 0;o < numero_jogadores; o++){
        cartao(tabela_resultados, o); // lê cartão de cada jogador e altera valor vetor escolhido
    }
    for(int i = 0;i<6;i++){ //lê resultados corretos
        scanf("%d", &resultados_corretos);
        corretos[i] = resultados_corretos;
    }
    verificar(tabela_resultados, corretos, numero_jogadores, numero_acertos); //checa valor sorteado com valor escolhido
    calcular_printar_valor(numero_acertos,numero_jogadores, premio); // calcula premio e printa valor
    return 0;
}