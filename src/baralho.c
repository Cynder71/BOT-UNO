#include "../include/baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Criação de nó para a lista duplamente encadeada
typedef struct no {
  Carta carta;
  struct no *proximo;
  struct no *anterior;
} No;

//Lista duplamente encadeada
struct baralho {
  No *cabeca;
  No *cauda;
  int tam;
};

Baralho *cria_baralho() { //cria o baralho, começa vazio
  Baralho *novo_baralho = (Baralho *)malloc(sizeof(Baralho));
  if (novo_baralho != NULL) { // se o baralho foi alocado com sucesso
    novo_baralho->cabeca =
        NULL; // aponta para nada pq não foi adicionada nenhuma carta
    novo_baralho->cauda = NULL;
    novo_baralho->tam = 0; // autoexplicativo
  }
  return novo_baralho;
}

int tamanho_baralho(Baralho *baralho) {
  if (baralho == NULL)
    return 0;
  return baralho->tam; //retorna a quantidade de cartas que tem no baralho :p
}

int adiciona_carta(Baralho *baralho, Carta carta) { //adiciona a carta no baralho passado
  if (baralho == NULL)
    return 0; // Baralho passado não existe

  No *novo_no = (No *)malloc(sizeof(No)); //aloca memória para um novo nó
  if (novo_no == NULL)
    return 0; // Não foi possível alocar um novo nó

  novo_no->carta = carta;
  novo_no->proximo = NULL; // vai pro fim da lista

  if (baralho->tam == 0) {
    novo_no->anterior = NULL;
    baralho->cabeca = novo_no;
  } else {
    novo_no->anterior = baralho->cauda;
    baralho->cauda->proximo = novo_no;
  }

  baralho->cauda = novo_no;

  baralho->tam++; // atualiza a quantidade de cartas do baralho
  return 1;       // nada pegou fogo
}

int adiciona_carta_no_inicio(Baralho *baralho, Carta carta) { //similar ao adiciona_carta, mas agora no início
  if (baralho == NULL)
    return 0; // Baralho passado não existe

  No *novo_no = (No *)malloc(sizeof(No));
  if (novo_no == NULL)
    return 0; // Não foi possível alocar um novo nó

  novo_no->carta = carta;
  novo_no->proximo = baralho->cabeca;
  novo_no->anterior = NULL;

  baralho->cabeca = novo_no;

  if (novo_no->proximo != NULL) {
    novo_no->proximo->anterior = novo_no;
  }

  if (baralho->tam == 0) {
    baralho->cauda = novo_no;
  }

  baralho->tam++; // atualiza a quantidade de cartas do baralho
  return 1;       // nada pegou fogo
}

int acessa_carta(Baralho *baralho, int index,Carta *carta) { // fotocópia de cartas / método getter da deep web
  if (baralho == NULL || index >= baralho->tam)
    return 0; // baralho não existe ou índice passado excede a quantidade de cartas que existem no baralho

  No *procurador = baralho->cabeca; //"entra" pro baralho
  for (int i = 0; i < index; i++) { // avança na estrutura de nós até chegar no nó que corresponde ao index
    
    procurador = procurador->proximo;
  }
  *carta = procurador->carta; //"copia" a informação da carta encontrada par uma "carta em branco".
  
  return 1;                   // esperamos que nada tenha pego fogo
}

int descarta_carta(Baralho *baralho, int index) { //remove a carta do baralho correspondente ao índice passado
  if (baralho == NULL || index >= baralho->tam)
    return 0; // baralho não existe ou índice passado excede a quantidade de cartas que existem no baralho

  No *apagado = baralho->cabeca;

  if (index == 0) {
    if (baralho->tam == 1) {
      baralho->cauda = NULL;
    }
    baralho->cabeca = baralho->cabeca->proximo;
    free(apagado);
    baralho->tam--;
    return 1;
  }

  for (int i = 0; i < index; i++) {
    apagado = apagado->proximo;
  }

  if (apagado->anterior != NULL) {
    apagado->anterior->proximo = apagado->proximo;
  }

  if (apagado->proximo != NULL) {
    apagado->proximo->anterior = apagado->anterior;
  }

  free(apagado);
  baralho->tam--;
  return 1;
}

int gira_baralho(Baralho *baralho) { //Pega a primeira carta do baralho e coloca no final, a segundo vira a primeira, a terceira a segunda e assim por diante...
  if (baralho == NULL)
    return 0;
  if (baralho->tam == 0 || baralho->tam == 1)
    return -1;

  baralho->cauda->proximo = baralho->cabeca;
  baralho->cabeca->anterior = baralho->cauda;
  baralho->cabeca->proximo->anterior = NULL;
  baralho->cabeca = baralho->cabeca->proximo;
  baralho->cauda->proximo->proximo = NULL;
  baralho->cauda = baralho->cauda->proximo;
  return 1;
}

int destroi_baralho(Baralho *baralho) { //Destroi o baralho (libera a memória)
  if (baralho == NULL)
    return 0;
  while (baralho->tam > 0)
    descarta_carta(baralho, 0);
  free(baralho);
  return 1;
}

void printa_baralho(Baralho *baralho) { //printa todas as cartas que estiverem no baralho no momento 
  if (baralho == NULL)
    return;
  fprintf(stderr, "\nMeu baralho [");
  No *aux = baralho->cabeca;
  for (int i = 0; i < baralho->tam; i++) {
    fprintf(stderr, " %s ", aux->carta.carta_str);
    aux = aux->proximo;
  }
  fprintf(stderr, "]\n");
}

void printa_de_tras_para_frente(Baralho *baralho) { //mesma coisa de printa_baralho, mas de trás pra frente :p
  if (baralho == NULL)
    return;
  No *aux = baralho->cauda;
  for (int i = 0; i < baralho->tam; i++) {
    printf("%s\n", aux->carta.carta_str);
    aux = aux->anterior;
  }
}

int compara_carta(Carta c1, Carta c2) { //Analisa e separa duas cartas passadas em 3 categorias
  if(c1.valor_int == BARALHO_AS || c1.valor_int == BARALHO_C)return COMPATIVEL;
  if (strcmp(c1.carta_str,c2.carta_str)==0)
    return IGUAL; //As cartas são consideradas iguais se tanto seus naipes quanto seus valores forem iguais
  if (c1.naipe_int == c2.naipe_int || c1.valor_int == c2.valor_int) return COMPATIVEL; //Duas cartas são compativeis se seus naipes ou valores são iguais. Basta que um deles seja.
  return INCOMPATIVEL; //Se não é igual nem compatível, então é incompativel
}

int naipe_preferido(Baralho* baralho){ //Analisa o baralho e retorna o naipe que mais se repetir entre as cartas.
  Carta carta_fotocopia;
  int naipes[4]={0,0,0,0};
  for(int i=0;i<tamanho_baralho(baralho);i++){
    acessa_carta(baralho, 0,&carta_fotocopia);
    if(carta_fotocopia.naipe_int==COPAS) naipes[COPAS]++;
    else if(carta_fotocopia.naipe_int==ESPADAS) naipes[ESPADAS]++;
    else if(carta_fotocopia.naipe_int==PAUS) naipes[PAUS]++;
    else if(carta_fotocopia.naipe_int== OURO) naipes[OURO]++; 
    gira_baralho(baralho);
  }
  int naipe_dominante = 0;
  for(int i=0; i<4; i++)
    if(naipes[naipe_dominante]>=naipes[i])naipe_dominante=i;

  return naipe_dominante;
  
}
