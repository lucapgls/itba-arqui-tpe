#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <colors.h>

void shell();

void print_ps1(char *user, char *pwd);
void buffer_command(const char *buff);

#endif