/**
* @file loader.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Describes functions to load .csv files to merge with vector memory.
* @date 16 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 27 October 2025
*
*/

#ifndef LOADER_H
#define LOADER_H

void load_file(char *path);

bool validate_path_format(char *path, bool *valid_ending);

void add_csvtag(char *path);

#endif