#include <shell.h>
#include <syscalls.h>
#include <stdio.h>
#include <stdlib.h>
#include <random.h>

#define EOF (-1)
void shell() {

	// SHELL HEADER
	putchar('\n');
    printf_color("Welcome to AmongOS Shell\n", COLOR_MAGENTA, COLOR_BLACK);   
	putchar('\n');
	printf("To see the list of available commands, type 'help'\n");
	putchar('\n');
	printf("user@AmongOS:~$ ");
	//

    // printf("random: %d y %d", random(), 9);
    // printf("%s", "Amigooooos");


	// SHELL LOOP
	while (1) {
    	if (getchar() == 'j') {
			char* buff[20];
	    	printf("user@AmongOS:~$ ");
		// 	gets(buff, 20);
		// printf("%s", buff);
		}

		// read(1, buff, 20);
		// scanf("%d", &buff);
		// printf("Esto: %s", buff);
		// if (buff == '9') {
		// 	printf("asdjsa");
		// }
	}
}