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

// Use typedef to avoid having to use 'struct' every time
typedef struct UArray2 {
    int rows;
    int columns;
    int size;
    UArray_T UArray;
} UArray2;  // This creates an alias 'UArray2' for 'struct UArray2'

// Function declarations
UArray2 *create_Uarray2(int rows, int columns, int element_size);
void UArray2_map_col_major(UArray2 *U_Array2, void (*apply)(void *element));  // Changed to use UArray2 alias
void UArray2_map_row_major(UArray2 *U_Array2, void (*apply)(void *element));  // Changed to use UArray2 alias

#endif /* _UARRAY2_T_ */
