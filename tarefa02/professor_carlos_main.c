#include<stdio.h>
#include "professor_carlos.h"
void criar_sala(int numero_alunos, int j, Turma t[])
{
    t[j].qtd =0;
    Aluno A;
    for(int i = 0; i<numero_alunos;i++){
         scanf("%d ", &j);
         scanf("%s ", A.nome);
         scanf("%s ", A.sobrenome);
         scanf("%d %d %d ", &A.nascimento.dia, &A.nascimento.mes, &A.nascimento.ano);
         add_aluno(t, A, j);
    }
}

int main(){
    Aluno novo, velho, A;
    int k, n, comando, j, total; //n quantidades de turma; k numero de operações; j turma escolhida 
    char string[6], *padrao ;
        Turma t[50];
    scanf("%d %d ",&n, &k);
    for(int g = 0; g<n; g++){
        int num_alunos;
        scanf("%d ", &num_alunos);
        criar_sala(num_alunos,g,t);
    }
    for(int i=0;i<k;i++){
        scanf("%d", &comando);
        if(comando==1){ //Dado um inteiro j, deve-se retornar o nome do aluno mais novo da turma j
            scanf("%d ", &j);
            novo = procura_novo_na_turma(t, n, j);
            printf("%s \n", novo.nome);
        }
        else if(comando==2){
            scanf("%d ", &j);
            velho = procura_velho_na_turma(t, n, j);
            printf("%s \n", velho.sobrenome);
        }
        else if(comando==3){
            velho = procura_velho_todas_turmas(t, n);
            printf("%s \n", velho.nome);
        }
        else if(comando==4){
            novo = procura_novo_todas_turmas(t, n);
            printf("%s \n", novo.sobrenome);
        }
        else if(comando==5){
            scanf("%s ",string);
            padrao = string;
            total = conta_substrings(t, n, padrao);
            printf("%d \n", total);
        }
        else if(comando==6){
            scanf("%d ", &j);
            scanf("%s ", A.nome);
            scanf("%s ", A.sobrenome);
            scanf("%d %d %d ", &A.nascimento.dia, &A.nascimento.mes, &A.nascimento.ano);
            total = add_aluno(t, A, j);
            printf("%d \n", total);
        }
        else if(comando==7){
            scanf("%d \n", &j);
            total = remove_aluno(t, j);
            printf("%d \n", total);
        }
    }
    return 0;
}
