#include <ncurses.h>
#include "snake.h"
#include "gaming.h"

static SnakeNode *
gaming_get_next_snake_node(Snake *snake, enum SnakeDir dir)
{
	SnakeNode *nextmove;
	nextmove = snake_node_new(snake->head->row, snake->head->col);

	switch (dir) {
		case UP:
			nextmove->row -= 1;
			break;
		case DOWN:
			nextmove->row += 1;
			break;
		case LEFT:
			nextmove->col -= 1;
			break;
		case RIGHT:
			nextmove->col += 1;
			break;
	}

	return nextmove;
}

void
gaming_main(void)
{
	int play_again = 1;
	int c; /* play_again input */

	game_stat_reset(&gamestat);
	while (play_again) {
		gamestat.score = 0;
		game_stat_print_score();
		game_stat_print_highscore();

		gaming();
		game_over_screen();

		do {
			c = wgetch(gameinfo.map);
			switch (c) {
				case '\n':
					play_again = 1;
					break;
				case 'q':
					play_again = 0;
					break;
				default:
					play_again = -1;
			}
		} while (play_again == -1);
	}
}

void
gaming(void)
{
	Snake *snake;
	snake = snake_new();

	int c, game_continue = 1;

	SnakeNode *next_move; /* free after use */
	enum SnakeDir dir = RIGHT;

	Food *food = food_new();

	while (game_continue) {
		c = wgetch(gameinfo.map);
		switch (c) {
			case 'w':
				dir = UP;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
		}

		next_move = gaming_get_next_snake_node(snake, dir);

		if (next_move->row == food_get_row(food) &&
				next_move->col == food_get_col(food)) { /* next is food */
			snake_eat_food(snake, food);
			food_renew(food);

			goto frame_end;
		}

		if (next_move->row == 0 /* next hit frame */
				|| next_move->row == map.row - 1
				|| next_move->col == 0
				|| next_move->col == map.col - 1) {
			game_continue = 0;
			goto frame_end;
		}

		for (SnakeNode *node = snake->head; /* check if next hit body */
				node != snake->tail;
				node = node->next)
			if (node->row == next_move->row &&
					node->col == next_move->col) {
				game_continue = 0;
				goto frame_end;
			}

		snake_move(snake, dir);

		frame_end:
		snake_node_free(next_move);
		wrefresh(gameinfo.map);
		wrefresh(gameinfo.stat);
	}

	snake_free(snake);
}
