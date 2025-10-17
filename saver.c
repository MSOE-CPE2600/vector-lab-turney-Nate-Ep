/**
* @file saver.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Defines functions to save vector memory as a .csv file.
* @date 16 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 27 October 2025
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vect.h"
#include "loader.h"

/**
 * @brief Saves vector memory to a .csv file
 * @param path The location of where to save the .csv file
 */
void save(char *path) {
    int v_mem_size = get_vmem_size();
    int path_len = strlen(path);
    vect *curr_vect;
    bool valid_ending = false;
    bool valid_path = validate_path_format(path, &valid_ending);
    
    if (valid_path) {

        if (!valid_ending) {
            add_csvtag(path);
        }

        FILE *ptr = fopen(path, "w");

        if (ptr != NULL) {
            for (int i = 0; i < v_mem_size; i++) {
                curr_vect = getvect(i);

                if (curr_vect != NULL) {
                    fprintf(ptr, "%c,%f,%f,%f\n", curr_vect->name, curr_vect->a, 
                        curr_vect->b, curr_vect->c);
                }
            }

            fclose(ptr);
        } else {
            printf("Invalid file path: %s", path);
        }
    } else {
        printf("Invalid path format: %s", path);
    }
}