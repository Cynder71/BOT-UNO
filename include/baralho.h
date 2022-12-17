#ifndef BARALHO_H
#define BARALHO_H

//MACROS DE CARTAS ESPECIAIS
#define BARALHO_AS 1
#define BARALHO_J  11
#define BARALHO_Q  12
#define BARALHO_K  13
#define BARALHO_V  14
#define BARALHO_D  15
#define BARALHO_R  16
#define BARALHO_C  17 

//MACROS DE COMPARAÇÃO DE CARTA
#define INCOMPATIVEL 0 
#define COMPATIVEL 1
#define IGUAL 2

//MACROS DE NAIPES
#define COPAS  0
#define ESPADAS 1
#define PAUS  2
#define OURO  3
#define NAIPE_ERRO 4
/// @brief 

//Estrutura carta, com a carta inteira, separada por naipe e valor e com valores inteiros que representam os diferentes naipes e valores (para facilitar comparações)
struct  carta{
    char carta_str[15];
    char valor_str[5];
    char naipe_str[5];
    int naipe_int;
    int valor_int;
};

//Estruturas criadas em baralho.c
typedef struct carta Carta;
typedef struct baralho Baralho;

Baralho* cria_baralho(); //cria baralho :p

int naipe_preferido(Baralho* baralho); //Analisa o baralho e retorna o naipe que mais se repetir entre as cartas.

int compara_carta(Carta c1, Carta c2); //Separa as cartas em passadas em 3 categorias: compativeis, incompativeis e iguais (mais informações em baralho.c)

int adiciona_carta(Baralho* baralho, Carta carta); //adiciona a carta no final do baralho passado

int tamanho_baralho(Baralho* baralho); //retorna a quantidade de cartas que tem no baralho :p

int adiciona_carta_no_inicio(Baralho* baralho, Carta carta);  //similar ao adiciona_carta, mas agora no início

int acessa_carta(Baralho* baralho, int index, Carta* carta); //acessa a carta no baralho correspondente ao indíce passado, a carta "em branco" passada na prórpia função será alterada por referência para corresponder a carta que foi de fato encontrada.

int descarta_carta(Baralho* baralho, int index);  //remove a carta do baralho correspondente ao índice passado

int gira_baralho(Baralho* baralho); //Pega a primeira carta do baralho e coloca no final, a segundo vira a primeira, a terceira a segunda e assim por diante...

int destroi_baralho(Baralho* baralho); //libera toda a momória alocada para o baralho

void printa_baralho(Baralho* baralho); //printa todas as cartas que estão no baralho no momento que a função for chamada

void printa_de_tras_para_frente(Baralho* baralho); //Similar ao anterior, mas de trás para frente


#endif