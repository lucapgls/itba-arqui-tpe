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
    uint8_t dir;
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
    draw_board(COLOR_WHITE, BOARD_SIZE * PIXEL, DRAW_START_X, DRAW_START_Y);

    // initialize player
    player_t player1;
    init_player(player1 ,"felidown", COLOR_RED, (controller_t){'w','s','a','d'});

    // spawn a starting fruit.
    food();

    do {

        draw_game(player1);
        move_player(player1);
        check_collision(player1);

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

    player->snake.tail = player->snake.head;

    player->alive = 1;
    player->uid = ++player_count;
    

    collision_board[player->snake.head.x][player->snake.head.y] = player->uid;
}

void draw_board(color_t color, uint16_t size, uint64_t x, uint64_t y) {
    draw_rectangle(color, size + PIXEL, x - PIXEL, y - PIXEL);
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

    
    // First, we set the last tail position to 0
    collision_board[player->snake.tail.x][player->snake.tail.y] = FRUIT;

    // Now we move the tail to the new position (based on the direction of the previous tail) and add a new tail
    uint8_t dir = player->snake.tail.dir;
    if (dir == player->controller.up) {
        player->snake.tail = (snake_body_t){player->snake.tail.x, player->snake.tail.y - 1, 
                                            player->snake.tail.dir};
    } else if (dir == player->controller.right) { 
        player->snake.tail = (snake_body_t){player->snake.tail.x + 1, player->snake.tail.y, 
                                            player->snake.tail.dir};
    } else if (dir == player->controller.down) {
        player->snake.tail = (snake_body_t){player->snake.tail.x, player->snake.tail.y + 1, 
                                            player->snake.tail.dir};
    } else if (dir == player->controller.left) {
        player->snake.tail = (snake_body_t){player->snake.tail.x - 1, player->snake.tail.y, 
                                            player->snake.tail.dir};
    }
    // collision_board[player->snake.tail.x][player->snake.tail.y] = player->uid;

    // Now we move the head to the new position (based on the direction of the previous head or the new input)
    dir = getchar();
    // If there is no input, we move the head in the same direction as the previous head
    if (dir == 0) {
        dir = player->snake.head.dir;
    } else {
        // Handle direction change and check for opposite direction
        if ((dir == player->controller.up && player->snake.head.dir != player->controller.down) ||
            (dir == player->controller.down && player->snake.head.dir != player->controller.up) ||
            (dir == player->controller.left && player->snake.head.dir != player->controller.right) ||
            (dir == player->controller.right && player->snake.head.dir != player->controller.left)) {
            player->snake.head.dir = dir;
        }
    }

    // Now we move the head to the new position (based on the direction of the previous head or the new input)
    if (dir == player->controller.up) {
        player->snake.head = (snake_body_t){player->snake.head.x, player->snake.head.y - 1, 
                                            player->snake.head.dir};
    } else if (dir == player->controller.right) {
        player->snake.head = (snake_body_t){player->snake.head.x + 1, player->snake.head.y, 
                                            player->snake.head.dir};
    } else if (dir == player->controller.down ) {
        player->snake.head = (snake_body_t){player->snake.head.x, player->snake.head.y + 1, 
                                            player->snake.head.dir};
    } else if (dir == player->controller.left ) {
        player->snake.head = (snake_body_t){player->snake.head.x - 1, player->snake.head.y, 
                                            player->snake.head.dir};
    }

    // Finally, we set the new head position to the player id
    collision_board[player->snake.head.x][player->snake.head.y] = player->uid;


}


// void move_player(player_t player) {

        

//     uint8_t dir = player->snake.tail.dir;
//     if (dir == player->controller.up) {
//         player->snake.tail.y--;
//     } else if (dir == player->controller.right) { 
//         player->snake.tail.x++;
//     } else if (dir == player->controller.down) {
//         player->snake.tail.y++;
//     } else if (dir == player->controller.left) {
//         player->snake.tail.x--;
//     }
    
//     // if(player->snake.len != 1)
//         collision_board[player->snake.tail.x][player->snake.tail.y] = 0;

//     char c = getchar();
//     if (c == 0) {
//         c = player->snake.head.dir;
//     }    

//     // Handle direction change and check for opposite direction
//     if ((c == player->controller.up && player->snake.head.dir != player->controller.down) ||
//         (c == player->controller.down && player->snake.head.dir != player->controller.up) ||
//         (c == player->controller.left && player->snake.head.dir != player->controller.right) ||
//         (c == player->controller.right && player->snake.head.dir != player->controller.left)) {
//         player->snake.head.dir = c;
//     }

//     // @TODO: Make switch statement
//     int uid = player->uid;
//     // if (player->snake.len == 1) {
//     //     player->snake.tail = player->snake.head; 
//     //     collision_board[player->snake.tail.x][player->snake.tail.y] = uid;
//     // }


//     if (c == player->controller.up) {
//         player->snake.head.y--;
//         player->snake.head.dir = player->controller.up;
//     }
//     else if (c == player->controller.right) {
//         player->snake.head.x++;
//         player->snake.head.dir = player->controller.right;
//     }
//     else if (c == player->controller.down ) {
//         player->snake.head.y++;
//         player->snake.head.dir = player->controller.down;
//     }
//     else if (c == player->controller.left ) {
//         player->snake.head.x--;
//         player->snake.head.dir = player->controller.left;
//     }

//     collision_board[player->snake.head.x][player->snake.head.y] = uid;
//     // collision_board[player->snake.head.x][player->snake.head.y] = uid;
//     // collision_board[player->snake.tail.x][player->snake.tail.y] = 0;


// }

void food() {

    int x, y;
    do {
        x = rand(21304, BOARD_SIZE);
        y = rand(21304, BOARD_SIZE);
    } while (collision_board[x][y] != 0);

    // collision_board[x][y] = FRUIT;
    
    // temp
    collision_board[10][5] = FRUIT;
}

void check_collision(player_t player) {
    
    // check player in bound
    if (player->snake.head.x < 0 || player->snake.head.x >= BOARD_SIZE 
        || player->snake.head.y < 0 || player->snake.head.y >= BOARD_SIZE) {
            player->alive = 0;
    }

    switch (collision_board[player->snake.head.x][player->snake.head.y]) {
        case 0:
            break;
        case FRUIT:
            collision_board[player->snake.head.x][player->snake.head.y] = player->uid;
            // increment_length(); has to add another bodypart to tail.
            increment_length(player);
            food();
            break;
        default:
            // collided with a player or themselves


            // if player len is 1 (head only) ignore collision
            if (player->snake.len == 1)
                break; 

            player->alive = 0;
            break;
    }
    // else if (collision_board[player->snake.head.x][player->snake.head.y] > 0) {
    //     //player.alive = 0;
    // }
}

void increment_length(player_t player) {
    player->snake.len++;
    printf("%d", player->snake.len);
    // we move the tail to the new position and add a new tail
    uint8_t dir = player->snake.tail.dir;
    if (dir == player->controller.up) {
        player->snake.tail = (snake_body_t){player->snake.tail.x, player->snake.tail.y + 1, 
                                            player->snake.tail.dir};
    } else if (dir == player->controller.right) { 
        player->snake.tail = (snake_body_t){player->snake.tail.x - 1, player->snake.tail.y, 
                                            player->snake.tail.dir};
    } else if (dir == player->controller.down) {
        player->snake.tail = (snake_body_t){player->snake.tail.x, player->snake.tail.y - 1, 
                                            player->snake.tail.dir};
    } else if (dir == player->controller.left) {
        player->snake.tail = (snake_body_t){player->snake.tail.x + 1, player->snake.tail.y, 
                                            player->snake.tail.dir};
    }

   collision_board[player->snake.tail.x][player->snake.tail.y] = player->uid;
   
}