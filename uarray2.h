/*
 *     uarray2.h
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     
 */
#ifndef _UARRAY2_T_
#define _UARRAY2_T_


#include <uarray.h>

struct UArray2 {
    int rows;
    int columns;
    int size;
    UArray_T UArray;
};

struct UArray2 *create_Uarray2(int rows, int columns, int element_size);
void UArray2_map_col_major(UArray_T *U_Array2, void (*apply)(void *element));
void UArray2_map_row_major(UArray_T *U_Array2, void (*apply)(void *element));


#endif /* _UARRAY2_T_ */