#include <stdio.h>
#include "professor_carlos.h"


Aluno verificar_lexicografia(Aluno A, Aluno B)
{
    int i;
    for(i =0; A.nome[i] != '\0' && B.nome[i] != '\0'; i++)
    {   
        if(A.nome[i]<B.nome[i])
        {
            return A;
        }
        else if(A.nome[i]>B.nome[i])
        {
            return B;
        }
        else if (A.nome[i+1] =='\0' && B.nome[i+1] != 0){
            return A;
        }
        else if(A.nome[i+1] !='\0' && B.nome[i+1] == 0){
            return B;
        }
    }
    for(int k = 0;A.sobrenome[k] != '\0' && B.sobrenome[k] != '\0';k++)
    {
        if(A.sobrenome[k]<B.sobrenome[k])
        {
            return A;
        }
        else if(A.sobrenome[k]>B.sobrenome[k])
        {
            return B;
        }
        else if (A.sobrenome[k+1] =='\0' && B.sobrenome[k+1] != 0){
            return A;
        }
        else if(A.sobrenome[k+1] !='\0' && B.sobrenome[k+1] == 0){
            return B;
        }
    }
    return A;
}

Aluno comparar_idade(Aluno A, Aluno B, int parametro){
    Aluno velho, novo;
    //  printf("A:%s B:%s\n", A.nome, B.nome);
    //  printf("Ano A %d Ano B %d \n", A.nascimento.ano, B.nascimento.ano);
    if(A.nascimento.ano < B.nascimento.ano){
        velho = A;
        novo =  B;
    }
    else if(A.nascimento.ano > B.nascimento.ano)
    {
        novo = A;
        velho = B;
    }
    else if(A.nascimento.ano == B.nascimento.ano)
    {
        if (A.nascimento.mes < B.nascimento.mes)
        {
            velho = A;
            novo = B;
        }
        else if(A.nascimento.mes > B.nascimento.mes)
        {
            novo = A;
            velho = B;
        }
        else if(A.nascimento.mes == B.nascimento.mes)
        {
            if(A.nascimento.dia < B.nascimento.dia)
            {
                velho = A;
                novo = B;
            }
            else if(A.nascimento.dia > B.nascimento.dia)
            {
                novo = A;
                velho = B;
            }
            else if(A.nascimento.dia == B.nascimento.dia)
            {
               velho = verificar_lexicografia(A, B);
               novo = velho;
            }
        }
    }
    if(parametro == 0)
    {
        return velho;
    }
    return novo;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j)
{
    Aluno aluno_novo;
    aluno_novo = t[j].alunos[0];
    for(int k = 1; k<t[j].qtd; k++){
        aluno_novo = comparar_idade(aluno_novo, t[j].alunos[k], 1);
    } 
    return aluno_novo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    Aluno aluno_velho;
    aluno_velho = t[j].alunos[0];
    for(int k = 1; k<t[j].qtd; k++)
    {
        aluno_velho = comparar_idade(aluno_velho, t[j].alunos[k], 0);
    }     
    return aluno_velho;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
    Aluno aluno_novo;
    aluno_novo = t[0].alunos[0];
    for(int i =0; i < qtd_turmas; i++){
        for(int k = 0; k < t[i].qtd; k++)
        {
            aluno_novo = comparar_idade(aluno_novo, t[i].alunos[k], 1);
        }
    }
    return aluno_novo;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    Aluno aluno_velho;
    aluno_velho = t[0].alunos[0];
    for(int i =0; i < qtd_turmas; i++){
        for(int k = 0; k < t[i].qtd; k++)
        {
            aluno_velho = comparar_idade(aluno_velho, t[i].alunos[k], 0);
        }
    }
    return aluno_velho;
}

int add_aluno(Turma t[], Aluno A, int j){
    int posicao_ultimo;
    posicao_ultimo = t[j].qtd;
    t[j].qtd ++;
    t[j].alunos[posicao_ultimo] = A;
    return posicao_ultimo + 1;
}

int remove_aluno(Turma t[], int j){
    int posicao_ultimo;
    posicao_ultimo = t[j].qtd;
    t[j].qtd = t[j].qtd -1 ;
    return posicao_ultimo - 1;    
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao){
    int contador, numero_alunos = 0;
    char *local_padrao;
    local_padrao = padrao;
    for(contador = 0; *local_padrao != '\0'; local_padrao ++){
        contador++;
    }
    for(int i = 0; i < qtd_turmas; i++){
        for(int k = 0; k < t[i].qtd; k++){
            int achou =0, j = 0;           
            for(int letra = 0; t[i].alunos[k].nome[letra] != '\0' && achou == 0; letra++){
                if(t[i].alunos[k].nome[letra] == padrao[j])
                {
                    j++;
                    if(j == contador)
                    {
                        // printf("%s \n", t[i].alunos[k].nome);
                        numero_alunos ++;
                        achou = 1;
                    }
                }
                else
                {
                    j = 0;
                }
                
            }
        }
    }
    return numero_alunos;
}