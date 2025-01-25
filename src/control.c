#include "snake.h"
#include "map.h"
#include "control.h"
#include "global.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

extern snake_t *snake;
extern snake_t *head;
extern snake_t *tail;

// 禁用终端缓冲和回显
void init_terminal() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &new_termios);
    new_termios.c_lflag &= ~(ICANON | ECHO);  // 禁用缓冲和回显
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// 恢复终端设置
void reset_terminal() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &new_termios);
    new_termios.c_lflag |= (ICANON | ECHO);  // 恢复缓冲和回显
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

static void snake_move(SpinType direction) {
	head->spin_direction = direction;
}

static char get_input() {
	char ch = 0;
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
        read(STDIN_FILENO, &ch, 1);
    }
    return ch;
}

static void move(SpinType *direction_ptr) {
	SpinType direction = *direction_ptr;


	char input = get_input();
	switch (input)
	{
	case 'w': case 'W':
		if (head->spin_direction != Down)
			direction = Up;
		break;
	case 'a': case 'A':
		if (head->spin_direction != Right)
			direction = Left;
		break;
	case 's': case 'S':
		if (head->spin_direction != Up)
			direction = Down;
		break;
	case 'd': case 'D':
		if (head->spin_direction != Left)
			direction = Right;
		break;
	default:
		break;
	}

	*direction_ptr = direction;
}

extern map_t map[20][20];

void control_entry() {
	SpinType direction = head->spin_direction;

	state = Start;

	while (true) {
		init_terminal();
		if (		head->x < 0 || head->x >= 20 
				||	head->y < 0 || head->y >= 20) {
			printf("You lose!\n");
			state = Over;
		} else {
			snake = tail;
			int flag = 0;
			while (snake && snake != head) {
				if (head->x == snake->x && head->y == snake->y) {
					flag = 1;
					break;
				}
				snake = snake->next;
			}
			if (flag) {
				printf("you lose!\n");
				state = Over;
			}
		}

		if (state == Over) {
			char op;

			// Delete snake
			snake = tail;
			while (snake) {
				snake_t *free_node = snake;
				snake = snake->next;
				free(free_node);
			}
			snake = NULL;

			init_snake(&snake);
			snake_push();
			snake_push();

			while (true) {
				reset_terminal();
				printf("Do you want to play again? [y/n]> ");
				fflush(stdout);
				op = fgetc(stdin);
				while (getchar() != '\n');
				
				if (op == 'y') {
					state = Start;
				} else if (op == 'n') {
					state = Exit;
				} else {
					continue;
				}
				return;
			}
		}

		move(&direction);

		if (map[head->y][head->x].is_coin) {
			score++;			
			snake_push();
			refresh_coin(head->x, head->y);
		}

		snake_move(direction);
		snake_go_foward();

		draw_map();

		usleep(200000);
		
		reset_terminal();
	}
}

