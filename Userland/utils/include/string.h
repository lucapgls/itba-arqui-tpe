/******************************************************************************
 *
 * @file    string.h
 *
 * @brief   String related functions.
 *
 * @author  Luca Pugliese                           <lpugliese@itba.edu.ar>
 * @author  Felipes Venturino                        <fventurino@itba.edu.ar>
 * @author  Uriel Sosa Vazquez                      <usosavazquez@itba.edu.ar>
 *
 ******************************************************************************/

#ifndef STRING_H
#define STRING_H
#include <stdint.h>

/*
 * @brief Compares the src to tgt.
 * @param src pointer to the source of data.
 * @param tgt pointer to the destination array.
 */
int8_t strcmp(const char* src, const char* tgt);


/*
 * @brief size of the string.
 * @returns Length of the string.
 */
uint64_t strlen(char* buff);
#endif