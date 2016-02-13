#include <ncurses.h>
#include "game.h"

void
game_info_init(GameInfo *gameinfo)
{
	gameinfo->map = newwin(LINES - 1, COLS, 1, 0);
	wborder(gameinfo->map, '#', '#', '#', '#',
			'#', '#', '#', '#');
	gameinfo->stat = newwin(1, COLS, 0, 1);
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
