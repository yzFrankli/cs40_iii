/*
 *     bit2.h
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     
 */


#ifndef _BIT2_H_
#define _BIT2_H_

#include <stdio.h>
#include "bit.h"

struct Bit2 {
    int rows;
    int columns;
    int size;
    Bit_T Bit_Array;
};



struct Bit2 *create_Bit2(int rows, int columns, int element_size);
void Bit2_map_col_major(Bit2 *Bit_2, void (*apply)(void *element));
void UArray2_map_row_major(Bit2 *Bit_2, void (*apply)(void *element));



#endif 