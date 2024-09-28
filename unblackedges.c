/*
 *     unblackedges.c
 *     By Sid & Frank
 *     9/24/2024
 *     CS40 HW2: iii
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bit2.h"


void read_pbm(FILE *input, Bit2 *pbm_array) {
    for (int i = 0; i < pbm_array->rows; i++) {
        for (int j = 0; j < pbm_array->columns; j++) {
            int value;
            fscanf(input, "%d", &value);
            if (value == 1) {  // Replacing BLACK with 1
                Bit_set(pbm_array->Bit_Array, i * pbm_array->columns + j, 1);
            }
        }
    }
}


void process_edges(Bit2 *pbm_array) {
    int rows = pbm_array->rows;
    int columns = pbm_array->columns;

    for (int j = 0; j < columns; j++) {
        if (Bit_get(pbm_array->Bit_Array, 0 * columns + j) == 1) {
            flood_fill(pbm_array, 0, j);
        }
        if (Bit_get(pbm_array->Bit_Array, (rows - 1) * columns + j) == 1) {
            flood_fill(pbm_array, rows - 1, j);
        }
    }

    for (int i = 0; i < rows; i++) {
        if (Bit_get(pbm_array->Bit_Array, i * columns + 0) == 1) {
            flood_fill(pbm_array, i, 0);
        }
        if (Bit_get(pbm_array->Bit_Array, i * columns + (columns - 1)) == 1) {
            flood_fill(pbm_array, i, columns - 1);
        }
    }
}

void flood_fill(Bit2 *pbm_array, int row, int col) {
    int rows = pbm_array->rows;
    int columns = pbm_array->columns;

    if (row < 0 || row >= rows || col < 0 || col >= columns || 
        Bit_get(pbm_array->Bit_Array, row * columns + col) == 0) {  // Replacing WHITE with 0
        return;
    }

    Bit_set(pbm_array->Bit_Array, row * columns + col, 0);  // Set to 0 (WHITE)

    // Recursive flood-fill for all directions
    flood_fill(pbm_array, row - 1, col);   // Up
    flood_fill(pbm_array, row + 1, col);   // Down
    flood_fill(pbm_array, row, col - 1);   // Left
    flood_fill(pbm_array, row, col + 1);   // Right
    flood_fill(pbm_array, row - 1, col - 1); // Diagonal up-left
    flood_fill(pbm_array, row - 1, col + 1); // Diagonal up-right
    flood_fill(pbm_array, row + 1, col - 1); // Diagonal down-left
    flood_fill(pbm_array, row + 1, col + 1); // Diagonal down-right
}


void write_pbm(FILE *output, Bit2 *pbm_array) {
    int rows = pbm_array->rows;
    int columns = pbm_array->columns;

    fprintf(output, "P1\n");
    fprintf(output, "%d %d\n", columns, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int value = Bit_get(pbm_array->Bit_Array, i * columns + j);
            fprintf(output, "%d ", value);
        }
        fprintf(output, "\n");
    }
}


int main(int argc, char *argv[]) {
    assert(argc == 3);

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    assert(input != NULL);
    assert(output != NULL);

    int rows, columns;
    fscanf(input, "%d %d", &columns, &rows);

    Bit2 *pbm_array = create_Bit2(rows, columns);

    read_pbm(input, pbm_array);
    process_edges(pbm_array);
    write_pbm(output, pbm_array);

    free(pbm_array); 

    fclose(input);
    fclose(output);

    return 0;
}
