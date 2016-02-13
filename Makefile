CC=clang

default: sssnake

sssnake: src/main.c src/snake.c src/food.c src/game.c src/gaming.c
	${CC} $+ -o $@ -lncurses -Wall

debug: src/main.c src/snake.c src/food.c src/game.c src/gaming.c
	${CC} $+ -o $@ -lncurses -Wall -g

clear: sssnake
	if [ -f sssnake ]; then rm sssnake; fi
	if [ -f debug ]; then rm debug; fi

.PHONY: clear
