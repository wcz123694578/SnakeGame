#ifndef _GLOBAL_H
#define _GLOBAL_H

typedef enum game_state_t {
    Title,
    Start,
    Over,
    Exit
} GameState;

extern int score;
extern GameState state;

#endif	// _GLOBAL_H