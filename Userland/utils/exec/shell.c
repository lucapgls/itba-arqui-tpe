#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscalls.h>
#include <commands.h>

#define EOF (-1)
#define MAX_BUFFER_SIZE 1024

void shell() {

    print_header();

    char buff[MAX_BUFFER_SIZE];

    // SHELL LOOP
    while (1) {
        print_ps1("user", "~");
        gets(buff, MAX_BUFFER_SIZE);
        execute_command(buff);
        hlt();
    }
}


void print_header() {

    printf_color("Welcome to AmongOS Shell (SUShell) \n", COLOR_MAGENTA, COLOR_BLACK);
    putchar('\n');
    printf("To see the list of available commands, type 'help'\n");
    putchar('\n');
    putchar('\n');
}

void print_ps1(char *user, char *pwd) {

    printf_color("%s@AmongOS", COLOR_GREEN, COLOR_BLACK, user);
    printf_color("%s$ ", COLOR_MAGENTA, COLOR_BLACK, pwd);
}
