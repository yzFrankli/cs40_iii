/*
 *     uarray2.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include <assert.h>

// Update all references to UArray2 to UArray2_T
UArray2_T *create_Uarray2(int rows, int columns, int element_size) {
    UArray2_T *newUArray2 = (UArray2_T *)malloc(sizeof(UArray2_T));
    
    if (newUArray2 == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    newUArray2->rows = rows;
    newUArray2->columns = columns;
    newUArray2->size = element_size;
    newUArray2->UArray = UArray_new((rows * columns), element_size);

    return newUArray2;
}

void UArray2_map_col_major(UArray2_T *U_Array2, void (*apply)(void *element)) {
    int rows = U_Array2->rows;
    int columns = U_Array2->columns;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            int index = j * columns + i;
            void *element = UArray_at(U_Array2->UArray, index);
            apply(element);
        }
    }
}

void UArray2_map_row_major(UArray2_T *U_Array2, void (*apply)(void *element)) {
    int rows = U_Array2->rows;
    int columns = U_Array2->columns;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = i * columns + j;
            void *element = UArray_at(U_Array2->UArray, index);
            apply(element);
        }
    }
}

void *UArray2_at(UArray2_T *array, int row, int column) {
    assert(array != NULL);
    assert(row >= 0 && row < array->rows);
    assert(column >= 0 && column < array->columns);
    
    int index = row * array->columns + column;
    return UArray_at(array->UArray, index);
}
