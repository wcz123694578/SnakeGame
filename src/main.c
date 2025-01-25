#include <stdio.h>
#include <stdbool.h>
#include "snake.h"
#include "map.h"
#include "control.h"
#include "global.h"

int main() {
	init_snake(&snake);
	init_map();
	map[3][6].is_coin = true;
	snake_push();
	snake_push();
	while (state != Exit) {
		control_entry();
	}

	printf("============================\n");

	printf("GAME OVER!\n");

	getchar();
	return 0;
}
