#include "snake.h"
#include <syscalls.h>
#include <colors.h>
#include <stdlib.h>
#include <stdio.h>
#include <draw.h>
#include <random.h>

#define PIXEL 16


struct controller {
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;
} ;

struct snake_body {
    uint64_t x;
    uint64_t y;
    char dir;
};

struct snake {
    struct snake_body head;
    struct snake_body tail;
    uint64_t len;
    int collision_board[BOARD_SIZE][BOARD_SIZE];
};

struct food {
    uint64_t x;
    uint64_t y;
};

//static snake_t player;
struct player {
    char* name;
    snake_t snake;
    controller_t controller;
    uint8_t alive;
};

void snake(){
    game();
}

void game(){

    player_t player1 = init_player("felidown", (controller_t){'w','s','a','d'});
    draw_board();
    // food_t food = init_food(player1->snake.collision_board);
    // do{
    //     draw_player(player1);
    //     move_player(player1);
    //     // if (check_collision(food)){
    //     //     food = init_food();
    //     // }
    //     sleep(500);

    //   // temp  
    // } while (1);
}

player_t init_player(char* name, controller_t controller) {
    player_t player;
    player->name = "test";
    player->controller = controller;
    player->snake.len = 1;
    player->snake.head.x = 4;
    player->snake.head.y = BOARD_SIZE/2;
    player->snake.head.dir = 'd';
    player->alive = 1;
    // // setup board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            player->snake.collision_board[i][j] = 0;
        }
    }
    // player->snake.collision_board[player->snake.head.x][player->snake.head.y] = 1;
    return player;
}

void draw_board() {
    // top margin
    draw_line(COLOR_WHITE, 0, PIXEL+8, BOARD_SIZE*PIXEL, PIXEL+8);
    // bottom margin
    draw_line(COLOR_WHITE, 0, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL);
    draw_line(COLOR_WHITE, 0, 0, 0, BOARD_SIZE*PIXEL);
    draw_line(COLOR_WHITE, BOARD_SIZE*PIXEL, 0, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL);
}

void draw_player(player_t player){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (player->snake.collision_board[i][j] > 0) {
                draw_pixel(COLOR_RED, PIXEL, i*PIXEL, j*PIXEL);
            }
            // temp
            else {
                draw_pixel(COLOR_BLACK,PIXEL, i*PIXEL, j*PIXEL);
            }
        }
    }
    
    
}

void move_player(player_t player) {
    char c = getchar();
    // if (c == 0) {
    //     c = player.head.dir;
    // }    
    snake_t snake = player->snake;
    if (c == player->controller.up) {
        snake.head.dir = player->controller.up;
        snake.collision_board[snake.head.x][snake.head.y] = 0;
        snake.head.y--;
    }
    else if (c == player->controller.right) {
        snake.head.dir = player->controller.right;
        snake.collision_board[snake.head.x][snake.head.y] = 0;
        snake.head.x++;

    }
    else if (c == player->controller.down) {
        snake.head.dir = player->controller.down;
        snake.collision_board[snake.head.x][snake.head.y] = 0;
        snake.head.y++;
    }
    else if (c == player->controller.left) {
        snake.head.dir = player->controller.left;
        snake.collision_board[snake.head.x][snake.head.y] = 0;
        snake.head.x--;
    }

    // check collision
    if (snake.head.x < 0 || snake.head.x >= BOARD_SIZE || snake.head.y < 0 || snake.head.y >= BOARD_SIZE) {
        // player->alive = 0;
    }
    else if (snake.collision_board[snake.head.x][snake.head.y] > 0) {
     //player.alive = 0;
    }
    else {
        snake.collision_board[snake.head.x][snake.head.y] = 1;
    }

}

food_t init_food(int16_t collision_board[BOARD_SIZE][BOARD_SIZE]) {
    food_t fruit;
      do {
        fruit.x = rand(BOARD_SIZE);
        fruit.y = rand(BOARD_SIZE);
    } while (collision_board[fruit.x][fruit.y] > 0);
    return fruit;
}