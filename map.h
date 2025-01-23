#ifndef _MAP_H
#define _MAP_H

#include <stdbool.h>

struct _map_node_t {
	int x;
	int y;
	bool is_coin;
};
typedef struct _map_node_t map_t;

extern map_t map[20][20];

void init_map();
void draw_map();
void refresh_coin(int cur_x, int cur_y);

#endif // _MAP_H
