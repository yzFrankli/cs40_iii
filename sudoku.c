/*
 *     sudoku.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "uarray2.h"

// Function to fill the Sudoku grid from input
void fill_array(FILE *input, UArray2_T arr) {
    int value;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(input, "%d", &value);
            int *element = (int *)UArray2_at(arr, i, j);
            *element = value;
        }
    }
}

// Function to validate each section (row, column, or 3x3 subgrid)
int validate_section(int arr[]) {
    int traversed[9] = {0};  // Array to track if numbers 1-9 are used

    for (int i = 0; i < 9; i++) {
        if (arr[i] < 1 || arr[i] > 9 || traversed[arr[i] - 1] != 0) {
            return 0;  // Invalid if number out of bounds or duplicate
        }
        traversed[arr[i] - 1] = 1;
    }
    return 1;
}

// Function to validate the Sudoku grid
int validate_grid(UArray2_T arr) {
    int test_array[9];

    // Check rows
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            test_array[j] = *(int *)UArray2_at(arr, i, j);
        }
        if (!validate_section(test_array)) {
            return 0;
        }
    }

    // Check columns
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            test_array[i] = *(int *)UArray2_at(arr, i, j);
        }
        if (!validate_section(test_array)) {
            return 0;
        }
    }

    // Check 3x3 subgrids
    for (int grid_row = 0; grid_row < 3; grid_row++) {
        for (int grid_col = 0; grid_col < 3; grid_col++) {
            int index = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    test_array[index++] = *(int *)UArray2_at(arr, grid_row * 3 + i, grid_col * 3 + j);
                }
            }
            if (!validate_section(test_array)) {
                return 0;
            }
        }
    }

    return 1;
}

// Main function
int main(int argc, char *argv[]) {
    assert(argc < 3);  // Ensure correct number of arguments

    FILE *sudoku;
    if (argc == 2) {
        sudoku = fopen(argv[1], "r");
        assert(sudoku != NULL);  // Ensure file opens correctly
    } else {
        sudoku = stdin;  // Read from standard input
    }

    // Create a new 9x9 UArray2_T array to store the Sudoku grid
    UArray2_T newArr = UArray2_new(9, 9, sizeof(int));

    // Fill the array with input values
    fill_array(sudoku, newArr);

    // Validate the Sudoku grid
    int is_valid = validate_grid(newArr);

    // Print result
    if (is_valid) {
        printf("The Sudoku puzzle is valid!\n");
    } else {
        printf("The Sudoku puzzle is invalid!\n");
    }

    // Free memory and close file
    UArray2_free(&newArr);
    if (argc == 2) {
        fclose(sudoku);
    }

    return 0;
}

