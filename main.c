/**
* @file main.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief A mini MATLAB program to do simple vector calculations.
* @date 7 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vect.h"
#include "io_helper.h"

int main(int argc, char *argv[]) {
    char input[100];
    char *arg1;
    char *arg2;
    char *arg3;
    char *arg4;
    char *arg5;
    char *arg6;
    bool quit = false;

    //initialize and clear vectors (Set all vect mem locations to open)
    clear();

    do {
        //make sure none of the arguments input are blank
        printf("miniMATLAB> ");
        fgets(input, 99, stdin);

        //parse arguments
        arg1 = strtok(input, " ");
        arg2 = strtok(NULL, " ");
        arg3 = strtok(NULL, " ");
        arg4 = strtok(NULL, " ");
        arg5 = strtok(NULL, " ");
        arg6 = strtok(NULL, " ");

        //FIXME, TAKE IN ALL ARGUMENTS, IF ',' replace with " ", then parse

        if (arg6 == NULL) { //check if the number of arguments is valid (5 args max)
            if (arg5 != NULL) {
                //Then there must be some kind of opperation where the result is stored.
                //call store opperation, unless the equal symbol got messed up
                if (strcmp(arg2, "=") == 0) {
                    str_op(arg1, arg3, arg4, arg5);
                } else {
                    //error with equal sign
                    printf("Error: Expecting '=' for arg2 | Got: %s\n", arg2);
                }
            }  else if (arg3 != NULL && strcmp(arg2, "=") == 0) {
                //a = b
                int ret_loc = findvect(arg1);
                int arg_loc = findvect(arg3);
                int len_arg1 = 1;//strlen(arg1);

                if (ret_loc == -1 && len_arg1 == 1) {
                    vect ret;
                    ret.name = *arg1;
                    if (addvect(ret) == -1) {
                        //memory full
                        printf("Error: memory full, cannot perform opperation.\n");
                    } else {
                        ret_loc = findvect(arg1);
                    }
                } else if (len_arg1 > 1){
                    //invalid name for return
                    printf("Invalid vector name: %s Expected v_name of length 1\n", arg1);
                }

                if (ret_loc != -1 && arg_loc != -1) {
                    vect *v = getvect(arg_loc);
                    write_vect_data(ret_loc, *v);
                } else {
                    //error in finding vector
                    printf("Error: Invalid argument '%s' Expected: v_name", (ret_loc == -1) ? arg1 : arg2);
                }
            } else if (arg3 != NULL) {
                //then must be an v1 op v2
                display_op(arg1, arg2, arg3);
            } else {
                //one argument command, check list of potential display commands.
                quit = display(arg1);
            }
        } else {
            //print error
            printf("ERROR: Too many arguments, expected 5 arguments maximum.\n");
        }
       
    } while (!quit);
    
    return 0;
}



/* Arg 1 potential values:
vect_name, list, help, clear, quit, scalar factor
*/

/* Arg 2 potential values:
NULL, =, +, -, *, int
Note: an opperator in arg2 indicates the result is displayed not stored.
*/

/* Arg 3 potential values:
vect_name, NULL, scalar factor int
*/

/* Arg 4 potential values:
NULL, +, -, *, int
*/

/* Arg 5 potential values:
NULL, vect_name, int
*/