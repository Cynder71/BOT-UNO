# UNO BOT
Por: Eduarda Chiesa e Danillo da Fonseca
## Introdução

UNO BOT é um projeto de conclusão da matéria de Introdução a Técnicas de Programação (ITP) cujo o objetivo é desenvolver um BOT capaz de jogar, do início ao fim, uma partida do jogo cartas UNO. [detalhes sobre o jogo](https://pt.wikihow.com/Jogar-UNO)

## Requisitos
Para conseguir rodar uma partida é necessário executar o código em um ambiente línux

## Dos diretórios
No reposotório encontram-se os seguintes diretórios: 
* /apps      : Possui o código fonte do bot;
* /include   : Protótipos dos TADS utilizados para fazer o código;
* /src       : Implementação dos TADS utilizados;
* /obj       : Arquivos .o;
* /bin       : Arquivos binários finalizados (quando um bot é gerado com o comando make no terminal ele aparece aqui com o nome "meu_bot");
* /game      : Executáveis para necessários para rodar uma partida disponibilizados pelo professor. (possui uma cópia do bot presente em \bin)
* /bkps      : Possui cópias dos arquivos de /game

## Dos bibliotecas e TADS
* baralho.h : lista dinâmica duplamente encadeada responsável por gerenciar as cartas do baralho;
* lista_de_eventos : lista dinâmica duplamente encadeada responável por guardar as jogadas de cada jogador e gerenciar as próprias jogadas;
* utilidades.h :  biblioteca com funções gerais de manipulações de strings e conversão de string para o tipo carta definido em Baralho.h;

## Da lógica do meu BOT
O bot gerado tem um funcionamento simples. Ele foca em destruir os adversários enchendo-os de cartas ao procurar, sempre que possível, jogar cartas +4, caso contrário ele jogará a primeira carta compatível que houver. Se não houver cartas disponíveis o bot puxa uma carta. Ao jogar uma carta que muda de cor ("+4" ou "muda de cor") o bot calcula qual é a cor mais conveniente e a escolhe.

## Como gerar um bot e iniciar uma ~batalha mortal~ partida de UNO
**Passo 1** Faça o download do repositorio com o comando:
```bash
git clone https://github.com/gabriel26077/UNO
```
**Passo 2** A partir do diretório principal do repositorio "\UNO" gere um bot com o comando abaixo:
```bash
gcc ./apps/main.c ./src/baralho.c ./src/lista_de_eventos.c ./src/utilidades.c -o nome_do_seu_bot
```
**Passo 3** Inicie a ~batalha mortal~ partida com o comando abaixo:
```bash
./game/uno ./game/Bot_A ./bin/nome_do_seu_bot
```
Também é possível iniciar uma partida rápida através do Makefile
**Passo 1** A partir do diretório princiál do repositório "\UNO" gere um bot de nome genérico "meu_bot" com o comando abaixo:
```bash
make
```
**Passo 2** Inicie a ~batalha mortal~ partida entre o "Bot_A" e o "meu_bot" com o comando abaixo;
```bash
make run
```
