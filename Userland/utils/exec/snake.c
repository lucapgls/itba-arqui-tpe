#include "snake.h"
#include <syscalls.h>
#include <colors.h>
#include <stdlib.h>
#include <stdio.h>
#include <draw.h>
#include <random.h>

#define PIXEL 16
#define BOARD_SIZE 32


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
    // int collision_board[BOARD_SIZE][BOARD_SIZE];
};

struct food {
    uint64_t x;
    uint64_t y;
};

//static snake_t player;
struct player {
    int uid;
    char* name;
    color_t color;
    snake_t snake;
    controller_t controller;
    uint8_t alive;
};

static int collision_board[BOARD_SIZE][BOARD_SIZE];
static int player_count = 0;

// 0 negro , 1 pyr1, 2 pyr2 

void snake(){
    game();
}

void game(){

    player_t player1;
    init_player(player1 ,"felidown", COLOR_RED, (controller_t){'w','s','a','d'});
    draw_board();
    //food_t food = init_food(collision_board);
    do {
        // if (move_player(player..) || spawn_fruit()) {
        //     draw();
        // }

        draw_player(player1);
        move_player(player1);
        // if (check_collision(food)){
        //     food = init_food();
        // }
        sleep(200);

      // temp  
    } while (player1->alive);
}

void init_player(player_t player, char* name, color_t color, controller_t controller) {
    player->name = "test";
    player->color = color;
    player->controller = controller;
    player->snake.len = 1;
    player->snake.head.x = 4;
    player->snake.head.y = BOARD_SIZE / 2;
    player->snake.head.dir = controller.right;
    player->alive = 1;
    player->uid = ++player_count;
    
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            collision_board[i][j] = 0;
           
        }
    }
    collision_board[player->snake.head.x][player->snake.head.y] = player->uid;
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
            // make switch, change name to "draw_logic"
            if (collision_board[i][j] > 0) {
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
    if (c == 0) {
        c = player->snake.head.dir;
    }    

    int uid = player->uid;
    if (c == player->controller.up) {
        player->snake.head.y--;
        player->snake.head.dir = player->controller.up;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }
    else if (c == player->controller.right) {
        player->snake.head.x++;
        player->snake.head.dir = player->controller.right;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }
    else if (c == player->controller.down) {
        player->snake.head.y++;
        player->snake.head.dir = player->controller.down;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }
    else if (c == player->controller.left) {
        player->snake.head.x--;
        player->snake.head.dir = player->controller.left;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }

    // check collision
    if (player->snake.head.x < 0 || player->snake.head.x >= BOARD_SIZE || player->snake.head.y < 0 || player->snake.head.y >= BOARD_SIZE) {
        player->alive = 0;
    }
    else if (collision_board[player->snake.head.x][player->snake.head.y] > 0) {
        //player.alive = 0;
    }
    // else {
    //     collision_board[player->snake.head.x][player->snake.head.y] = uid;
    // }

}

food_t init_food(int16_t collision_board[BOARD_SIZE][BOARD_SIZE]) {
    food_t fruit;
      do {
        fruit.x = rand(BOARD_SIZE);
        fruit.y = rand(BOARD_SIZE);
    } while (collision_board[fruit.x][fruit.y] > 0);
    return fruit;
}