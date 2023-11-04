#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>

#define BOARD_SIZE 32

void snake();
void game();

typedef struct player * player_t;
typedef struct controller controller_t;
typedef struct snake_body snake_body_t;
typedef struct snake snake_t;
typedef struct food food_t;

player_t init_player(char* name, controller_t controller);
void draw_player(player_t player);
void move_player(player_t player);
void draw_board();
food_t init_food(int16_t collision_board[BOARD_SIZE][BOARD_SIZE]);
#endif
