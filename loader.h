/**
* @file loader.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Describes functions to load .csv files to merge with vector memory.
* @date 7 October 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#ifndef LOADER_H
#define LOADER_H

bool validate_path_format(char *path);

void add_csvtag(char *path);

#endif