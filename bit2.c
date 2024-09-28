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

// Example function implementations

Bit2_T Bit2_new(int width, int height) {
    Bit2_T bit2 = malloc(sizeof(*bit2));
    assert(bit2 != NULL);
    
    bit2->width = width;
    bit2->height = height;
    
    // Allocate 2D array
    bit2->array = malloc(width * sizeof(int *));
    for (int i = 0; i < width; i++) {
        bit2->array[i] = malloc(height * sizeof(int));
    }
    
    return bit2;
}

int Bit2_width(Bit2_T array) {
    return array->width;
}

int Bit2_height(Bit2_T array) {
    return array->height;
}

int Bit2_get(Bit2_T array, int row, int col) {
    return array->array[row][col];
}

int Bit2_put(Bit2_T array, int row, int col, int value) {
    int prev = array->array[row][col];
    array->array[row][col] = value;
    return prev;
}

void Bit2_map_col_major(Bit2_T array, void apply(int i, int j, Bit2_T a, int b, void *p1), void *cl) {
    for (int j = 0; j < array->height; j++) {
        for (int i = 0; i < array->width; i++) {
            apply(i, j, array, array->array[i][j], cl);
        }
    }
}

void Bit2_map_row_major(Bit2_T array, void apply(int i, int j, Bit2_T a, int b, void *p1), void *cl) {
    for (int i = 0; i < array->width; i++) {
        for (int j = 0; j < array->height; j++) {
            apply(i, j, array, array->array[i][j], cl);
        }
    }
}

void Bit2_free(Bit2_T *array) {
    for (int i = 0; i < (*array)->width; i++) {
        free((*array)->array[i]);
    }
    free((*array)->array);
    free(*array);
    *array = NULL;
}
