/******************************************************************************
 *
 * @file    shell.h
 *
 * @brief   Shell.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/
#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <colors.h>


/*
 * @name shell
 * @brief Shell :).
 */
void shell();

/*
 * @name print_ps1
 * @brief Prints the shell prompt.
 *
 */
void print_ps1(char *user, char *pwd);

/*
 * @name print_header
 * @brief Prints the shell header.
 */
void print_header();

#endif