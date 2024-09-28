/*
 *     uarray2.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "uarray.h"

// Definition of the UArray2_T structure
struct UArray2_T {
    int width;
    int height;
    int element_size;
    UArray_T array;  // 1D array to hold the 2D array data
};

// Create a new 2D array with the given width, height, and element size
UArray2_T UArray2_new(int width, int height, int element_size) {
    assert(width > 0 && height > 0 && element_size > 0);
    
    UArray2_T uarray2 = malloc(sizeof(*uarray2));
    assert(uarray2 != NULL);

    uarray2->width = width;
    uarray2->height = height;
    uarray2->element_size = element_size;
    uarray2->array = UArray_new(width * height, element_size);

    return uarray2;
}

// Free the 2D array
void UArray2_free(UArray2_T *uarray2) {
    assert(uarray2 != NULL && *uarray2 != NULL);

    UArray_free(&(*uarray2)->array);
    free(*uarray2);
    *uarray2 = NULL;
}

// Get a pointer to the element at (i, j)
void *UArray2_at(UArray2_T uarray2, int i, int j) {
    assert(uarray2 != NULL);
    assert(i >= 0 && i < uarray2->width);
    assert(j >= 0 && j < uarray2->height);

    return UArray_at(uarray2->array, i * uarray2->height + j);  // Access 1D array element
}

// Get the width of the 2D array
int UArray2_width(UArray2_T uarray2) {
    return uarray2->width;
}

// Get the height of the 2D array
int UArray2_height(UArray2_T uarray2) {
    return uarray2->height;
}

// Get the size of elements stored in the array
int UArray2_size(UArray2_T uarray2) {
    return uarray2->element_size;
}

// Apply a function to every element in the array in row-major order
void UArray2_map_row_major(UArray2_T uarray2, void (*apply)(int i, int j, UArray2_T uarray2, void *p1, void *p2), void *cl) {
    assert(uarray2 != NULL);
    
    for (int i = 0; i < uarray2->width; i++) {
        for (int j = 0; j < uarray2->height; j++) {
            apply(i, j, uarray2, UArray2_at(uarray2, i, j), cl);
        }
    }
}

// Apply a function to every element in the array in column-major order
void UArray2_map_col_major(UArray2_T uarray2, void (*apply)(int i, int j, UArray2_T uarray2, void *p1, void *p2), void *cl) {
    assert(uarray2 != NULL);
    
    for (int j = 0; j < uarray2->height; j++) {
        for (int i = 0; i < uarray2->width; i++) {
            apply(i, j, uarray2, UArray2_at(uarray2, i, j), cl);
        }
    }
}
