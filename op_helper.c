/**
* @file op_helper.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Defines functions to parse and compute miniMATLAB operations.
* @date 7 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "vect.h"
#include "vect_math.h"
#include "io_helper.h"

/**
* @brief Function displays the opperation of arg1 op arg2 to the user.
* The function does not store the result to memory. This function is called when
* arg2 is either +, -, or *.
* @param arg1 The first vector.
* @param op The opperation to perform.
* @param arg2 The second vector.
*/
void display_op(char *arg1, char *op, char *arg2) {
    int v_arg1_loc = findvect(arg1);
    int v_arg2_loc = findvect(arg2);

    if (*op == '*') {
            //multiply
            mult(-1, arg1, arg2, v_arg1_loc, v_arg2_loc);
        } else if (*op == '+') {
            if (v_arg1_loc != -1 && v_arg2_loc != -1) {
                vect result = add(getvect(v_arg1_loc), getvect(v_arg2_loc));
                print_result(result);
            } else {
                //invalid argument
                printf("Invalid argument: Could not find vector: %s\n", (v_arg1_loc == -1) ? arg1 : arg2);
            }
        } else if (*op == '-') {
            if (v_arg1_loc != -1 && v_arg2_loc != -1) {
                vect result = sub(getvect(v_arg1_loc), getvect(v_arg2_loc));
                print_result(result);
            } else {
                //invalid argument
                printf("Invalid argument: Could not find vector: %s\n", (v_arg1_loc == -1) ? arg1 : arg2);
            }
        } else {
            //invalid expression
            printf("Error: Invalid expression: %s %s %s\n", arg1, op, arg2);
        }
}

/**
* @brief Stores the output of arg1 op arg2 in the return vector specified. 
* Creates a new vector if there is no existing vector with the given name.
* @param ret A string storing the name of vector to put the return in.
* @param arg1 The first vector.
* @param op The opperation to perform on the 2 vectors.
* @param arg2 The second vector.
*/
void str_op(char *ret, char *arg1, char *op, char *arg2) {
    vect* v_ret;
    vect* v_arg1;
    vect* v_arg2;
    int v_ret_loc = findvect(ret);
    int v_arg1_loc = findvect(arg1);
    int v_arg2_loc = findvect(arg2);
    //if at any point valid_op becomes false for any reason, an error has occured
    //and the result of the opperation is not stored
    bool valid_op = true;

    if (strlen(ret) > 1) {
        printf("Error: variable name invalid. Expected name of 1 character. Got %ld characters\n", strlen(ret));
        valid_op = false;
    }

    if (v_ret_loc == -1) {
        //no existing return vector, make a new one
        vect v;
        v.name = *ret;
        if (addvect(v) == -1) {
            //error when adding vector
            printf("Error: No room in vector memory for storage. Operation skipped.\n");
            valid_op = false;
        } else {
            //if vect of same name already exists, the data will be overwritten
            //as findvect() returns the first location where the name occurs.
            v_ret_loc = findvect(ret);
        }
    } 

    //check to see if the value of the op can be stored, if it can continue, else skip the operation.
    if (v_ret_loc != -1) {
        if (*op == '*') {
            //multiply
            valid_op = mult(v_ret_loc, arg1, arg2, v_arg1_loc, v_arg2_loc);
        } else if (*op == '+') {
            if (v_arg1_loc != -1 && v_arg2_loc != -1) {
                vect result = add(getvect(v_arg1_loc), getvect(v_arg2_loc));
                write_vect_data(v_ret_loc, result);
            } else {
                //invalid argument
                printf("Invalid argument: Could not find vector: %s\n", (v_arg1_loc == -1) ? arg1 : arg2);
                valid_op = false;
            }
        } else if (*op == '-') {
            if (v_arg1_loc != -1 && v_arg2_loc != -1) {
                vect result = sub(getvect(v_arg1_loc), getvect(v_arg2_loc));
                write_vect_data(v_ret_loc, result);
            } else {
                //invalid argument
                printf("Invalid argument: Could not find vector: %s\n", (v_arg1_loc == -1) ? arg1 : arg2);
                valid_op = false;
            }
        } else {
            //if op is not an opperator, this could also be an assignment case
            double arg1_val;
            double arg2_val;
            double arg3_val;

            //remove any potential commas used during assignment
            replace(arg1, ',', ' ');
            replace(op, ',', ' ');
            replace(arg2, ',', ' ');

            //validate arg1, op, and arg2 are all doubles
            //if they are, make a new vect, else display an error message.
            bool arg1_valid = arg_to_double(arg1, &arg1_val);
            bool arg2_valid = arg_to_double(op, &arg2_val);
            bool arg3_valid = arg_to_double(arg2, &arg3_val);

            if (arg1_valid && arg2_valid && arg3_valid) {
                vect new_vect;
                new_vect.a = arg1_val;
                new_vect.b = arg2_val;
                new_vect.c = arg3_val;

                write_vect_data(v_ret_loc, new_vect);
            } else {
                //invalid op
                valid_op = false;
                printf("Error assigning values: Expected: v_name = arg1, arg2, arg3.\n");
            }
        }
        
    } 

    if (!valid_op) {
        rmvvect(ret);
    }

}
