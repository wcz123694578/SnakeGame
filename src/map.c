#include "map.h"
#include "snake.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET "\033[0m"
#define SNAKE_HEAD "\033[42m"
#define SNAKE_BODY "\033[44m"
#define BG_GRAY "\033[100m"
#define BG_BROWN "\033[43m"
#define BG_BORDER "\033[45m"

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

static void gotoxy(int x, int y) {
	printf("\033[%d;%dH", x, y);
}

void draw_map() {
	for (int i = 0; i < 22; i++) {
		gotoxy(1, i * 2 + 1);
		printf(BG_BORDER "  " RESET);
	}
	printf("\n");

	// 循环输出
	for (int i = 0; i < 20; i++) {
		gotoxy(i + 2, 1);
		printf(BG_BORDER "  " RESET);
		for (int j = 0; j < 20; j++) {
			snake = tail;
			gotoxy(i + 2, (j + 1) * 2 + 1);
			if (map[i][j].is_coin) {
				printf(BG_BROWN "  " RESET);
			} else {
				printf(BG_GRAY "  " RESET);
			}

			while (snake) {
				if (snake->x == j && snake->y == i) {
					gotoxy(i + 2, (j + 1) * 2 + 1);
					if (snake == head)
						printf(SNAKE_HEAD "  " RESET);
					else
						printf(SNAKE_BODY "  " RESET);
					break;
				}
				snake = snake->next;
			}
		}
		gotoxy(i + 2, 21 * 2 + 1);
		printf(BG_BORDER "  " RESET);
	}

	for (int i = 0; i < 22; i++) {
		gotoxy(22, i * 2 + 1);
		printf(BG_BORDER "  " RESET);
	}

	gotoxy(3, 27 * 2 + 1);

	printf("GAME PANEL");
	gotoxy(4, 27 * 2 + 1);
	printf("Score: %d", score);

	printf("\n");
}
