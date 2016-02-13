#include <stdlib.h>
#include <ncurses.h>
#include "food.h"

#define FOOD_CHAR ('$')

struct _food {
	int row;
	int col;
};

Food *
food_new(void)
{
	Food *food;
	food = malloc(sizeof(Food));
	if (food == NULL) {
		fprintf(stderr, "malloc in %s failed\n", __func__);
		exit(EXIT_FAILURE);
	}

	food_renew(food);

	return food;
}

void
food_renew(Food *food)
{
	food->row = 1 + rand() % (map.row - 2);
	food->col = 1 + rand() % (map.col - 2);

	mvwprintw(gameinfo.map, food->row, food->col, "%c", FOOD_CHAR);
}

int
food_get_row(const Food *f)
{
	return f->row;
}

int
food_get_col(const Food *f)
{
	return f->col;
}
