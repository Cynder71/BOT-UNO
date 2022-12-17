#include <stdlib.h>
#include "../include/lista_de_eventos.h"

//Criação de nó para a lista duplamente encadeada
typedef struct no{
   Evento evento;
   struct no* proximo;
   struct no* anterior;
}No;

//Lista duplamente encadeada
struct lista_de_eventos{
    No* cabeca;
    No* cauda;
    int tam;
};


Lista_de_eventos* cria_lista_de_eventos(){ //cria a lista de eventos, começa vazia
    Lista_de_eventos* novo_lista_de_eventos = (Lista_de_eventos*)malloc(sizeof(Lista_de_eventos));
    if(novo_lista_de_eventos != NULL){ //se o lista_de_eventos foi alocado com sucesso
        novo_lista_de_eventos->cabeca = NULL; //aponta para nada pq não foi adicionada nenhum evento (ainda)
        novo_lista_de_eventos->cauda=NULL;
        novo_lista_de_eventos->tam = 0;  
    }
    return novo_lista_de_eventos;
}

int tamanho_lista_de_eventos(Lista_de_eventos* lista_de_eventos){ 
    if(lista_de_eventos==NULL)return 0;
    return lista_de_eventos->tam; //retorna a quantidade de eventos que estão na lista
}

int adiciona_evento(Lista_de_eventos* lista_de_eventos, Evento evento){ //adiciona evento na lista passada
    if(lista_de_eventos == NULL)return 0;//Lista_de_eventos passado não existe

    No* novo_no = (No*)malloc(sizeof(No));
    if(novo_no == NULL)return 0; // Não foi possível alocar um novo nó
    
    novo_no->evento = evento;
    novo_no->proximo = NULL;


    if(lista_de_eventos->tam==0){
        novo_no->anterior = NULL;
        lista_de_eventos->cabeca=novo_no;
    }else{
        novo_no->anterior = lista_de_eventos->cauda;
        lista_de_eventos->cauda->proximo = novo_no;
    }
    
    lista_de_eventos->cauda = novo_no;

    lista_de_eventos->tam++; //atualiza a quantidade de eventos do lista_de_eventos
    return 1; //nada pegou fogo
}

int adiciona_evento_no_inicio(Lista_de_eventos* lista_de_eventos, Evento evento){ //adiciona evento no início da lista passada
 if(lista_de_eventos == NULL)return 0;//Lista_de_eventos passado não existe

    No* novo_no = (No*)malloc(sizeof(No));
    if(novo_no == NULL)return 0; // Não foi possível alocar um novo nó
    
    novo_no->evento = evento;
    novo_no->proximo = lista_de_eventos->cabeca;
    novo_no->anterior = NULL;

    lista_de_eventos->cabeca = novo_no;

    if(novo_no->proximo!=NULL){
      
        novo_no->proximo->anterior = novo_no;
    }

    if(lista_de_eventos->tam==0){
        lista_de_eventos->cauda = novo_no;
    }

    lista_de_eventos->tam++; //atualiza a quantidade de eventos do lista_de_eventos
    return 1; //nada pegou fogo
}

int acessa_evento(Lista_de_eventos* lista_de_eventos, int index, Evento* evento){ //fotocópia de eventos / método getter da deep web
    if(lista_de_eventos == NULL || index >= lista_de_eventos->tam)return 0; //lista_de_eventos não existe ou índice passado excede a quantidade de eventos que existem no lista_de_eventos

    No* procurador = lista_de_eventos->cabeca; //"entra" pro lista_de_eventos
    for(int i=0; i<index; i++){//avança na estrutura de nós até chegar no nó que corresponde ao index
        procurador = procurador->proximo;  
    }
    *evento = procurador->evento; //"copia" a informação da evento encontrada para uma evento em branco.
    return 1; //esperamos que nada tenha pego fogo
}

int descarta_evento(Lista_de_eventos* lista_de_eventos, int index){ //Descarta o evento da lista correspondente ao indíce passado
    if(lista_de_eventos == NULL || index >= lista_de_eventos->tam)return 0;//lista_de_eventos não existe ou índice passado excede a quantidade de eventos que existem no lista_de_eventos
    
    No* apagado = lista_de_eventos->cabeca;

    if(index==0){ 
        if(lista_de_eventos->tam == 1){
            lista_de_eventos->cauda = NULL;
        }
        lista_de_eventos->cabeca = lista_de_eventos->cabeca->proximo;
        free(apagado);
        lista_de_eventos->tam--;
        return 1;
    }

    for(int i=0; i<index; i++){
        apagado = apagado->proximo;
    }
    
    if(apagado->anterior != NULL){
       apagado->anterior->proximo = apagado->proximo; 
    }

    if(apagado->proximo != NULL){
        apagado->proximo->anterior = apagado->anterior;
    }

    free(apagado); 
    lista_de_eventos->tam--;
    return 1;
}

int gira_lista_de_eventos(Lista_de_eventos* lista_de_eventos){ //Pega o primeiro evento da lista e coloca no final, o segundo vira o primeiro, o terceiro o segunda e assim por diante...
    if(lista_de_eventos == NULL)return 0;
    if(lista_de_eventos->tam == 0 || lista_de_eventos->tam == 1)return -1;

    lista_de_eventos->cauda->proximo = lista_de_eventos->cabeca;
    lista_de_eventos->cabeca->anterior = lista_de_eventos->cauda;
    lista_de_eventos->cabeca->proximo->anterior = NULL;
    lista_de_eventos->cabeca = lista_de_eventos->cabeca->proximo;
    lista_de_eventos->cauda->proximo->proximo = NULL;
    lista_de_eventos->cauda = lista_de_eventos->cauda->proximo;
    return 1;
}

int destroi_lista_de_eventos(Lista_de_eventos* lista_de_eventos){ //Destrói a lista (libera a memória)
    if(lista_de_eventos == NULL)return 0;
    while(lista_de_eventos->tam > 0)
        descarta_evento(lista_de_eventos, 0);
    free(lista_de_eventos);
    return 1;
}
