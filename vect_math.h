/**
* @file main.c
* @author Nathan Eppler <epplern@msoe.edu>
* @brief Describes the vector math functions.
* @date 27 September 2025
* 
* Course: CPE2600
* Section: 111
* Due: 10 October 2025
*
*/

#include "vect.h"

#ifndef V_MATH
#define V_MATH

vect add(vect *a, vect *b);

vect sub(vect *a, vect *b);

vect scalar_mult(double mult, vect *a);

float dot_product(vect *a, vect *b);

vect cross_product(vect *a, vect *b);

#endif 