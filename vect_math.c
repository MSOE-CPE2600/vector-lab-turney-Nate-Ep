/**
* @file vect_math.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Computes vector math given 2 vectors defined in vect.c.
* @date 27 September 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include "vect.h"
#include <stdio.h>

/**
* @brief Adds two vects together.
* @param a The first vector.
* @param b The second vector.
* @return The sum of vectors a and b.
*/
vect add(vect *a, vect *b) {
    vect c;

    c.name = 'r';
    //add vector components
    c.a = a->a + b->a;
    c.b = a->b + b->b;
    c.c = a->c + b->c;

    return c;
}

/**
* @brief Subtracts two vects.
* @param a The first vector.
* @param b The second vector.
* @return The subtraction of b from a (ie. a - b).
*/
vect sub(vect *a, vect *b) {
    vect c;

    c.name = 'r';
    //add vector components
    c.a = a->a - b->a;
    c.b = a->b - b->b;
    c.c = a->c - b->c;

    return c;
}

/**
* @brief Performs scalar multiplication on vect a.
* @param mult The scalar factor.
* @param a The vect to scale.
* @return The scaled vect.
*/
vect scalar_mult(double mult, vect *v) {
    vect c;

    c.name = v->name;
    //add vector components
    c.a = v->a * mult;
    c.b = v->b * mult;
    c.c = v->c * mult;

    return c;
}