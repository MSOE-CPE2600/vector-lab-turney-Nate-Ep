/**
* @file vect.h
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Describes the vector functions.
* @date 27 September 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include <stdbool.h>

#ifndef VECT_H
#define VECT_H
typedef struct {
    //vector name
    char name; 
    //each vector has 3 magnitudes
    double a, b, c;
    bool open;
} vect;

int addvect(vect new_vect);

bool rmvvect(char *name);

int findvect(char *name);

vect* getvect(int addr);

void clear(int start);

int get_vmem_size(void);

void write_vect_data(int addr, vect v);

void free_vect_mem();

void init_vect_mem();

#endif