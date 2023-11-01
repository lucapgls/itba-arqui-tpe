#include "snake.h"
#include <syscalls.h>
#include <colors.h>
#include <stdlib.h>
#include <stdio.h>
#include <draw.h>
#include <random.h>

#define BOARD_SIZE 16
#define PIXEL 16


struct snake_head {
    uint64_t x;
    uint64_t y;
    uint8_t dir;
};


typedef struct {
    struct snake_head head;
    uint64_t len;
    uint8_t collision_board[BOARD_SIZE][BOARD_SIZE];
    uint8_t alive;
} snake_t;

typedef struct food{
    uint64_t x;
    uint64_t y;
} food_t;

static snake_t player;

void snake(){
    game();
}

void game(){
    init_player();
    draw_board();
    // food_t food = init_food();
    while(player.alive){
        draw_player();
        // draw_food(food);
        move_player();
        // if (check_collision(food)){
        //     food = init_food();
        // }
        // sleep(100);
    }    
}

void init_player() {
    player.len = 1;
    player.head.x = BOARD_SIZE/2;
    player.head.y = BOARD_SIZE/2;
    player.head.dir = 0;
    player.alive = 1;
    // setup board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            player.collision_board[i][j] = 0;
        }
    }
    player.collision_board[player.head.x][player.head.y] = 1;
}

void draw_board() {
    // top margin
    draw_line(COLOR_WHITE, 0, PIXEL+8, BOARD_SIZE*PIXEL, PIXEL+8);
    // bottom margin
    draw_line(COLOR_WHITE, 0, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL);
    draw_line(COLOR_WHITE, 0, 0, 0, BOARD_SIZE*PIXEL);
    draw_line(COLOR_WHITE, BOARD_SIZE*PIXEL, 0, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL);
}

void draw_player(){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (player.collision_board[i][j] == 1){
                draw_pixel(COLOR_RED, PIXEL, i*PIXEL, j*PIXEL);
            }
        }
    }
}

void move_player() {
    char c = getchar();
    if (c == 'w') {
        player.head.dir = 0;
        player.collision_board[player.head.x][player.head.y] = 0;
        player.head.y--;
    }
    else if (c == 'd') {
        player.head.dir = 1;
        player.collision_board[player.head.x][player.head.y] = 0;
        player.head.x++;

    }
    else if (c == 's') {
        player.head.dir = 2;
        player.collision_board[player.head.x][player.head.y] = 0;
        player.head.y++;
    }
    else if (c == 'a') {
        player.head.dir = 3;
        player.collision_board[player.head.x][player.head.y] = 0;
        player.head.x--;
    }
    // check collision
    if (player.head.x < 0 || player.head.x >= BOARD_SIZE || player.head.y < 0 || player.head.y >= BOARD_SIZE) {
        player.alive = 0;
    }
    else if (player.collision_board[player.head.x][player.head.y] == 1) {
        // player.alive = 0;
    }
    else {
        player.collision_board[player.head.x][player.head.y] = 1;
    }
}