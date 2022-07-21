#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define N 40

struct _func{
    int cod;
    char nome[N];
    double salario;
    struct _func *next;
    struct _func *prev;
};
typedef struct _func Funcionario;

typedef struct list{
    Funcionario *first;
    Funcionario *last;
}Lista;

int listaVazia(Funcionario *first){
    if(first == NULL)
        return 1;
    return 0;
}

Funcionario *procura(Lista *lista, int cod){
    Funcionario *aux;
    for(aux = lista->first;aux->next != NULL;aux = aux->next){
        if(aux->cod == cod){
            return aux;
        }
    }
    return NULL;
}

void adicionaInicio(Lista *lista,Funcionario *novo){
    if(listaVazia(lista->first)){
        lista->first = novo;
        lista->last = novo;
        return;
    }
    novo->next = lista->first;
    novo->next->prev = novo;
    lista->first = novo; 
    return;
}

void adicionaMeio(Lista *lista, Funcionario *elemento, Funcionario *novo){
    if(listaVazia(lista->first)){
        lista->first = novo;
        lista->last = novo;
        return;
    }
    novo->next = elemento;
    elemento->prev->next = novo;
    novo->prev = elemento->prev;
    elemento->prev = novo;
    return;
}


void deletar(Lista *lista, int cod){
    Funcionario *aux, *previous , *next;
    if((listaVazia(lista->first)))
        return;
    for(aux = lista->first; aux->cod != cod; aux = aux->next);
    if(aux == NULL)
        return;   
    if(lista->first == aux){
        if(aux == lista->last){
           lista->last = NULL;
           lista->first = NULL;
           
        }else{
            lista->first = lista->first->next;
            lista->first->prev = NULL;
        }
    }
    else if(lista->last == aux){
        lista->last = lista->last->prev;
        lista->last->next = NULL;
    }
    else{
            previous = aux->prev;
            next = aux->next;
            previous->next = next;
            // aux->prev->next = aux->next
            next->prev = previous;
            // aux->next->prev = aux->previous
        
    }
    free(aux);
}

// Funcionario *adicionaFinal(Funcionario *first,Funcionario *novo){
//     Funcionario *aux;
//     if(listaVazia(first)){
//         return novo;
//     }    
//     for(aux = first; aux->next != NULL; aux=aux->next);
//     aux->next = novo;
//     return first;
// }

// Funcionario *adicionaDepois(Funcionario *first,Funcionario *novo, int v){
//     Funcionario *aux;
//     if(listaVazia(first)){
//         return novo;
//     }
//     for(aux = first; aux->next != NULL; aux=aux->next){
//         if(aux->cod == v){
//             novo->next = aux->next;
//             aux->next = novo;

//             break;
//         }
//     }
//     return first;
// }

Funcionario *criaFunc(int cod, char nome[], double salario){
    Funcionario *novo = malloc(sizeof(Funcionario));
    novo->cod = cod;
    snprintf(novo->nome, sizeof(novo->nome), "%s", nome);
    novo->salario = salario;
    novo->next = NULL;
    return novo;
}

void printLista(Funcionario *first){
    Funcionario *aux;
    for(aux = first; aux != NULL; aux=aux->next){
        printf("%d %s %lf", aux->cod, aux->nome, aux->salario);
        printf("\n");
    }
}

void printListaContrario(Funcionario *last){
    Funcionario *aux;
    for(aux = last; aux !=NULL; aux = aux->prev){
        printf("%d %s %lf", aux->cod, aux->nome, aux->salario);
        printf("\n");
    }
}

int main(){
    Lista *lista = malloc(sizeof(Lista));
    lista->first = NULL; lista->last = NULL;
    adicionaInicio(lista, criaFunc(1, "João", 1000.0));
    adicionaInicio(lista, criaFunc(2, "Weverton", 1001.0));
    adicionaInicio(lista, criaFunc(3, "Luiz", 1002.0));
    adicionaMeio(lista, procura(lista,2), criaFunc(4, "Jardel", 1003.0));
    deletar(lista, 1);deletar(lista, 2);deletar(lista, 3);deletar(lista, 4);
    printLista(lista->first);
    printf("\n");
    printListaContrario(lista->last);
    adicionaInicio(lista, criaFunc(1, "João", 1000.0));
    adicionaInicio(lista, criaFunc(2, "Weverton", 1001.0));
    printListaContrario(lista->last);

   
    return 0;
}
