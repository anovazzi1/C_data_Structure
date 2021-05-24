typedef struct No //nó duplo ligado que carrega um inteiro
{
    int valor;
    struct No *prox;
    struct No *anterior;
} No;

typedef struct No *p_no; // ponteiro para nó de int

typedef struct paciente //paciente 
{
    int ocupado; //indicador se está na fila de um médico ou não : 0 livre, 1 ocupado
    char nome[50]; //nome do paciente
    int carteira; // preferencial ou normal
    p_no atendimento; //lista ligada de ints que representam ids dos medicos para consulta
}paciente;

typedef struct No_paciente //nó para strcut paciente
{
    struct paciente *pessoa; //paciente dentro do nó
    struct No_paciente *prox;
    struct No_paciente *anterior;
}No_paciente;

typedef struct No_paciente *p_no_paciente; // ponteiro para nó paciente

typedef struct deck //estrutura que armazena o primeiro e o ultimo nó de uma lista ligada
{
    p_no_paciente cabeca;
    p_no_paciente fim;   
}deck;

typedef struct deck *p_deck; //ponteiro pra deck

typedef struct medico //medico
{
    p_no_paciente fila; //ponteiro para fila de nó de pacientes que devem ser atendidos
    int indentificador; // identificador do medico
    int maximo; //maximo de atendimentos possivel
    p_deck deck_medico; //ponteiro para deck da lista de pacientes do médico
}MED;
