/******************************************************************************
 *
 * @file    commands.h
 *
 * @brief   Shell commands.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct command {
	char* name;
	char* description;
	int (*cmd)();
} command_t;

void execute_command(char* cmdname);

// Commands
void print_help();
void screen();
void font();
void print_amongus();
void print_random();
void print_time();
void print_clear();
void print_regs();

#endif