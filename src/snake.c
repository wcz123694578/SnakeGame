#include "snake.h"
#include "map.h"
#include <malloc.h>

snake_t *snake;
snake_t *head;
snake_t *tail;

void init_snake(snake_t **snake_ptr) {
	snake_t *snake = *snake_ptr;

	snake = (snake_t *)malloc(sizeof(snake_t));
	snake->x = snake->y = 10;
	snake->spin_direction = Right;
	snake->next = snake->prev = NULL;


	head = snake;
	tail = snake;

	*snake_ptr = snake;
}

void snake_push() {
	snake_t *new = (snake_t *)malloc(sizeof(snake_t));
	new->spin_direction = tail->spin_direction;

	if (tail->spin_direction == Left) {
		new->x = tail->x + 1;
		new->y = tail->y;
	} else if (tail->spin_direction == Up) {
		new->x = tail->x;
		new->y = tail->y + 1;
	} else if (tail->spin_direction == Right) {
		new->x = tail->x - 1;
		new->y = tail->y;
	} else if (tail->spin_direction == Down) {
		new->x = tail->x;
		new->y = tail->y - 1;
	}


	new->next = tail;
	tail->prev = new;
	new->prev = NULL;
	tail = new;
}

void snake_go_foward() {

	snake = tail;

	while (snake) {
		if (snake->spin_direction == Left) {
			snake->x--;
		} else if (snake->spin_direction == Up) {
			snake->y--;
		} else if (snake->spin_direction == Right) {
			snake->x++;
		} else if (snake->spin_direction == Down) {
			snake->y++;
		}
		snake = snake->next;
	}

	snake = tail;

	while (snake->next) {
		snake->spin_direction = snake->next->spin_direction;
		snake = snake->next;
	}
}
