#ifndef LISTA_DE_EVENTOS_H
#define LISTA_DE_EVENTOS_H

#include "baralho.h"

/// @brief
//Estrutura evento, com ação (ex:DISCARD,BUY,SAY...), complemento (cartas relacionadas a ação), complemento2 (naipe que existe caso a carta do complemento peça uma mudança de naipe)
struct evento {
  char action[15];
  char complemento[20];
  char complemento2[20];
};

//Estruturas criadas em lista_de_eventos.c
typedef struct evento Evento;
typedef struct lista_de_eventos Lista_de_eventos;

Lista_de_eventos *cria_lista_de_eventos();//cria uma lista_de_eventos, que começa vazia

int adiciona_evento(Lista_de_eventos *lista_de_eventos, Evento evento);//adiciona evento no final da lista_de_eventos passada

int tamanho_lista_de_eventos(Lista_de_eventos *lista_de_eventos);//retorna a quantidade de eventos da lista_de_eventos

int adiciona_evento_no_inicio(Lista_de_eventos *lista_de_eventos, Evento evento); //adiciona evento no início da lista_de_eventos

int acessa_evento(Lista_de_eventos *lista_de_eventos, int index, Evento *evento);//acessa o evento na lista_de_eventos correspondente ao indíce passado, o evento "em branco" passado na prórpia função será alterado por referência para corresponder ao evento que foi de fato encontrado.

int descarta_evento(Lista_de_eventos *lista_de_eventos, int index);//remove o evento da lista_de_eventos correspondente ao índice passado

int gira_lista_de_eventos(Lista_de_eventos *lista_de_eventos);//Pega o primeiro evento da lista_de_eventos e coloca no final, o segundo vira o primeiro, o terceiro o segundo e assim por diante...

int destroi_lista_de_eventos(Lista_de_eventos *lista_de_eventos);//libera toda a momória alocada para a lista_de_eventos

#endif