/*
 *     bit2.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     Purpose: Defines the Bit2 structure and its associated operations
 */

#include "bit2.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <uarray.h>

// Function to create a new Bit2 2D array
Bit2 *create_Bit2(int rows, int columns, int element_size) {
    printf("Creating Bit2 with %d rows and %d columns, element size: %d\n", rows, columns, element_size);
    Bit2 *newBit2 = malloc(sizeof(Bit2));
    assert(newBit2 != NULL);  // Ensure memory allocation was successful

    newBit2->rows = rows;
    newBit2->columns = columns;
    newBit2->Bit_Array = UArray_new(rows * columns, element_size);  // Create a UArray of size rows * columns
    assert(newBit2->Bit_Array != NULL);  // Ensure UArray allocation was successful

    return newBit2;
}

// Function to map over the array in row-major order
void Bit2_map_row_major(Bit2 *bit2, void (*apply)(void *element)) {
    for (int i = 0; i < bit2->rows; i++) {
        for (int j = 0; j < bit2->columns; j++) {
            int index = i * bit2->columns + j;
            void *element = UArray_at(bit2->Bit_Array, index);
            apply(element);
        }
    }
}

// Function to set a bit in the array
void Bit_set(UArray_T array, int index, int value) {
    printf("Setting index %d with value %d\n", index, value);
    assert(index >= 0 && index < UArray_length(array));  // Ensure index is within bounds
    int *element = UArray_at(array, index);
    *element = value;
}

// Function to get a bit from the array
int Bit_get(UArray_T array, int index) {
    printf("Getting value from index %d\n", index);
    assert(index >= 0 && index < UArray_length(array));  // Ensure index is within bounds
    int *element = UArray_at(array, index);
    return *element;
}
