/**
* @file vect.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Defines the vector struct and typedef. Controls an array of 10 vectors.
* @date 27 September 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "vect.h"

static vect vect_mem[10];
static const int V_MEM_SIZE = 10;

/**
* @brief Adds a new vector to the storage array.
* @param new_vect The new vector to add to the array.
* @return 0 if the new vector was added. -1 if vector memory is full.
*/
int addvect(vect new_vect) {
    for (int i = 0; i < V_MEM_SIZE; ++i) {
        if (vect_mem[i].open == true) {
            vect_mem[i] = new_vect;
            vect_mem[i].open = false;
            return 0;
        }
    }

    return -1;
}

/**
* @brief Removes a vector from the storage array.
* @param name The name of the vector to remove.
* @return True if remove was sucsessful, false otherwise.
*/
bool rmvvect(char *name) {
    int loc = findvect(name);
    if (loc != -1) {
        vect_mem[loc].open = true;
        return true;
    } else {
        return false;
    }
}

/**
* @brief Searches the vector memory for a vector with the given name.
* @param name The name of the vector to search for.
* @return -1 if no vector with the given name found.
* Otherwise, return the vector mem location of the specified vector.
*/
int findvect(char *name) {
    for (int i = 0; i < V_MEM_SIZE; ++i) {
        if (vect_mem[i].name == *name) {
            return i;
        }
    }
    return -1;
}

/**
* @brief Returns the vector at the specified vector mem address.
* @param addr The address of the vector to retrieve.
* @return The pointer to the vector at the given address. NULL is returned if
* the address is invalid, or no vector found.
*/
vect* getvect(int addr) {
    if ((addr >= 0) && (addr < V_MEM_SIZE) && (vect_mem[addr].open == false)) {
        return &vect_mem[addr];
    } else {
        return NULL;
    }
}

void write_vect_data(int addr, vect v) {
    if (addr >= 0 && addr < V_MEM_SIZE) {
        vect *vmem = &vect_mem[addr];
        vmem->a = v.a;
        vmem->b = v.b;
        vmem->c = v.c;
        vmem->open = false;

    } else {
        printf("Error writing vector data: Invalid address of %d\n", addr);
    }
}

/**
* @brief Clears the vector memory.
*/
void clear() {
    for (int i = 0; i < V_MEM_SIZE; ++i) {
        vect_mem[i].open = true;
    }
}

/**
* @brief Returns V_MEM_SIZE
*/
int get_vmem_size(void) {
    return V_MEM_SIZE;
}

