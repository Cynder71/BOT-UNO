#ifndef MACRO_H
#define MACRO_H
#include "baralho.h"

//TIPOS DE AÇÂO
#define DISCARD 1
#define TURN 2
#define BUY 3
#define SAY 4

int guardarPlayers(char *str, char mat[][20]); //Guarda os nomes dos players numa matriz.

void my_strcpy(char *destino, char *origem, int n); //Similar a função strcpy

int analisa_acao(char* acao);//Informa qual o tipo da ação passada (DISCARD,SAY,BUY...)

void guardar_cartas(Baralho* baralho, char* string_de_cartas);//Ajusta a entrada das cartas HAND para o formato adequado e adiciona todas as cartas no baralho passado

Carta converte_string_para_carta(char* str);

int converte_string_para_naipe(char* str);

void debug(char *message);
#endif