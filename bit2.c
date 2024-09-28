/*
 *     bit2.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     Purpose: Defines the Bit2 structure and its associated operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <bit2.h>
#include <bit.h>
#include <uarray.h>
#include <assert.h>

// Define the Bit2 structure
struct Bit2 {
    int rows;
    int columns;
    int size;
    UArray_T Bit_Array;  // Assuming Bit_Array is a UArray_T storing bits
};

// Function to create a new Bit2 structure
struct Bit2 *create_Bit2(int rows, int columns, int element_size) {
    struct Bit2 *newBit2 = (struct Bit2 *)malloc(sizeof(struct Bit2));
    
    if (newBit2 == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newBit2->rows = rows;
    newBit2->columns = columns;
    newBit2->size = element_size;
    newBit2->Bit_Array = UArray_new((rows * columns), element_size);  // Allocate bit array using UArray

    return newBit2;
}

// Function to map over the Bit2 structure in column-major order
void Bit2_map_col_major(Bit2 *Bit_2, void (*apply)(void *element)) {
    int rows = Bit_2->rows;
    int columns = Bit_2->columns;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            int index = j * columns + i;
            void *element = UArray_at(Bit_2->Bit_Array, index);
            apply(element);
        }
    }
}

// Function to map over the Bit2 structure in row-major order
void Bit2_map_row_major(Bit2 *Bit_2, void (*apply)(void *element)) {
    int rows = Bit_2->rows;
    int columns = Bit_2->columns;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = i * columns + j;
            void *element = UArray_at(Bit_2->Bit_Array, index);
            apply(element);
        }
    }
}
