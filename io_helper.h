/**
* @file io_helper.h
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Describes functions to assist main.c in parsing input and displaying output.
* @date 7 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#ifndef IO_HELPER_H
#define IO_HELPER_H

bool mult(int ret_loc, char *arg1, char *arg2, int v_arg1_loc, int v_arg2_loc);

bool arg_to_double(char *arg, double *val);

void replace(char *data, char key, char new_val);

void print_result(vect result);

bool display(char *code);

#endif