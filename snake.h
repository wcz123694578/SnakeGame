#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdbool.h>

typedef enum spin_t {
	Left,
	Up,
	Right,
	Down
} SpinType;

struct _snake_node_t {
	struct _snake_node_t *prev, *next;
	int x, y;
	SpinType spin_direction;
	bool is_spin;
};
typedef struct _snake_node_t snake_t;

extern snake_t *snake;
extern snake_t *head;
extern snake_t *tail;

void init_snake(snake_t **snake_ptr);
void snake_push();
void snake_go_foward();

#endif // _SNAKE_H
