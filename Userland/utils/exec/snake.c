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
    uint64_t len;
};

struct food {
    uint64_t x;
    uint64_t y;
};


struct player {
    int uid;
    char* name;
    color_t color;
    snake_t snake;
    controller_t controller;
    uint8_t alive;
};

struct block {
    int uid;
    int count;
};

static block_t collision_board[BOARD_SIZE][BOARD_SIZE];
static uint8_t player_count = 0;



void snake(){
    player_count = 0;
    main_menu();
}

void main_menu() {
    player_t player1;
    player_t player2;
    clear(COLOR_BLACK);
    writing_pos(20 * PIXEL, 8 * PIXEL);
    printf_color("SNAKE: The last impostor.", COLOR_WHITE, COLOR_BLACK);

    putchar('\n');
    writing_pos(20 * PIXEL, 10 * PIXEL);
    int plcount = 0;
    scanf("Player count (1-2): %d", &plcount);
    // printf("%d", plcount);

    putchar('\n');
    writing_pos(20 * PIXEL, 10 * PIXEL);

    // initialize collision board 
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            collision_board[i][j].uid = 0;
            collision_board[i][j].count = 0; 
        }
    }
    // fix scanf is not changing the value from ascii to number
    // switch (plcount) {
    //     case '2':
    //         scanf("\nPlease enter P2 name: %s\n", player2->name);
    //         putchar('\n');
    //         writing_pos(20 * PIXEL, 10 * PIXEL);
    //         init_player(player2, player2->name, COLOR_RED, (controller_t){'i','k','j','l'});
    //     case '1':
    //         scanf("\nPlease enter P1 name: %s\n", player1->name);
    //         init_player(player1 , player1->name, COLOR_GREEN, (controller_t){'w','s','a','d'});
    //         break;
    //     default:
    //         clear(COLOR_BLACK);
    //         printf_color("Invalid player count, aborting...\n", COLOR_WHITE, COLOR_BLACK);
    //         sleep(2000);
    //         clear(COLOR_BLACK);
    //         return;
    //         // exit(); @TODO
    //         break;
    // }


    // writing_pos(20 * PIXEL, 10 * PIXEL);
    // scanf("\nPress any key to start %d", 0);

    
    // game(player1, player2, plcount - '0');
    init_player(player1, player1->name, COLOR_RED, (controller_t){'w','s','a','d'});
    init_player(player2, player2->name, COLOR_GREEN, (controller_t){'i','k','j','l'});
    game(player1, player2);

    
}

void game(player_t player1, player_t player2) {
    // clear(COLOR_BLACK);


    draw_board(COLOR_WHITE, BOARD_SIZE * PIXEL, DRAW_START_X, DRAW_START_Y);

    // initialize player

    // spawn a starting fruit.
    food();

    do {

        draw_game(player1, player2);
        move_player(player1, player2);

        // fix: if theres two players, inputs are not read correctly. (also, collision board is not setup correctly for 2 players)
        // if (player_count == 2) {
        //     move_player(player2);
        // }
        sleep(200);
      // temp  
    } while ((player_count == 1 && player1->alive) || 
            (player_count == 2 && (player1->alive || player2->alive)));

    // clear(COLOR_BLACK);
    writing_pos(20 * PIXEL, 10 * PIXEL);
    printf_color("GAME OVER", COLOR_WHITE, COLOR_BLACK);
    putchar('\n');
    sleep(500);
    clear(COLOR_BLACK);
    return;
    // exit(0);
}

void init_player(player_t player, char* name, color_t color, controller_t controller) {
    player->name = name;
    player->color = color;
    player->controller = controller;
    player->snake.len = 5;

    player->alive = 1;
    
    player->snake.head.x = 4 + player_count * 15;
    player->snake.head.y = BOARD_SIZE / 2;

    player->uid = ++player_count;
    player->snake.head.dir = player_count == 1 ? controller.right : controller.left;

    collision_board[player->snake.head.x][player->snake.head.y].uid = player->uid;
    collision_board[player->snake.head.x][player->snake.head.y].count = player->snake.len;
}

void draw_board(color_t color, uint16_t size, uint64_t x, uint64_t y) {
    draw_rectangle(color, size + PIXEL, x - PIXEL, y - PIXEL);
}

// change name to update board
void draw_game(player_t player1, player_t player2){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
  
            switch (collision_board[i][j].uid) {
                // fruit
                case FRUIT: 
                    draw_pixel(COLOR_MAGENTA, PIXEL/2, DRAW_START_X + i*PIXEL, DRAW_START_Y + j * PIXEL);
                    break;
                // nothing
                case 0: 
                    draw_pixel(COLOR_BLACK, PIXEL, DRAW_START_X + i * PIXEL, DRAW_START_Y + j * PIXEL);
                    break;
                // player
                case 1:
                    if (player1->alive)
                        draw_pixel(player1->color, PIXEL, DRAW_START_X + i * PIXEL, DRAW_START_Y + j * PIXEL);
                    break;
                case 2:
                    if (player2->alive)
                    draw_pixel(player2->color, PIXEL, DRAW_START_X + i * PIXEL, DRAW_START_Y + j * PIXEL);
                    break;
            }
            
            if (collision_board[i][j].count > 0) {
                collision_board[i][j].count--;
                
            } else if (collision_board[i][j].uid != FRUIT){
                collision_board[i][j].uid = 0;
            }
           
        }
    }
    
    
}

static test_input_dir(uint8_t ch, player_t player) {
    return ch == player->controller.up || ch == player->controller.down || 
        ch == player->controller.left || ch == player->controller.right;
}

void move_player(player_t player1, player_t player2) {

    char ch = getchar();

    if (test_input_dir(ch, player1)) {
        update_position(player1, ch);
    } else {
        update_position(player1, 0);
    }

    if (player_count == 2) {
        if (test_input_dir(ch, player2)) {
            update_position(player2, ch);
        } else {
            update_position(player2, 0);
        }
    }
}

void update_position(player_t player, uint8_t dir) {

    // If no input or oposite direction, move in the same direction as the previous head
    if ((dir == 0) || (dir == player->controller.up && player->snake.head.dir == player->controller.down) || 
                (dir == player->controller.down && player->snake.head.dir == player->controller.up) ||
                (dir == player->controller.left && player->snake.head.dir == player->controller.right) ||
                (dir == player->controller.right && player->snake.head.dir == player->controller.left)) {
        dir = player->snake.head.dir;
    } else { 
        player->snake.head.dir = dir;
    }

    // Move the head to the new position (based on the direction of the previous head or the new input)
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

    check_collision(player);
    // Set the new head position to the player id
    collision_board[player->snake.head.x][player->snake.head.y].count = player->snake.len;
    collision_board[player->snake.head.x][player->snake.head.y].uid = player->uid;


}


void food() {

    int x, y;
    do {
        x = rand(21304, BOARD_SIZE);
        y = rand(21304, BOARD_SIZE);
    } while (collision_board[x][y].uid != 0);

     collision_board[x][y].uid = FRUIT;
    
}

void check_collision(player_t player) {
    
    // check player in bound of playing area
    if (player->snake.head.x < 0 || player->snake.head.x >= BOARD_SIZE 
        || player->snake.head.y < 0 || player->snake.head.y >= BOARD_SIZE) {
            writing_pos(0, 20);
            printf("Player %d out of bounds\n", player->uid);
            player->alive = 0;
            return;
    }

    switch (collision_board[player->snake.head.x][player->snake.head.y].uid) {
        // empty space, do nothing
        case 0:
            break;
        
        case FRUIT:
            collision_board[player->snake.head.x][player->snake.head.y].uid = player->uid;
            increment_length(player);
            food();
            break;
        
        // collided with a player or themselves
        default:

            player->alive = 0;
            break;
    }
}

void increment_length(player_t player) {
    player->snake.len++; 
}