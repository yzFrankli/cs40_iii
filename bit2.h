/*
 *     bit2.h
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#ifndef BIT2_H
#define BIT2_H

#include <uarray.h>  // Include necessary libraries

// Define the Bit2 structure only once
typedef struct Bit2 {
    int rows;
    int columns;
    UArray_T Bit_Array;  // Use Hanson's UArray to store the bits
} Bit2;

// Function declarations
Bit2 *create_Bit2(int rows, int columns, int element_size);
void Bit2_map_row_major(Bit2 *bit2, void (*apply)(void *element));
void Bit_set(UArray_T array, int index, int value);
int Bit_get(UArray_T array, int index);

#endif /* BIT2_H */
