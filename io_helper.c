/**
* @file io_helper.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Defines functions to assist main.c in parsing input and displaying output.
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
#include <stdlib.h>
#include "vect_math.h"
#include "vect.h"
#include "io_helper.h"

/**
* @brief Prints out the resulting vector from an opperation.
* @param result The vector containing the data to be printed.
*/
void print_result(vect result) {
    printf("<%.3f, %.3f, %.3f>\n", result.a, result.b, result.c);
}

/**
* @brief Replaces all characters of value key in char string data with char new_val.
* @param data The string to search.
* @param key The key to search for in the data string.
* @param new_val The value to replace key with in the data string.
*/
void replace(char *data, char key, char new_val) {
    char *ptr = strchr(data, key);

    //do this while key exists in data string
    while(ptr != NULL) {
        //change value at ptr to be new_val instead of key
        *ptr = new_val;

        //move to next location of key
        ptr = strchr(data, key);
    } 
}

/**
* @brief Converts a user argument to a double.
* @param arg The argument to convert into a double.
* @param val The value of the argument, the function will assign this value.
* @return True if sucsessful, false otherwise.
*/
bool arg_to_double(char *arg, double *val) {
    char *endptr;
    *val = strtod(arg, &endptr);

    if (*endptr == '\0' || *endptr == '\n' || *endptr == ' ') {
        //valid argument, return true
        return true;
    } else {
        printf("Invalid Argument: \'%s\' Extected type double.\n", arg);
        return false;
    }
}

/**
* @brief Performs scalar multiplication on arg1 * arg2 and stores the result at the
* return v_mem address provided.
* @param ret_loc The address where the result will be stored in vector memory.
* If ret_loc = -1, nothing is written back to the storage array, data will be displayed instead.
* @param arg1 The first argument -- either a vector name or factor of type double.
* @param arg2 The second argument -- either a vector name or factor of type double.
* @param v_arg1_loc The location of arg1 in vector memory.
* @param v_arg2_loc The location of arg2 in vector memory.
* @return Returns true if the mult function executes with no errors, false otherwise.
*/
bool mult(int ret_loc, char *arg1, char *arg2, int v_arg1_loc, int v_arg2_loc) {
    //arg1 is the double to parse, endptr is where the parser ends in the string
    char *endptr;
    double factor = strtod(arg1, &endptr);
    vect result;
    bool valid_op = true;

    if (*endptr == '\0' || *endptr == '\n') { 
        //the end pointer made it to the end of arg1 sucsessfully
        if (v_arg2_loc != -1) {
            //both valid arguments, perform scalar multiplication
            result = scalar_mult(factor, getvect(v_arg2_loc));
        } else {
            printf("Invalid argument: %s\nExpected: v_name\n", arg2);
            valid_op = false;
        }
    } else {
        //arg1 was not a valid factor, check arg2
        factor = strtod(arg2, &endptr);
        if (*endptr == '\0' || *endptr == '\n') { 
            //the end pointer made it to the end of arg1 sucsessfully
            if (v_arg1_loc != -1) {
                //both valid arguments, perform scalar multiplication
                result = scalar_mult(factor, getvect(v_arg1_loc));
            } else {
                valid_op = false;
                printf("Invalid argument: %s\nExpected: v_name\n", arg1);
            }
        } else {
            valid_op = false;
            printf("Error: Could not find double in arg1: %s or arg2: %s\n", arg1, arg2);
        }
    }
    //write result to vector memory if sucsessful opperation
    if (result.name != '\0' && ret_loc != -1) {
        write_vect_data(ret_loc, result);
    } else if (ret_loc == -1 && valid_op) {
        print_result(result);
    }
    return valid_op;
}

/**
* @brief Displays what the user requests. (I.e. list, help, clear, quit, vect_name)
* @param code The code specifying what to display.
* @return True if the code was "quit" and the user requested program termination.
* False otherwise.
*/
bool display(char *code) {

    if (strcmp(code, "quit\n") == 0) {
        return true;
    } else if (strcmp(code, "list\n") == 0) {
        //Display all active vectors in vector memory
        vect *curr_vect;
        bool empty = true;
        for (int i = 0; i < get_vmem_size(); ++i) {
            curr_vect = getvect(i);
            if (curr_vect != NULL) {
                printf("Vector: %c = <%.3f, %.3f, %.3f>\n", curr_vect->name, 
                    curr_vect->a, curr_vect->b, curr_vect->c);
                empty = false;
            }
        }
        if (empty) {
            printf("No vectors to be displayed.\n");
        }
    } else if (strcmp(code, "clear\n") == 0) {
        //clear the vector memory
        printf("Clearing vector memory...\n");
        clear(0);
    } else if (strcmp(code, "help\n") == 0) {
        //Display the help menu
        printf("Options:\n\n");
        printf("1. v_name1 = v_name2 op v_name3\n"
            "-- Stores the result of v_name2 op v_name3 in v_name1\n\n");
        printf("2. v_name2 op v_name3\n"
            "-- Displays the result of v_name2 op v_name3 in v_name1\n\n");
        printf("3. v_name -- Displays the value of v_name\n\n");
        printf("4. v_name = val_1 val_2 val_3\n"
            "-- Assigns v_name with the values val_1, val_2, val_3.\n"
            "-- All values must be sepparated by either a space or a comma.\n\n");
        printf("5. list -- Displays all active vectors in vector memory.\n\n"
               "6. clear -- Clears vector memory.\n\n"
               "7. load <path> -- Loads a .csv comma sepparated file. Merges with current vector memory.\n\n"
               "8. quit -- Terminates the program.\n\n"
               "9. help -- Displays this menu.\n\n\n");
        printf("Note: \n-- v_name must be 1 character in length\n"
                "-- all arguments must be sepparated by one space\n"
                "-- op must be either +, -, *, ., or x. "
                "These perform vector addition, subtraction, scalar multiplication,\n"
                " dot product, and cross product respectively.\n");
    } else {
        // Likely a vector name if none of the above conditions are met, but still need to validate
        int loc = findvect(code);

        if (loc != -1) {
            //valid vector, display vector values
            vect* v = getvect(loc);
            printf("%c: <%f, %f, %f>\n", v->name, v->a, v->b, v->c);
        } else {
            //Then there is an error with the code
            printf("Error: Unknown argument: %s\n", code);
            printf("Expected: list, help, clear, quit, or vect_name\n\n");
        }
    }

    return false;
}
