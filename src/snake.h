#ifndef _SNAKE_H
#define _SNAKE_H

#include <ncurses.h>
#include "food.h"
#include "game.h"

#define SNAKE_DEFAULT_LENGTH (4)
#define SNAKE_TAIL_DEFAULT_Y (5)
#define SNAKE_TAIL_DEFAULT_X (20)

#define SNAKE_BODY_CHAR ('*')
#define SNAKE_HEAD_CHAR ('@')

typedef struct _snake_node SnakeNode;
struct _snake_node {
	int row;
	int col;
	struct _snake_node *prev;
	struct _snake_node *next;
};

typedef struct _snake Snake;
struct _snake {
	SnakeNode *head;
	SnakeNode *tail;

	int length;
};

enum SnakeDir {
	UP, DOWN, LEFT, RIGHT
};

SnakeNode *snake_node_new(int row, int col);
Snake *snake_new(void);
void snake_free(Snake *snake);
void snake_node_free(SnakeNode *snakenode);

void snake_append_head(Snake *snake, SnakeNode *node);

void snake_move(Snake *snake, enum SnakeDir direction);

void snake_eat_food(Snake *snake, Food *food);

#endif /* _SNAKE_H */
