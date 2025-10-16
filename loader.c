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
vect parse_vect(char *input, const int len);

/**
 * @brief Loads a .csv comma sepparated file into vector memory.
 * Prints an error if the function is given an invalid path or file data.
 * @param path The path of the file to load (relative or absolute).
 */
void load_file(char *path) {
    const int INPUT_LEN = 20;
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
            // TODO LOAD FILE INTO VECTOR MEMROY
            fgets(input, INPUT_LEN-1, ptr);
            input[INPUT_LEN] = '\0'; //set last char to null
            printf("Input: %s", input);
            parse_vect(input, INPUT_LEN);
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
 * @brief Parses an input string into a vector. Displays an error if invalid format.
 * @param input The input string to parse.
 * @param len The length of the input string.
 */
vect parse_vect(char *input, const int len) {
    //int num_args = num_vals(input, len);

    char *v_name = strtok(input, ",");
    char *val_1 = strtok(NULL, ",");
    char *val_2 = strtok(NULL, ",");
    char *val_3 = strtok(NULL, ",");
    char *extra = strtok(NULL, ",");
    vect ret;

    //FIXME Error detecting if there is a 3rd value or not
    //Regardless of if a value exists in a row, it will at least be a ',' for each column in the entire data

    //TODO Ideas:
    // If extra != Null, invalid
    // otherwise, leave value parsing up to the float parser?
    //if v_name or val1 or val2 or val3 are null, invalid
    //make use of the store-op function
    if (extra == NULL) {
        printf("v_name: %s\n", v_name);
        printf("len: %ld\n\n", strlen(v_name));

        // Remove BOM if v_name starts with it
        if ((unsigned char)v_name[0] == 0xEF &&
            (unsigned char)v_name[1] == 0xBB &&
            (unsigned char)v_name[2] == 0xBF) {
            v_name += 3;
        }

        //FIXME Start of .csv file contains UTF-8 BOM Encoding
        printf("val_1: %s\n", val_1);
        printf("val_2: %s\n", val_2);
        printf("val_3: %s\n", val_3);
        str_op(v_name, val_1, val_2, val_3);
    } else { //FIXME Extra can not be null but still hold no value
        printf("Error: too may values input: skipping\n");
    }
    return ret;
}

// /**
//  * @brief Counts the number of values sepparated by a comma in a given input string.
//  * @param input The input string to count.
//  * @param len The length of the input.
//  */
// int num_vals(char *input, int len) {
//     int count = 0;
//     for (int i = 0; i < len; ++i) {
//         if (*(input+i) == ',') {
//             count += 1;
//         }
//     }

//     return count;
// }

/**
 * @brief Adds a .csv ending to a path.
 * @param path The path to add the .csv tag to.
 */
void add_csvtag(char *path) {
    //add the .csv ending to the user given path
    replace(path, '\n', '.');
    strcat(path, "csv");
}