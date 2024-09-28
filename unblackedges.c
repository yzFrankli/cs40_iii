#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bit2.h"

typedef struct {
    int row;
    int col;
} Coordinate;

#define MAX_BLACK_SQUARES 1000

Coordinate black_squares[MAX_BLACK_SQUARES];
int black_square_count = 0;
int current_row;
int current_col;
Bit2 *pbm_array;

// Function to check if a black square is adjacent to any squares in the array
int is_adjacent(Coordinate *black_squares, int count, int row, int col) {
    for (int i = 0; i < count; i++) {
        int r = black_squares[i].row;
        int c = black_squares[i].col;

        if ((abs(r - row) <= 1) && (abs(c - col) <= 1)) {
            return 1;  // Found an adjacent black square
        }
    }
    return 0;
}

// Apply function for row-major mapping, checking for adjacent black squares
void apply_row_major(void *element) {
    // Access the global variables for row and column
    int row = current_row;
    int col = current_col;

    if (*(int *)element == 1) {  // If this square is black
        if (is_adjacent(black_squares, black_square_count, row, col)) {
            black_squares[black_square_count++] = (Coordinate){row, col};
            Bit_set(pbm_array->Bit_Array, row * pbm_array->columns + col, 0);  // Turn white
        }
    }
}

// Function to process the perimeter of the PBM array
void process_perimeter(Bit2 *bit2) {
    int rows = bit2->rows;
    int columns = bit2->columns;

    // Process the top and bottom rows
    for (int j = 0; j < columns; j++) {
        if (Bit_get(bit2->Bit_Array, 0 * columns + j) == 1) {
            black_squares[black_square_count++] = (Coordinate){0, j};
            Bit_set(bit2->Bit_Array, 0 * columns + j, 0);  // Turn white
        }
        if (Bit_get(bit2->Bit_Array, (rows - 1) * columns + j) == 1) {
            black_squares[black_square_count++] = (Coordinate){rows - 1, j};
            Bit_set(bit2->Bit_Array, (rows - 1) * columns + j, 0);  // Turn white
        }
    }

    // Process the left and right columns
    for (int i = 0; i < rows; i++) {
        if (Bit_get(bit2->Bit_Array, i * columns + 0) == 1) {
            black_squares[black_square_count++] = (Coordinate){i, 0};
            Bit_set(bit2->Bit_Array, i * columns + 0, 0);  // Turn white
        }
        if (Bit_get(bit2->Bit_Array, i * columns + (columns - 1)) == 1) {
            black_squares[black_square_count++] = (Coordinate){i, columns - 1};
            Bit_set(bit2->Bit_Array, i * columns + (columns - 1), 0);  // Turn white
        }
    }
}

// Function to read the PBM file into the Bit2 structure
void read_pbm(FILE *input, Bit2 *bit2) {
    for (int i = 0; i < bit2->rows; i++) {
        for (int j = 0; j < bit2->columns; j++) {
            int value;
            fscanf(input, "%d", &value);
            Bit_set(bit2->Bit_Array, i * bit2->columns + j, value);
        }
    }
}

// Function to print the corrected PBM content to stdout
void print_pbm(Bit2 *bit2) {
    int rows = bit2->rows;
    int columns = bit2->columns;

    printf("P1\n");
    printf("%d %d\n", columns, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int value = Bit_get(bit2->Bit_Array, i * columns + j);
            printf("%d ", value);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    assert(argc == 2);

    FILE *input = fopen(argv[1], "r");
    assert(input != NULL);

    int rows, columns;
    fscanf(input, "%d %d", &columns, &rows);

    pbm_array = create_Bit2(rows, columns, sizeof(int));

    read_pbm(input, pbm_array);
    process_perimeter(pbm_array);

    Bit2_map_row_major(pbm_array, apply_row_major);

    print_pbm(pbm_array);

    free(pbm_array);
    fclose(input);

    return 0;
}
