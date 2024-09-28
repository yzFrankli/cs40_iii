/*
 *     bit2.h
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#ifndef _BIT2_H_
#define _BIT2_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <bit.h>

// Define the Bit2 structure
typedef struct Bit2 {
    int rows;
    int columns;
    int size;
    Bit_T Bit_Array;  // Assuming Bit_T is used to store bits
} Bit2;

// Function declarations
Bit2 *create_Bit2(int rows, int columns, int element_size);
void Bit2_map_col_major(Bit2 *Bit_2, void (*apply)(void *element));
void Bit2_map_row_major(Bit2 *Bit_2, void (*apply)(void *element));

#endif /* _BIT2_H_ */
