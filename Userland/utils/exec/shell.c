#include <shell.h>
#include <syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <random.h>
#include <string.h>
#include <draw.h>
#include <amongus.h>
#include <snake.h>

#define EOF (-1)
#define MAX_BUFFER_SIZE 1024

void shell() {

	/*
	sleep(1000);
	amongus(0,0);
	sleep(3000);
	for(int i = 0; i<300; i += 2){
		draw_line(0x000000,0,i,1100,i);
	}
	*/
	// SHELL HEADER
	putchar('\n');
    printf_color("Welcome to AmongOS Shell (SUShell) \n", COLOR_MAGENTA, COLOR_BLACK);   
	putchar('\n');
	printf("To see the list of available commands, type 'help'\n");
	putchar('\n');
	putchar('\n');

	for (int i = 0; i < 10; ++i) {
        int randomNumber = rand(21304, BOARD_SIZE);
        // Do something with the random number, for example, print it
        printf("%d\n", randomNumber);
    }
	//sound((uint8_t)0x0888,1	);
	

	char buff[MAX_BUFFER_SIZE];

	// for (int i =0; i< 10 ; i++ ) {
	// 	printf("Random number: %d\n", random(i)); 
		
	// }
		
	

	// SHELL LOOP
	while (1) {
		print_ps1("user", "~");
		gets(buff, MAX_BUFFER_SIZE);
		buffer_command(buff);
		hlt();
	}

}

void buffer_command(const char *buff)
{
	if (strcmp(buff, "help") == 0) {
		printf("\nAvailable commands:\n");
		printf("help: Shows this help\n");
		printf("clear: Clears the screen\n");
		printf("time: Shows the current time\n");
		printf("date: Shows the current date\n");
		printf("random: Shows a random number\n");
		printf("exit: Exits the shell\n");
	}
	else if (strcmp(buff, "amongus") == 0) {
		print_amongus();
	}

	// else if (strcmp(buff, "clear") == 0) {
	// 	clear_screen();
	// }
	else if (strcmp(buff, "time") == 0) {
		printf("\n%s\n", time());
	}
	else if (strcmp(buff, "clear") == 0) {
		// @FIX: needs to start printing from 0, 0
		clear(COLOR_BLACK);
	}
	else if (strcmp(buff, "snake") == 0) {
		clear(COLOR_BLACK);
		snake();
	}
	else if (strcmp(buff, "random") == 0) {
		printf("\n%d\n", random(1203929));
	}
	// else if (strcmp(buff, "date") == 0) {
	// 	printf("Date: d/d/d\n", get_day(), get_month(), get_year());
	// }
	// else if (strcmp(buff, "random") == 0) {
	// 	printf("Random: d\n", random());
	// }
	// else if (strcmp(buff, "exit") == 0) {
	// 	exit(0);
	// }
	else if (strcmp(buff, "") != 0) {
		printf("\nSUShell: '%s' command not found\n", buff);
	}	
}

void print_ps1(char *user, char *pwd) {

	printf_color("%s@AmongOS", COLOR_GREEN, COLOR_BLACK, user);
	printf_color("%s$ ", COLOR_MAGENTA, COLOR_BLACK, pwd);
}

void print_amongus() {
	printf_color("\n........ooooooooo.......\n", COLOR_RED, COLOR_BLACK);
	printf_color("......oo.....oooooo.....\n", COLOR_RED, COLOR_BLACK);
	printf_color("......oo...oo......oo...\n", COLOR_RED, COLOR_BLACK);
	printf_color("......oo.....oooooo.....\n", COLOR_RED, COLOR_BLACK);
	printf_color("......oo.......oo.......\n", COLOR_RED, COLOR_BLACK);
	printf_color("......oo...oo..oo.......\n", COLOR_RED, COLOR_BLACK);
	printf_color("......oo...oo..oo.......\n", COLOR_RED, COLOR_BLACK);
	printf_color("......ooo..oo.ooo.......\n", COLOR_RED, COLOR_BLACK);
}