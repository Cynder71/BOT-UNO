all:
	gcc -c ./src/baralho.c -I ./include/ -o ./obj/baralho.o
	gcc -c ./src/lista_de_eventos.c -I ./include/ -o ./obj/lista_e_eventos.o
	gcc -c ./src/utilidades.c -I ./include/ -o ./obj/utilidades.o
	gcc ./apps/main.c ./obj/*.o -I ./include -o ./bin/meu_bot
	cp ./bin/meu_bot ./game/meu_bot

antigo_bot:
	gcc -c ./src/baralho.c -I ./include/ -o ./obj/baralho.o
	gcc -c ./src/lista_de_eventos.c -I ./include/ -o ./obj/lista_e_eventos.o
	gcc -c ./src/utilidades.c -I ./include/ -o ./obj/utilidades.o
	gcc ./apps/main.c ./obj/*.o -I ./include -o ./bin/meu_antigo_bot

run:
	./game/uno ./bin/meu_bot ./game/bot_A

run_antigo_bot:
	./game/uno ./bin/meu_bot ./game/meu_antigo_bot
clean:
	rm ./bin/* ./obj/*
