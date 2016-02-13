#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"

SnakeNode *
snalloc(int n)
{
	return (SnakeNode *) malloc(n * sizeof(SnakeNode));
}

SnakeNode *
snake_node_new(int row, int col)
{
	SnakeNode *ret;

	ret = snalloc(1);
	if (ret == NULL) {
		fprintf(stderr, "snalloc in %s failed\n", __func__);
		exit(EXIT_FAILURE);
	}

	ret->row = row;
	ret->col = col;
	ret->prev = NULL;
	ret->next = NULL;

	return ret;
}

Snake *
snake_new(void)
{
	Snake *ret_snake;
	SnakeNode *node;

	ret_snake = malloc(sizeof(Snake));
	if (ret_snake == NULL) {
		fprintf(stderr, "malloc in %s failed", __func__);
		exit(EXIT_FAILURE);
	}

	ret_snake->head = NULL;
	ret_snake->tail = NULL;
	ret_snake->length = 0;

	for (int i = 0; i < SNAKE_DEFAULT_LENGTH; i++) {
		node = snake_node_new(SNAKE_TAIL_DEFAULT_Y + i,
				SNAKE_TAIL_DEFAULT_X + i);
		snake_append_head(ret_snake, node);

		if (ret_snake->head == node)
			mvwprintw(gameinfo.map, node->row, node->col, "%c", SNAKE_HEAD_CHAR);
		else
			mvwprintw(gameinfo.map, node->row, node->col, "%c", SNAKE_BODY_CHAR);
	}

	return ret_snake;
}

void
snake_free(Snake *snake)
{
	SnakeNode *node, *next;

	node = snake->head;
	while (node) {
		mvwdelch(gameinfo.map, node->row, node->col);
		next = node->next;
		snake_node_free(node);
		node = next;
	}
}

void
snake_node_free(SnakeNode *node)
{
	free(node);
}

void
snake_append_head(Snake *snake, SnakeNode *node)
{
	/* before appending */
	node->next = snake->head;
	if (snake->length > 0) {
		snake->head->prev = node;
		mvwprintw(gameinfo.map, snake->head->row, snake->head->col, "%c",
			SNAKE_BODY_CHAR);
	}

	/* append */
	if (snake->length == 0)
		snake->tail = node;
	snake->head = node;

	/* after appending */
	snake->head->prev = NULL;
	snake->length += 1;
	mvwprintw(gameinfo.map, snake->head->row, snake->head->col, "%c",
			SNAKE_HEAD_CHAR);
}

void
snake_move(Snake *snake, enum SnakeDir dir)
{
	SnakeNode *node = snake->tail;
	/* mvwdelch(gameinfo.map, node->row, node->col); */
	/* Don't do what is on above because it cause characters on the right to 
	 * go left
	 */
	mvwprintw(gameinfo.map, node->row, node->col, " ");
	mvwprintw(gameinfo.map, snake->head->row, snake->head->col, "%c",
			SNAKE_BODY_CHAR);

	snake->tail = snake->tail->prev;
	snake->tail->next = NULL;
	
	switch (dir) {
		case UP:
			node->row = snake->head->row - 1;
			node->col = snake->head->col;
			break;
		case DOWN:
			node->row = snake->head->row + 1;
			node->col = snake->head->col;
			break;
		case LEFT:
			node->row = snake->head->row;
			node->col = snake->head->col - 1;
			break;
		case RIGHT:
			node->row = snake->head->row;
			node->col = snake->head->col + 1;
			break;
	}

	snake->head->prev = node;

	node->next = snake->head;
	node->prev = NULL;
	snake->head = node;
	mvwprintw(gameinfo.map, snake->head->row, snake->head->col, "%c",
			SNAKE_HEAD_CHAR);
}

void
snake_eat_food(Snake *snake, Food *food)
{
	SnakeNode *node;
	node = snake_node_new(food_get_row(food), food_get_col(food));

	snake_append_head(snake, node);
	game_stat_update();
}
