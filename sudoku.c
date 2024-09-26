/*
 *     sudoku.h
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 *     
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "uarray2.h"
// #include "pnmrdr.h"

int main(int argc, char *argv[]) {
    assert(argc < 3);
    FILE *sudoku;
    if (argc == 2) {
        sudoku = fopen(argv[1], "r");
        assert(sudoku != NULL);
    } else {
        sudoku = stdin;
    }

    UArray2_T newArr = UArray2_new(9, 9, 4);
    // fill the array


    int test_array[9];
    int is_valid = 1;



    return 0;
}