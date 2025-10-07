/**
* @file io_helper.h
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Describes functions to assist main.c in parsing input and displaying output.
* @date 27 September 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#ifndef IO_HELPER_H
#define IO_HELPER_H

void display_op(char *arg1, char *op, char *arg2);

void str_op(char *ret, char *arg1, char *op, char *arg2);

bool display(char *code);

#endif