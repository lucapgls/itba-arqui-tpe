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
    char dir;
};

typedef struct {
    struct snake_head head;
    uint64_t len;
    uint8_t collision_board[BOARD_SIZE][BOARD_SIZE];
    uint8_t alive;
} snake_t;

typedef struct food {
    uint64_t x;
    uint64_t y;
} food_t;

//static snake_t player;

void snake(){
    game();
}

void game(){

    snake_t player;
    init_player(&player);
    draw_board(&player);
    //food_t food = init_food();
    do{
        draw_player(&player);
        spawn_fruit();
        move_player(&player);
        // if (check_collision(food)){
        //     food = init_food();
        // }
        sleep(500);
       
    } while(player.alive == 1);   
}

void init_player(snake_t *player) {
    player->len = 1;
    player->head.x = 4;
    player->head.y = BOARD_SIZE/2;
    player->head.dir = 'd';
    player->alive = 1;
    // setup board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            player->collision_board[i][j] = 0;
        }
    }
    player->collision_board[player->head.x][player->head.y] = 1;
    return;
}

void draw_board(snake_t *player) {
    // top margin
    draw_line(COLOR_WHITE, 0, PIXEL+8, BOARD_SIZE*PIXEL, PIXEL+8);
    // bottom margin
    draw_line(COLOR_WHITE, 0, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL);
    draw_line(COLOR_WHITE, 0, 0, 0, BOARD_SIZE*PIXEL);
    draw_line(COLOR_WHITE, BOARD_SIZE*PIXEL, 0, BOARD_SIZE*PIXEL, BOARD_SIZE*PIXEL);
}

void draw_player(snake_t *player){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if (player->collision_board[i][j] == 1){
                draw_pixel(COLOR_RED, PIXEL, i*PIXEL, j*PIXEL);
            }
            else{
                draw_pixel(COLOR_BLACK,PIXEL, i*PIXEL, j*PIXEL);
            }
        }
    }
    
    
}

void move_player(snake_t *player) {
    char c = getchar();

    // if (c == 0) {
    //     c = player.head.dir;
    // }    

    if (c == 'w') {
        player->head.dir = 'w';
        player->collision_board[player->head.x][player->head.y] = 0;
        player->head.y--;
    }
    else if (c == 'd') {
        player->head.dir = 'd';
        player->collision_board[player->head.x][player->head.y] = 0;
        player->head.x++;

    }
    else if (c == 's') {
        player->head.dir = 's';
        player->collision_board[player->head.x][player->head.y] = 0;
        player->head.y++;
    }
    else if (c == 'a') {
        player->head.dir = 'a';
        player->collision_board[player->head.x][player->head.y] = 0;
        player->head.x--;
    }

    
    

    // check collision
    if (player->head.x < 0 || player->head.x >= BOARD_SIZE || player->head.y < 0 || player->head.y >= BOARD_SIZE) {
        player->alive = 0;
    }
    else if (player->collision_board[player->head.x][player->head.y] == 1) {
     //player.alive = 0;
    }
    else {
        player->collision_board[player->head.x][player->head.y] = 1;
    }

}


void spawn_fruit(){
    uint32_t spawn_point_x = random(16);
    uint32_t spawn_point_y = random(16);

    draw_pixel(COLOR_GREEN, PIXEL, spawn_point_x * PIXEL, spawn_point_y * PIXEL);
   //player.collision_board[spawn_point_x][spawn_point_y] = 2;
}
