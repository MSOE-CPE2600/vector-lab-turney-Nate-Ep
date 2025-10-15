/**
* @file loader.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Defines functions to load .csv files to merge with vector memory.
* @date 7 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "vect.h"
#include "io_helper.h"

void add_csvtag(char *path);
bool validate_path_format(char *path, bool *valid_ending);

/**
 * @brief Loads a .csv comma sepparated file into vector memory.
 * Prints an error if the function is given an invalid path or file data.
 * @param path The path of the file to load (relative or absolute).
 */
void load_file(char *path) {
    bool valid_ending = false;
    bool valid_format;
    FILE *ptr;

    valid_format = validate_path_format(path, &valid_ending);

    if (valid_format && !valid_ending) {
        add_csvtag(path);
    }

    if (valid_format && valid_ending) {
        //remove '\n' char at end from user input, end with null terminator
        int length = strlen(path);
        *(path+length-1) = '\0';
    }
    
    if (valid_format) {
        ptr = fopen(path, "r");
        if (ptr != NULL) {
            // TODO LOAD FILE INTO VECTOR MEMROY
        } else {
            printf("FALURE: FILE NOT OPENED\n");
        }
    }

}

/**
 * @brief Validates the user given path format to the specified .csv file
 * @param path The path to validate. Null terminated.
 * @param valid_ending Indicates whether the given path has a valid .csv ending or not.
 */
bool validate_path_format(char *path, bool *valid_ending) {
    int i = 0;
    char curr_char;
    bool valid = true;
    int length = strlen(path);

    *valid_ending = false;

    do {
        curr_char = *(path + i);
        
        if (curr_char == ' ') {
            valid = false;
        } else if (curr_char == '.' && (i > 1 && i != (length - 5))) {
            //there should be no dots after the first 2 chars
            //there may be one dot near the end to indicate .csv
            valid = false;
        } else if (curr_char == '.' && i == (length - 5)) {
            if (strcmp(path+i, ".csv\n") == 0) {
                //valid ending, end loop
                *valid_ending = true;
                curr_char = '\0'; //this will skip the end and break the loop.
            } else {
                valid = false; //invalid ending
            }
        }

        ++i;
    } while (curr_char != '\0'); //loop while not at null terminator

    if (!valid) {
        printf("Error: Invalid path: %s\n", path);
    } 

    return valid;
}

/**
 * @brief Adds a .csv ending to a path.
 * @param path The path to add the .csv tag to.
 */
void add_csvtag(char *path) {
    //add the .csv ending to the user given path
    replace(path, '\n', '.');
    strcat(path, "csv");
}