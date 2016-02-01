CC=clang

default: sssnake

sssnake: src/main.c src/snake.c src/food.c src/game.c src/gaming.c
	${CC} $+ -o $@ -lncurses -Wall

clear: sssnake
	rm src/sssnake

.PHONY: clear
