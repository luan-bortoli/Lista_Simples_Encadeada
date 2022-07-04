#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAT 10
#define TAM_NOME 40

struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct data Data;

struct aluno{
    char matricula[TAM_MAT+1];
    char nome[TAM_NOME+1];
    Data dataNasc;
    float nota;
    struct aluno *next;
};

typedef struct aluno Aluno;

Aluno *inserir(Aluno *al){
    al = (Aluno *)malloc(sizeof(Aluno));
    //printf("Digite a matricula: ");
    scanf("%s", al->matricula);
    //printf("Digite o nome: ");
    scanf("%s", al->nome);
    //printf("Digite a data de nascimento: ");
    scanf("%d/%d/%d", &al->dataNasc.dia, &al->dataNasc.mes, &al->dataNasc.ano);
    //printf("Digite a nota: ");
    scanf("%f", &al->nota);
    al->next = NULL;
    return al;
}

Aluno *deletar(Aluno *first, char *matricula){
    Aluno *aux, *prev_aux = first;
    for(aux = first;aux != NULL; aux = aux->next){
        if(strcmp(aux->matricula, matricula) == 0){
            if(aux == first){
                first = first->next;
                free(prev_aux);
                return first;
            }
            prev_aux->next = aux->next;
            free(aux);
            return first;
        }
        prev_aux = aux;
    }
    return first;
}

int posRegistroDelete(Aluno *first, char matricula[TAM_MAT]){
    Aluno *aux;
    int pos;
    for(aux = first;aux != NULL; aux = aux->next){
        if(strcmp(aux->matricula, matricula) == 0){
            pos++;
        }
        return pos;
    }
}

Aluno *atualizarRegistros(Aluno *first, Aluno *aux){
    if(first != NULL){
        aux = first;
    }
    while(1){
        if(aux->next == NULL){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void imprimirAluno(Aluno *first){
    Aluno *aux;
    
     for(aux = first;aux != NULL; aux = aux->next){
         printf("%s, %s, %d/%d/%d, %.2f\n", aux->matricula, aux->nome, aux->dataNasc.dia, aux->dataNasc.mes, aux->dataNasc.ano, aux->nota);
     }
}

void imprimirAlunoInverso(Aluno *first){
    if(first == NULL){
        return;
    }
    imprimirAlunoInverso(first->next);
    printf("%s, %s, %d/%d/%d, %.2f\n", first->matricula, first->nome, first->dataNasc.dia, first->dataNasc.mes, first->dataNasc.ano, first->nota);
}

int contarAlunos(Aluno *first){
    int qtd = 0;
    while(first != NULL){
        qtd++;
        first = first->next;
    }
    return qtd;
}

void sairPrograma(Aluno *first){
    Aluno *aux;
    aux = first;
    while(aux != NULL){
        Aluno *next = aux->next;
        free(aux);
        printf("-");
        aux = next;
    }
}

int menu(){
    int op;
    //printf("Digite a opcao desejada: \n");
    //printf("1 - Inluir elemento na lista\n");
    //printf("2 - Excluir elemento da lista\n");
    //printf("3 - Listar todos os elementos da lista na ordem de inclusão\n");
    //printf("4 - Listar todos os elementos da lista na ordem inversa a inclusão\n");
    //printf("5 - Apresentar quantos elementos existem na lista\n");
    //printf("0 - Sair do programa\n");
    scanf("%d", &op);
    return op;
}

int main()
{
    int op, qtd;
    Aluno *al, *aux, *first = NULL;
    char matricula[TAM_MAT+1];
    
    while (1){
        op = menu();
        if(op == 1){
            al = inserir(al);
            if(first == NULL){
                first = al;
                aux = al;
            }
            else{
                aux->next = al;
                aux = al;
            }
        }
        else if(op == 2){
            if (!contarAlunos(first)){
                printf("Lista Vazia!\n");
            }
            else{
                //printf("Digite a matricula para excluir? ");
                scanf("%s", matricula);
                for(int i=posRegistroDelete(first, matricula);i>0;i--){
                    first = deletar(first, matricula);
                    aux = atualizarRegistros(first, aux);
                }
            }
        }
        else if (op == 3){
            if (!contarAlunos(first)){
                printf("Lista Vazia!\n");
            }
            else{
                imprimirAluno(first);
            }
        }
        else if (op == 4){
            if (!contarAlunos(first)){
                printf("Lista Vazia!\n");
            }
            else{
                imprimirAlunoInverso(first);
            }
        }
        else if (op == 5){
            if(!contarAlunos(first)){
                printf("Lista Vazia!\n");  
            }
            else{
                printf("%d\n", contarAlunos(first));
            }
        }
        else if (op == 0){
            sairPrograma(first);
            printf("\n\n");
            exit(0);
        }
    }
    return 0;
}
