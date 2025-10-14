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

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include "vect.h"

static int v_mem_size = 10;
static vect *vect_mem;

/**
 * @brief Initializes vector memory by allocating memory for the array.
 */
void init_vect_mem() {
    vect_mem = malloc(v_mem_size * sizeof(vect));
}

/**
 * @brief Frees vector memory from allocation
 */
void free_vect_mem() {
    free(vect_mem);
}

/**
 * @brief Reallocates vector memory
 * @return Returns true if memory is reallocated, false otherwise.
 */
bool reallocate_vect_mem(int size) {
    vect* temp = realloc(vect_mem, size*sizeof(vect));
    //check if there was a place found for reallocation, if so, clear the new spaces
    if (temp != NULL) {
        int old_size = v_mem_size;
        vect_mem = temp;
        v_mem_size = size;
        clear(old_size);
        return true;
    } else { //otherwise, return false
        return false;
    }
}


/**
* @brief Adds a new vector to the storage array.
* @param new_vect The new vector to add to the array.
* @return 0 if the new vector was added. -1 if vector memory is full.
*/
int addvect(vect new_vect) {
    printf("Calling add: Size %d\n", v_mem_size);
    for (int i = 0; i < v_mem_size; ++i) {
        if (vect_mem[i].open == true) {
            vect_mem[i] = new_vect;
            vect_mem[i].open = false;
            
            return 0;
        }
    }
    
    //no open spaces found, reallocate
    if (reallocate_vect_mem(v_mem_size*2) == true) {
        //if reallocation was possible, attempt to add the new vector again
        return addvect(new_vect);
    } else {
        printf("Error: unable to reallocate vector memory.\nMemory is full.\n\n");
        return -1;
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
    for (int i = 0; i < v_mem_size; ++i) {
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
    if ((addr >= 0) && (addr < v_mem_size) && (vect_mem[addr].open == false)) {
        return &vect_mem[addr];
    } else {
        return NULL;
    }
}

void write_vect_data(int addr, vect v) {
    if (addr >= 0 && addr < v_mem_size) {
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
* @param start The starting location  to clear from.
*/
void clear(int start) {
    for (int i = start; i < v_mem_size; ++i) {
        vect_mem[i].open = true;
    }
}

/**
* @brief Returns v_mem_size
*/
int get_vmem_size(void) {
    return v_mem_size;
}

