#ifndef _FOOD_H
#define _FOOD_H

#include "game.h"
typedef struct _food Food;

Food *food_new(void);
void food_renew(Food *food);

int food_get_row(const Food *f);
int food_get_col(const Food *f);

#endif /* _FOOD_H */
