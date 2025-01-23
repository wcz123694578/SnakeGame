#include <stdio.h>
#include <stdbool.h>
#include "snake.h"
#include "map.h"
#include "control.h"

int main() {
	init_snake(&snake);
	init_map();
	map[3][6].is_coin = true;
	snake_push();
	snake_push();
	control_entry();

	getchar();
	return 0;
}
