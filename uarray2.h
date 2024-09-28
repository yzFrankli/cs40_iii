/*
 *     uarray2.h
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#ifndef _UARRAY2_T_
#define _UARRAY2_T_

#include <uarray.h>

// Change the struct name to UArray2_T
typedef struct UArray2_T {
    int rows;
    int columns;
    int size;
    UArray_T UArray;
} UArray2_T;  // Alias 'UArray2_T' for 'struct UArray2_T'

// Function declarations
UArray2_T *create_Uarray2(int rows, int columns, int element_size);
void UArray2_map_col_major(UArray2_T *U_Array2, void (*apply)(void *element));
void UArray2_map_row_major(UArray2_T *U_Array2, void (*apply)(void *element));
void *UArray2_at(UArray2_T *array, int row, int column);

#endif /* _UARRAY2_T_ */
