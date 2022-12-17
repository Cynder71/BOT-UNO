#include "../include/utilidades.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_CARTAS 14

int guardarPlayers(char *str, char mat[][20]) { //Guarda os nomes dos players numa matriz.
  int qtdPlayers = 1;
  for (int i = 0; i < 100; i++) {
    if (str[i] == '\0')
      break;
    if (str[i] == ' ')
      qtdPlayers++;
  }
  if (qtdPlayers == 1)
    return 0;
  int k = 0;
  for (int i = 0; i < qtdPlayers; i++) {
    for (int j = 0; j < 20; j++) {
      if (str[k] != ' ' && str[k] != '\0') {
        mat[i][j] = str[k];
        k++;
      } else {
        k++;
        mat[i][j] = '\0';
        break;
      }
    }
  }
  return qtdPlayers;
}

void my_strcpy(char *destino, char *origem, int n) { //strcpy caseiro
  for (int i = 0; i < n; i++) {
    destino[i] = origem[i];
  }
  destino[n] = '\0';
}

int analisa_acao(char* acao){//Informa qual o tipo da ação passada (DISCARD,SAY,BUY...)
  if(strcmp(acao,"DISCARD")==0 || strcmp(acao,"TABLE")==0)return DISCARD;
  if(strcmp(acao,"TURN")==0)return TURN;
  if(strcmp(acao,"BUY")==0)return BUY;
  return SAY;
}


Carta converte_string_para_carta(char* str){ 
    char strcopy[10];
    strcpy(strcopy, str);
    Carta carta;
    strcpy(carta.carta_str,strcopy);

    if(strstr(strcopy,"♥")){

        carta.naipe_int = COPAS;
        strcpy(carta.naipe_str, "♥");

    }else if(strstr(strcopy,"♦")){

        carta.naipe_int = OURO;
        strcpy(carta.naipe_str, "♦");

    }else if(strstr(strcopy,"♣")){

        carta.naipe_int = PAUS;
        strcpy(carta.naipe_str, "♣");

    }else if(strstr(strcopy,"♠")){

        carta.naipe_int = ESPADAS;
        strcpy(carta.naipe_str, "♠");

    }else{

        carta.naipe_int = NAIPE_ERRO;
        strcpy(carta.valor_str, "ERRO");
        strcpy(carta.carta_str, "CARTA_ERRO");

    }
    
  
    if(carta.naipe_int != NAIPE_ERRO){
      char* ptr;
      ptr=strcopy;
      while(*ptr!="♣"[0])ptr++;
      *ptr = '\0';
      strcpy(carta.valor_str, strcopy);
      if(str[0]=='A')carta.valor_int = BARALHO_AS;
      else if(str[0]=='J')carta.valor_int = BARALHO_J;
      else if(str[0]=='D')carta.valor_int = BARALHO_Q;
      else if(str[0]=='R')carta.valor_int = BARALHO_K;
      else if(str[0]=='V')carta.valor_int = BARALHO_V;
      else if(str[0]=='C')carta.valor_int = BARALHO_C;

      else carta.valor_int = atoi(strcopy);
  

  }

    return carta;

}

void guardar_cartas(Baralho* baralho, char* string_de_cartas){ //Ajusta a entrada das cartas HAND para o formato adequado e adiciona todas as cartas no baralho passado
  char string_de_cartas_copia[100];// Algo do gênero [ 4♥ 10♦ 2♣ V♠ A♥ 3♦ 2♣ ]
  strcpy(string_de_cartas_copia, string_de_cartas);
  char* ptr;
  ptr = strtok(string_de_cartas_copia, " ");
  ptr = strtok(NULL, " ");
  for(int i=0;i<7;i++){
    adiciona_carta(baralho,converte_string_para_carta(ptr));
    ptr = strtok(NULL, " ");
  }
}

int converte_string_para_naipe(char* str){
  if(strstr(str,"♥")){
      return COPAS;
  }else if(strstr(str,"♦")){
    return OURO;
  }else if(strstr(str,"♣")){
    return PAUS;
  }else if(strstr(str,"♠")){
    return ESPADAS;
  }else{
    return NAIPE_ERRO;
  }
}

void debug(char *message) { fprintf(stderr, "%s\n", message); }

