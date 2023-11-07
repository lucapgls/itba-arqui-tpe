#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct command {
	char* name;
	char* description;
	int (*cmd)();
} command_t;

void execute_command(char* cmdname);
void print_help();
void screen();
void font();
void print_amongus();
void print_random();
void print_time();
void print_clear();
void print_regs();

#endif