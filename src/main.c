#include <ncurses.h>
#include "snake.h"
#include "game.h"
#include "food.h"
#include "gaming.h"

int main()
{
	/* ncurses init */
	initscr();
	noecho();
	cbreak();
	keypad(gameinfo.map, 1);

	/* game init */
	game_info_init(&gameinfo);
	game_win_info_fill(gameinfo.map, &map);
	game_win_info_fill(gameinfo.stat, &stat);
	game_win_info_fill(gameinfo.gameover, &gameover);
	wtimeout(gameinfo.map, 300);

	gaming_main();

	endwin();

	return 0;
}
