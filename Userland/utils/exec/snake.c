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


#define DRAW_START_X 10 * PIXEL
#define DRAW_START_Y 5 * PIXEL

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

// 0 negro , 1 pyr1, 2 pyr2, -1 fruit 

void snake(){
    game();
}

void game(){

    // initialize collision board 
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            collision_board[i][j] = 0; 
        }
    }

    player_t player1;
    init_player(player1 ,"felidown", COLOR_RED, (controller_t){'w','s','a','d'});
    draw_board(COLOR_WHITE, BOARD_SIZE * PIXEL, DRAW_START_X, DRAW_START_Y);
    food();

    do {
        // if (move_player(player..) || spawn_fruit()) {
        //     draw();
        // }

        check_collision(player1);
        draw_game(player1);
        move_player(player1);
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
    

    collision_board[player->snake.head.x][player->snake.head.y] = player->uid;
}

void draw_board(color_t color, uint16_t size, uint64_t x, uint64_t y) {
    draw_rectangle(color, size + PIXEL, x - PIXEL, y - PIXEL);
    // top margin
    // int board = BOARD_SIZE * PIXEL + DRAW_START;
    // draw_line(COLOR_WHITE, DRAW_START, DRAW_START, board, DRAW_START);
    // // bottom margin
    // draw_line(COLOR_WHITE, DRAW_START, board, board, board);
    // draw_line(COLOR_WHITE, DRAW_START, DRAW_START, DRAW_START, board);
    // draw_line(COLOR_WHITE, board, DRAW_START, board, board);
}

void draw_game(player_t player){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            switch (collision_board[i][j]) {
                // fruit
                case FRUIT: 
                    draw_pixel(COLOR_MAGENTA, PIXEL/2, DRAW_START_X + i*PIXEL, DRAW_START_Y + j * PIXEL);
                    break;
                // nothing
                case 0: 
                    draw_pixel(COLOR_BLACK, PIXEL, DRAW_START_X + i * PIXEL, DRAW_START_Y + j * PIXEL);
                    break;
                // player
                default:
                   draw_pixel(player->color, PIXEL, DRAW_START_X + i * PIXEL, DRAW_START_Y + j * PIXEL);
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

    // @TODO: Make switch statement
    int uid = player->uid;

    // else {
    //     collision_board[player->snake.head.x][player->snake.head.y] = uid;
    // }

    collision_board[player->snake.head.x][player->snake.head.y] = uid;
    if (c == player->controller.up) {
        //collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.y--;
        player->snake.head.dir = player->controller.up;
    }
    else if (c == player->controller.right) {
        //collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.x++;
        player->snake.head.dir = player->controller.right;
    }
    else if (c == player->controller.down) {
        //collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.y++;
        player->snake.head.dir = player->controller.down;
    }
    else if (c == player->controller.left) {
        //collision_board[player->snake.head.x][player->snake.head.y] = 0;
        player->snake.head.x--;
        player->snake.head.dir = player->controller.left;
    }
    

}

void food() {

    int x, y;
    do {
        x = rand(21304, BOARD_SIZE);
        y = rand(21304, BOARD_SIZE);
    } while (collision_board[x][y] != 0);

    collision_board[x][y] = FRUIT;
}

void check_collision(player_t player){
    
      if (collision_board[player->snake.head.x][player->snake.head.y] == FRUIT) {
        printf("comio");
        player->snake.len++;
        // collision_board[player->snake.head.x][player->snake.head.y] = uid;
        food();
    }

    // check collision
    if (player->snake.head.x < 0 || player->snake.head.x >= BOARD_SIZE || player->snake.head.y < 0 || player->snake.head.y >= BOARD_SIZE) {
        player->alive = 0;
    }
    else if (collision_board[player->snake.head.x][player->snake.head.y] > 0) {
        //player.alive = 0;
    }
}