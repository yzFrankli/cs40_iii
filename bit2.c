/*
 *     bit2.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     purpose
 */


#include <stdio.h>
#include <stdlib.h>
#include <bit2.h>
#include <bit.h>
#include <uarray.h>
#include <assert.h>
 



struct Bit2 *create_Bit2(int rows, int columns, int element_size) {
    struct Bit2 *newBit2 = (struct Bit2 *)malloc(sizeof(struct Bit2_free));
    
    if (newBit2 == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    newBit2->rows = rows;
    newBit2->columns = columns;
    newBit2->size = element_size;
    newBit2->Bit_Array = Bit_new((rows*columns), element_size);

    return newBit2;
}


void Bit2_map_col_major(Bit2 *Bit_2, void (*apply)(void *element)) {
    rows = Bit_2->rows;
    columns = Bit_2->columns;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            int index = j * columns + i;
            void *element = UArray_at(Bit_2->Bit_Array, index);
            apply(element);
        }
    }
}



void UArray2_map_row_major(Bit2 *Bit_2, void (*apply)(void *element)) {
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
