/*
 *     bit2.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     Purpose: Defines the Bit2 structure and its associated operations
 */

#include <stdlib.h>
#include <assert.h>
#include "bit2.h"

struct Bit2_T {
    int width;
    int height;
    int **array;  // 2D array of bits (can store 1 or 0)
};

// Create a new Bit2 array
Bit2_T Bit2_new(int width, int height) {
    assert(width > 0 && height > 0);  // Ensure valid dimensions

    Bit2_T bit2 = malloc(sizeof(*bit2));
    assert(bit2 != NULL);  // Ensure the structure was allocated

    bit2->width = width;
    bit2->height = height;

    // Allocate the 2D array
    bit2->array = malloc(height * sizeof(int *));  // Allocate for each row
    assert(bit2->array != NULL);  // Ensure row pointers are allocated

    for (int i = 0; i < height; i++) {
        bit2->array[i] = malloc(width * sizeof(int));  // Allocate each row
        assert(bit2->array[i] != NULL);  // Ensure allocation succeeded

        // Initialize all values to 0
        for (int j = 0; j < width; j++) {
            bit2->array[i][j] = 0;  // Default to 0
        }
    }

    return bit2;
}

// Get the width of the Bit2 array
int Bit2_width(Bit2_T array) {
    return array->width;
}

// Get the height of the Bit2 array
int Bit2_height(Bit2_T array) {
    return array->height;
}

// Get the value at a specific position in the Bit2 array
int Bit2_get(Bit2_T array, int row, int col) {
    assert(array != NULL);
    assert(row >= 0 && row < array->height);  // Check row bounds
    assert(col >= 0 && col < array->width);   // Check column bounds
    return array->array[row][col];
}

// Put a value at a specific position in the Bit2 array
int Bit2_put(Bit2_T array, int row, int col, int value) {
    int prev = array->array[row][col];
    array->array[row][col] = value;
    return prev;
}

// Free the Bit2 array
void Bit2_free(Bit2_T *array) {
    for (int i = 0; i < (*array)->height; i++) {
        free((*array)->array[i]);  // Free each row
    }
    free((*array)->array);  // Free the array of row pointers
    free(*array);  // Free the struct itself
    *array = NULL;
}

// Row-major mapping function
void Bit2_map_row_major(Bit2_T array, void apply(int i, int j, Bit2_T a, int value, void *p1), void *p1) {
    for (int i = 0; i < Bit2_height(array); i++) {
        for (int j = 0; j < Bit2_width(array); j++) {
            apply(i, j, array, Bit2_get(array, i, j), p1);
        }
    }
}

// Column-major mapping function
void Bit2_map_col_major(Bit2_T array, void apply(int i, int j, Bit2_T a, int value, void *p1), void *p1) {
    for (int j = 0; j < Bit2_width(array); j++) {
        for (int i = 0; i < Bit2_height(array); i++) {
            apply(i, j, array, Bit2_get(array, i, j), p1);
        }
    }
}
