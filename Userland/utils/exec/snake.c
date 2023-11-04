#include "snake.h"
#include <syscalls.h>
#include <colors.h>
#include <stdlib.h>
#include <stdio.h>
#include <draw.h>
#include <random.h>

#define PIXEL 16
#define BOARD_SIZE 32
#define FRUIT -1


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
static uint8_t player_count = 0;

// 0 negro , 1 pyr1, 2 pyr2 

void snake(){
    game();
}

void game(){

    player_t player1;
    init_player(player1 ,"felidown", COLOR_RED, (controller_t){'w','s','a','d'});
    draw_board();
    food();
    //food_t food = init_food(collision_board);
    do {
        // if (move_player(player..) || spawn_fruit()) {
        //     draw();
        // }

        draw_game(player1);
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


void draw_game(player_t player){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            switch(collision_board[i][j]) {
                // fruit
                case FRUIT: 
                    draw_pixel(COLOR_MAGENTA, PIXEL/2, i*PIXEL, j * PIXEL);
                    break;
                // nothing
                case 0: 
                    draw_pixel(COLOR_BLACK, PIXEL, i*PIXEL, j*PIXEL);
                    break;
                // player
                default:
                    draw_pixel(player->color, PIXEL, i*PIXEL, j*PIXEL);
                    break;
            }
           
        }
    }
    
    
}

void move_player(player_t player) {
    char c = getchar();
    if (c == 0) {
        c = player->snake.head.dir;
    }    

    // temp 
    if (collision_board[player->snake.head.x][player->snake.head.y] == FRUIT) {
        printf("comio");
        food();
    }

    // @TODO: Make switch statement
    int uid = player->uid;
    if (c == player->controller.up) {
        collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.y--;
        player->snake.head.dir = player->controller.up;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }
    else if (c == player->controller.right) {
        collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.x++;
        player->snake.head.dir = player->controller.right;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }
    else if (c == player->controller.down) {
        collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.y++;
        player->snake.head.dir = player->controller.down;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }
    else if (c == player->controller.left) {
        collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.x--;
        player->snake.head.dir = player->controller.left;
        collision_board[player->snake.head.x][player->snake.head.y] = uid;
    }

    // check collision
    if (player->snake.head.x < 0 || player->snake.head.x >= BOARD_SIZE || player->snake.head.y < 0 || player->snake.head.y >= BOARD_SIZE) {
        player->alive = 0;
    }
    // if (player->)
    else if (collision_board[player->snake.head.x][player->snake.head.y] > 0) {
        //player.alive = 0;
    }
    // else {
    //     collision_board[player->snake.head.x][player->snake.head.y] = uid;
    // }

}

void food() {

    int x, y;
    do {
        x = rand(21304, BOARD_SIZE);
        y = rand(21304, BOARD_SIZE);
    } while (collision_board[x][y] != 0 && x > 0 && x < BOARD_SIZE && y > 0 && y < BOARD_SIZE);

    collision_board[x][y] = FRUIT;
}