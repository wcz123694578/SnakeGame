#include "map.h"
#include "snake.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

map_t map[20][20] = { 0 };

void init_map() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			map[i][j].x = j;
			map[i][j].y = i;
			map[i][j].is_coin = false;
		}
	}
}

void refresh_coin(int cur_x, int cur_y) {
	srand((unsigned)time(NULL));	
	int new_x = rand() % 20;
	int new_y = rand() % 20;
	map[cur_y][cur_x].is_coin = false;
	map[new_x][new_y].is_coin = true;
}

void draw_map() {
	printf("\033[2J");      // 清屏
    printf("\033[H");       // 将光标移动到左上角
									
	for (int i = 0; i < 22; i++) {
		printf("=");
	}
	printf("\n");

	// 循环输出
	for (int i = 0; i < 20; i++) {
		printf("|");
		for (int j = 0; j < 20; j++) {
			snake = tail;
			if (map[i][j].is_coin) {
				printf("o");
			} else {
				printf(" ");
			}

			while (snake) {
				if (snake->x == j && snake->y == i) {
					if (snake == head)
						printf("\b#");
					else
						printf("\b*");
					break;
				}
				snake = snake->next;
			}
		}
		printf("|\n");
	}

	for (int i = 0; i < 22; i++) {
		printf("=");
	}

	printf("\n\n");

	for (int i = 0; i < 40; i++) {
		printf("=");
	}

	printf("\n\nGAME PANEL\n");
	printf("Score: %d", score);

	printf("\n");
}
