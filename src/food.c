#include <stdlib.h>
#include <ncurses.h>
#include "food.h"

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

	food->row = 0;
	food->col = 0;

	return food;
}

void
food_renew(Food *food)
{
	food->row = rand() % map.row;
	food->col = rand() % map.col;
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
