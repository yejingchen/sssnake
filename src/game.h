#ifndef _GAME_H
#define _GAME_H

#define STAT_SCORE_COL_PERCENTAGE 0.1
#define STAT_HIGH_COL_PERCENTAGE 0.5

typedef struct _game_info GameInfo;
struct _game_info {
	WINDOW *map;
	WINDOW *stat;
	WINDOW *gameover;
};

typedef struct _game_stat GameStat;
struct _game_stat {
	unsigned long score;
	unsigned long highscore;
};

struct _win_info {
	int col;
	int row;
} map, stat, gameover;

GameInfo gameinfo;
GameStat gamestat;

void game_info_init(GameInfo *gameinfo);
void game_stat_reset(GameStat *gamestat);
void game_stat_print_score(void);
void game_stat_print_highscore(void);
void game_stat_update(void);

void game_win_info_fill(WINDOW *win, struct _win_info *scr);

void game_over_screen(void);

#endif /* _GAME_H */
