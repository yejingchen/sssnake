#include <ncurses.h>
#include <string.h>
#include "game.h"

void
game_info_init(GameInfo *gameinfo)
{
	gameinfo->map = newwin(LINES - 1, COLS, 1, 0);

	gameinfo->stat = newwin(1, COLS, 0, 1);

	gameinfo->gameover = newwin(10, 40, (LINES - 10) / 2, (COLS - 40) / 2);
}

void
game_stat_reset(GameStat *stat)
{
	stat->score = 0;
	stat->highscore = 0;
}

void
game_stat_print_score(void)
{
	wmove(gameinfo.stat, 0, stat.col * STAT_SCORE_COL_PERCENTAGE);
	wprintw(gameinfo.stat, "                  ");
	wprintw(gameinfo.stat, "Score: %lu", gamestat.score);
	wmove(gameinfo.stat, 0, 0);
}

void
game_stat_print_highscore(void)
{
	wmove(gameinfo.stat, 0, stat.col * STAT_HIGH_COL_PERCENTAGE);
	wprintw(gameinfo.stat, "                  ");
	wprintw(gameinfo.stat, "Highscore: %lu", gamestat.highscore);
	wmove(gameinfo.stat, 0, 0);
}

void
game_stat_update(void)
{
	gamestat.highscore = gamestat.highscore > gamestat.score ?
		gamestat.highscore : gamestat.score;

	game_stat_print_score();
	game_stat_print_highscore();
}

void
game_win_info_fill(WINDOW *win, struct _win_info *scr)
{
	getmaxyx(win, scr->row, scr->col);
}

void
game_over_screen(void)
{
	werase(gameinfo.gameover);

	const char *overstr = "Game Over!";
	int overstrlen = strlen(overstr);
	mvwprintw(gameinfo.gameover, 2, (gameover.col - overstrlen) / 2,
			"%s", overstr);

	mvwprintw(gameinfo.gameover, 3, (gameover.col - overstrlen) / 2,
			"Score: %lu", gamestat.score);
	mvwprintw(gameinfo.gameover, 4, (gameover.col - overstrlen) / 2,
			"Highscore: %lu", gamestat.highscore);

	const char *opstr1 = "Press <Enter> to play again,";
	const char *opstr2 = "or q to quit";
	int opstr1len = strlen(opstr1);
	int opstr2len = strlen(opstr2);
	mvwprintw(gameinfo.gameover, 6, (gameover.col - opstr1len) / 2,
			"%s", opstr1);
	mvwprintw(gameinfo.gameover, 7, (gameover.col - opstr2len) / 2,
			"%s", opstr2);

	wborder(gameinfo.gameover, '#', '#', '#', '#',
			'#', '#', '#', '#');

	wrefresh(gameinfo.gameover);
}
