#include <shell.h>
#include <syscalls.h>
#include <stdio.h>
#include <stdlib.h>

void shell() {
	putchar('\n');
    write(1, "hola", 4, 0xFF00FF, 0x000000);
    putchar_color("Welcome to AmongOS Shell\n", 0xFF00FF, 0x000000);
	printf("To see the list of available commands, type 'help'\n");
	putchar('\n');
    // if pressed enter write the new line

    // if (read() == '\n') {
	    printf("user@AmongOS:~$ ");
    // }
    printf("Shell");
}