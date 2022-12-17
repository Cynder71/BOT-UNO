#include "../include/baralho.h"
#include "../include/lista_de_eventos.h"
#include "../include/utilidades.h"
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10


int main() { 
  int houve_compra = FALSE; //auxiliar no tratamento de erros
  int aux_boleano = FALSE;
  char temp[MAX_LINE]; //variável de leitura de string rápida
  char my_id[MAX_ID_SIZE];
  char listaPlayers[10][20]; //cria a matriz que guarda os nomes dos diferentes jogadores da partida
  int qtdPlayers;
  Baralho *minhas_cartas = cria_baralho(); //cria a estrutura do tipo "Baralho" que será usada para guardar e manusear as cartas do Bot

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", temp); //Lê os players da partida
  qtdPlayers = guardarPlayers(temp, listaPlayers); //Guarda os players da partida em uma matriz

  scanf("YOU %s\n", my_id);//Lê o ID do próprio bot

  scanf("HAND %[^\n]\n", temp);//Lê as cartas que são passadas para o bot pelo gerenciador
  guardar_cartas(minhas_cartas, temp);//Guarda as cartas lidas numa estutura Baralho de nome minhas_cartas


  Carta carta_fotocopia; //usada para auxiliar a função acessa_carta

  scanf("TABLE %s\n", temp); //Lê a primeira carta da mesa

  //Serão utilizados para controlar os eventos do jogo
  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char complement2[MAX_LINE];

  Evento jogada; //Também será utilizada para controlar eventos dentro do jogo pela lista criada abaixo
  Lista_de_eventos *historico = cria_lista_de_eventos(); //histórico de todos os eventos do jogo

  //Pega as informações do primeiro evento do jogo (a carta que está na mesa) no histórico de eventos
  strcpy(jogada.action, "TABLE");
  strcpy(jogada.complemento, temp);
  strcpy(jogada.complemento2, "NULL");
  adiciona_evento_no_inicio(historico, jogada); //adiciona essa evento na lista
 

  while (1) {

    do {

      strcpy(complement2, "NULL"); //Pode ou não ser utilizado para ler strings que mudam o naipe do jogo, depende da carta que for jogada pelo adversário

      scanf("%s %s", action, complement); //Lê uma ação, como DISCARD de cartas, e um complemento, que é a carta que a ação se refere

      if (analisa_acao(action) == DISCARD && (complement[0] == 'A' || complement[0] == 'C')) { //Checa a necessidade de ler um segundo complemento a partir da ação do adversário e da carta que foi jogada
        scanf("%s", complement2);
      }

      //Pega os dados da jogada (evento) no histórico de eventos
      strcpy(jogada.action, action);
      strcpy(jogada.complemento, complement);
      strcpy(jogada.complemento2, complement2);
      adiciona_evento_no_inicio(historico, jogada); //Adiciona essa evento no histórico
      
    } while (strcmp(action, "TURN") || strcmp(complement, my_id)); //Para de "ouvir" as jogadas dos adversários quando o gerenciador informar que é a vez do Bot

    Evento evento_fotocopia; //auxiliar para a função acessa_evento
    
    houve_compra = FALSE; //auxiliar para o tratamento de erros
    
    do {
      descarta_evento(historico, 0); // Descarta primeiro evento do histórico, que contém a ação de turno do Bot (não é útil)
      
      acessa_evento(historico, 0, &evento_fotocopia); //vê qual foi o último acontecimento do jogo

      if (analisa_acao(evento_fotocopia.action)==BUY && houve_compra == FALSE){ //Tratamento de erro para evitar que o Bot ache que tem que comprar alguma carta sem necessidade
        houve_compra = TRUE;
      }

    } while (analisa_acao(evento_fotocopia.action) != DISCARD); //repete o processo até o último evento do jogo ser um descarte de cartas, para assim poder analisar a carta que de fato está na mesa

    Carta carta_que_esta_na_mesa;
    Evento meu_evento;
    carta_que_esta_na_mesa = converte_string_para_carta(evento_fotocopia.complemento); //Passa as informações sobre o último evento que será analisado para o formato de estrutura "Carta"

    Carta comprar;
    char str[10];
    //Se prepara para analisar um naipe diferente caso o oponente tenha descartado um Ás ou Coringa
    if (strcmp("NULL", evento_fotocopia.complemento2) != 0 && (carta_que_esta_na_mesa.valor_int == BARALHO_AS || carta_que_esta_na_mesa.valor_int == BARALHO_C)) {
      carta_que_esta_na_mesa.naipe_int = converte_string_para_naipe(evento_fotocopia.complemento2);
      strcpy(carta_que_esta_na_mesa.naipe_str, evento_fotocopia.complemento2);
    }

    //Checa se o oponente mandou comprar 2
    if (carta_que_esta_na_mesa.valor_int == BARALHO_V && houve_compra == FALSE) {
      printf("BUY 2\n");
      strcpy(meu_evento.action,"BUY");
      strcpy(meu_evento.complemento,"2");
      //Compra duas cartas
      for (int i = 0; i < 2; i++) {
        scanf("%s", str);
        comprar = converte_string_para_carta(str);
        adiciona_carta_no_inicio(minhas_cartas, comprar);
      }
    }
    //Checa se o oponente mandou comprar 4
    else if (carta_que_esta_na_mesa.valor_int == BARALHO_C && houve_compra == FALSE) {
      printf("BUY 4\n");
      strcpy(meu_evento.action,"BUY");
      strcpy(meu_evento.complemento,"4");
      //Compra quatro cartas
      for (int i = 0; i < 4; i++) {
        scanf("%s", str);
        comprar = converte_string_para_carta(str);
        adiciona_carta_no_inicio(minhas_cartas, comprar);
      }
    }else{

    // Hora de descartar uma carta

      Carta carta_na_mao; //auxiliar de acessa_carta
      int comparacao = INCOMPATIVEL;

      //Procura por um coringa no baralho e se o achar põe no início do baralho
        for (int i = 0; i < tamanho_baralho(minhas_cartas); i++) {
          acessa_carta(minhas_cartas, 0, &carta_na_mao);
          if(carta_na_mao.valor_int == BARALHO_C)break;
          gira_baralho(minhas_cartas);
      }  
      //Procura a primeira carta compatível, se o coringa já estiver no topo, mantem-se
        for (int i = 0; i < tamanho_baralho(minhas_cartas); i++) {
          acessa_carta(minhas_cartas, 0, &carta_na_mao);
          comparacao = compara_carta(carta_na_mao, carta_que_esta_na_mesa);
          if (comparacao == COMPATIVEL || comparacao == IGUAL)break;
          gira_baralho(minhas_cartas);
        }

      //Se não achar nenhuna carta compatível para a jogada, compra uma
      if (comparacao == INCOMPATIVEL) {
        printf("BUY 1\n");
        scanf("%s", str);
        Carta compra1 = converte_string_para_carta(str);
        adiciona_carta_no_inicio(minhas_cartas, compra1);
        //Cadastra o evento da compra dessa carta no histórico
        strcpy(meu_evento.action,"BUY");
        strcpy(meu_evento.complemento,"1");
        strcpy(meu_evento.complemento2,"NULL");        
        
      }else{
        //Informa o gerenciador sobre o descarte da carta que foi escolhida
        printf("DISCARD %s", carta_na_mao.carta_str);
        //Pega os dados sobre esse evento
        strcpy(meu_evento.action,"DISCARD");
        strcpy(meu_evento.complemento,carta_na_mao.carta_str);
        //Caso a carta descartada exigir que seja informado um novo naipe para troca
        if(carta_na_mao.valor_int == BARALHO_AS || carta_na_mao.valor_int == BARALHO_C){
          strcpy(meu_evento.complemento,carta_na_mao.carta_str);
          int naipe_da_vez = naipe_preferido(minhas_cartas); //Escolhe o melhor naipe para a mudança (aquele que mais se repetir nas minhas_cartas)
          switch(naipe_da_vez){ //Informa ao gerenciador sobre o naipe escolhido para a troca
            case PAUS:
              printf(" ♣\n");
              strcpy(meu_evento.complemento2,"♣");
              break;
            case OURO:
              strcpy(meu_evento.complemento2,"♦");
              printf(" ♦\n");
              break;
            case COPAS:
              strcpy(meu_evento.complemento2,"♥");
              printf(" ♥\n");
              break;
            case ESPADAS:
              strcpy(meu_evento.complemento2,"♠");
              printf(" ♠\n");
              break;
          }
        }else{
          strcpy(meu_evento.complemento2,"NULL"); //Caso não tenha sido necessário informar um naipe para a troca
          printf("\n"); //tratamento de erro
        }

        descarta_carta(minhas_cartas, 0); //Remove a carta que foi descartada das minhas_cartas
        carta_que_esta_na_mesa.naipe_int = converte_string_para_naipe(meu_evento.complemento2); //tratamento de erro para não confundir o histórico
      }
    }
    adiciona_evento_no_inicio(historico,meu_evento); //Adiciona o evento de toda essa jogada no histórico
  }
  return 0; 
}
