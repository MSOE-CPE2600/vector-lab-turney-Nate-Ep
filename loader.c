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
#include "op_helper.h"

void add_csvtag(char *path);
bool validate_path_format(char *path, bool *valid_ending);
void load_vect(char *input, const int len);

/**
 * @brief Loads a .csv comma sepparated file into vector memory.
 * Prints an error if the function is given an invalid path or file data.
 * @param path The path of the file to load (relative or absolute).
 */
void load_file(char *path) {
    //FIXME Error loading saved files
    const int INPUT_LEN = 200;
    char input[INPUT_LEN];
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
            while (fgets(input, INPUT_LEN-1, ptr)!= NULL) {
                input[INPUT_LEN] = '\0'; //set last char to null
                load_vect(input, INPUT_LEN);
            }
            fclose(ptr);
        } else {
            printf("FALURE: FILE NOT OPENED\nPlease check the file path.\n\n");
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
 * @brief Attempts to load an input string as a vector. Displays an error if invalid format.
 * @param input The input string to attempt to load.
 * @param len The length of the input string.
 */
void load_vect(char *input, const int len) {
    char *v_name = strtok(input, ",");
    char *val_1 = strtok(NULL, ",");
    char *val_2 = strtok(NULL, ",");
    char *val_3 = strtok(NULL, ",");
    char *extra = strtok(NULL, ",");

    //check if val_3 is a valid char, and make sure there is no extra characters
    if ((extra == NULL && val_3 != NULL && *val_3 != '\0' && *val_3 != '\n' && *val_3 != '\r') || 
            (extra != NULL && *extra == '\0')) {
        //if all conditions are met, load and store the new vector

        // Remove BOM if v_name starts with it
        if ((unsigned char)v_name[0] == 0xEF &&
            (unsigned char)v_name[1] == 0xBB &&
            (unsigned char)v_name[2] == 0xBF) {
            v_name += 3;
        }

        //store vector
        str_op(v_name, val_1, val_2, val_3);

    } else {
        //otherwise, print an error to the user telling them what was skipped
        printf("Error: Invalid input: %s,%s,%s,%s\nSkipping...\n\n", 
            input, val_1, val_2, val_3);
    }
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