CC=clang

default: sssnake

sssnake: src/main.c src/snake.c src/food.c src/game.c src/gaming.c
	${CC} $+ -o $@ -lcurses -Wall

debug: src/main.c src/snake.c src/food.c src/game.c src/gaming.c
	${CC} $+ -o $@ -lcurses -Wall -g

clear:
	if [ -f sssnake ]; then rm sssnake; fi
	if [ -f debug ]; then rm debug; fi

.PHONY: clear
