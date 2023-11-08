#include "snake.h"
#include <amongus.h>
#include <colors.h>
#include <draw.h>
#include <random.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscalls.h>

#define PIXEL 16
#define BOARD_SIZE 32
#define FRUIT -1

#define DRAW_START_X 10 * PIXEL
#define DRAW_START_Y 5 * PIXEL
#define SNAKE_LENGTH 5

struct controller {
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;
};

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
static uint8_t player_count;

void snake() {

    player_count = 0;
    main_menu();
}


void main_menu() {
    uint64_t width, height;
    screen_info(&width, &height);
    player_t player1; 
    player_t player2;

    clear(COLOR_BLACK);
    amongus(0, height / 2 + 160);
    font_size(2);
    writing_pos(width / 2 - 12 * PIXEL, 90);
    printf_color("SNAKE: ", COLOR_RED, COLOR_BLACK);
    printf_color("The last impostor", COLOR_WHITE, COLOR_BLACK);
    font_size(1);
    writing_pos(width / 2 - 5 * PIXEL, height / 2 - 8 * PIXEL);
    int plcount = 0;
    scanf("Player count (1-2): %d", &plcount);

    // initialize collision board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            collision_board[i][j].uid = 0;
            collision_board[i][j].count = 0;
        }
    }

    if (plcount == 1) {
        init_player(player1, COLOR_RED, (controller_t){'w', 's', 'a', 'd'});
    } else if (plcount == 2) {
        init_player(player1, COLOR_RED, (controller_t){'w', 's', 'a', 'd'});
        init_player(player2, COLOR_GREEN, (controller_t){'i', 'k', 'j', 'l'});
    } else {
        clear(COLOR_BLACK);
        printf_color("Invalid player count, aborting...\n", COLOR_WHITE, COLOR_BLACK);
        sleep(500);
        clear(COLOR_BLACK);
        return;
    }

    for (int i = 3; i > 0; i--) {
        writing_pos(width / 2 - 5 * PIXEL, height / 2 - 6 * PIXEL);
        printf("Game starting in: %d", i);
        sleep(500);
    }

    clear(COLOR_BLACK);

    game(player1, player2);
}

void game(player_t player1, player_t player2) {

    draw_board(COLOR_WHITE, BOARD_SIZE * PIXEL, DRAW_START_X, DRAW_START_Y);
    hud(player1, player2);

    // initialize player

    // spawn a starting fruit.
    food();

    do {

        draw_game(player1, player2);
        move_player(player1, player2);

        sleep(200);
    } while ((player_count == 1 && player1->alive) ||
             (player_count == 2 && (player1->alive || player2->alive)));

    gameover_menu();
}

void gameover_menu() {

    uint64_t width, height;
    screen_info(&width, &height);

    clear(COLOR_BLACK);

    font_size(2);
    writing_pos(width / 2 - 12 * PIXEL, 90);
    printf_color("SNAKE: ", COLOR_RED, COLOR_BLACK);
    printf_color("The last impostor", COLOR_WHITE, COLOR_BLACK);
    font_size(1);
    writing_pos(width / 2 - 9 * PIXEL, height / 2 - 9 * PIXEL);
    printf("The game is over, good luck next time!");
    writing_pos(width / 2 - 5 * PIXEL + 8, height / 2 - 6 * PIXEL);
    printf("Press 'Q' to quit");
    writing_pos(width / 2 - 5 * PIXEL + 8, height / 2 - 4 * PIXEL);
    printf("Press 'R' to restart");
    uint8_t ch;
    // ask for a character until it is 'q' or 'r' with getchar
    do {
        ch = getchar();
    } while (ch != 'q' && ch != 'r');

    if (ch == 'q') {
        clear(COLOR_BLACK);
        writing_pos(width / 2 - 5 * PIXEL, height / 2 - PIXEL);
        printf_color("Thanks for playing! <3\n", COLOR_GREEN, COLOR_BLACK);
         for(int i = 1000; i > 850; i-=10){
            sound(i, 100);
    }
        sleep(500);
        clear(COLOR_BLACK);
        return;
    } else if (ch == 'r') {
        clear(COLOR_BLACK);
        snake();
    }
    clear(COLOR_BLACK);
}

void init_player(player_t player, color_t color, controller_t controller) {
    player->color = color;
    player->controller = controller;
    player->snake.len = SNAKE_LENGTH;

    player->alive = 1;

    player->snake.head.x = 4 + player_count * 15;
    player->snake.head.y = 6;

    player->uid = ++player_count;
    player->snake.head.dir = player_count == 1 ? controller.right : controller.left;

    collision_board[player->snake.head.x][player->snake.head.y].uid = player->uid;
    collision_board[player->snake.head.x][player->snake.head.y].count = player->snake.len;
}

void draw_board(color_t color, uint16_t size, uint64_t x, uint64_t y) {
    draw_rectangle(color, size + PIXEL, x - PIXEL, y - PIXEL);
}

// change name to update board
void draw_game(player_t player1, player_t player2) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            switch (collision_board[i][j].uid) {
            // fruit
            case FRUIT:
                draw_pixel(COLOR_MAGENTA, PIXEL / 2, DRAW_START_X + i * PIXEL, DRAW_START_Y + j * PIXEL);
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
            } else if (collision_board[i][j].uid != FRUIT) {
                collision_board[i][j].uid = 0;
            }
        }
    }
}

static int test_input_dir(uint8_t ch, player_t player) {
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
    } else if (dir == player->controller.down) {
        player->snake.head = (snake_body_t){player->snake.head.x, player->snake.head.y + 1,
            player->snake.head.dir};
    } else if (dir == player->controller.left) {
        player->snake.head = (snake_body_t){player->snake.head.x - 1, player->snake.head.y,
            player->snake.head.dir};
    }

    // debug player position
    // writing_pos(0, 30);
    // printf("X: %d, Y: %d\n", player->snake.head.x, player->snake.head.y);

    check_collision(player);
    collision_board[player->snake.head.x][player->snake.head.y].count = player->snake.len;
    collision_board[player->snake.head.x][player->snake.head.y].uid = player->uid;
    // Set the new head position to the player id
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
    if (player->snake.head.x < 0 || player->snake.head.x >= BOARD_SIZE || player->snake.head.y < 0 || player->snake.head.y >= BOARD_SIZE) {
        player->alive = 0;
        delete_snake(player);
        kill_snake(player);
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
        update_points(player);
        sound(1000, 100);
        break;

    // collided with a player or themselves
    default:
        player->alive = 0;
        delete_snake(player);
        kill_snake(player);
        break;
    }
}

void delete_snake(player_t player) {
    // iterate through the colliosion matrix and replace all the values of the player id with 0
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (collision_board[i][j].uid == player->uid) {
                collision_board[i][j].uid = 0;
                collision_board[i][j].count = 0;
                player->snake.len = 0;
                player->snake.head.x = -1;
                player->snake.head.y = -1;
            }
        }
    }
}

void increment_length(player_t player) {
    player->snake.len++;
}

void update_points(player_t player) {
    if (player->uid == 1) {
        writing_pos(46 * PIXEL, 7 * PIXEL);
    } else if (player->uid == 2) {
        writing_pos(46 * PIXEL, 17 * PIXEL);
    }
    printf("points: %d\n", player->snake.len - SNAKE_LENGTH);
}

void hud(player_t player1, player_t player2) {
    switch (player_count) {
    case 2:
        draw_rectangle(COLOR_WHITE, 8 * PIXEL, 45 * PIXEL, 15 * PIXEL);
        writing_pos(46 * PIXEL, 16 * PIXEL);
        printf("player 2");
        update_points(player2);
    case 1:
        draw_rectangle(COLOR_WHITE, 8 * PIXEL, 45 * PIXEL, 5 * PIXEL);
        writing_pos(46 * PIXEL, 6 * PIXEL);
        printf("player 1");
        update_points(player1);
        break;
    }
}

void kill_snake(player_t player) {
    if (player->uid == 1) {
        writing_pos(47 * PIXEL, 8 * PIXEL);
    } else if (player->uid == 2) {
        writing_pos(47 * PIXEL, 18 * PIXEL);
    }
    printf_color("EXECUTED", COLOR_RED, COLOR_BLACK);
}