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
Bit2_T pbm_array;

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
void apply_row_major(void *element, void *cl, int i, int j) {
    Bit2_T bit2 = (Bit2_T)cl;
    int value = *(int *)element;

    if (value == 1) {  // If this square is black
        if (is_adjacent(black_squares, black_square_count, i, j)) {
            black_squares[black_square_count++] = (Coordinate){i, j};
            Bit2_put(bit2, i, j, 0);  // Turn white
        }
    }
}

// Function to process the perimeter of the PBM array
void process_perimeter(Bit2_T bit2) {
    int rows = Bit2_height(bit2);
    int columns = Bit2_width(bit2);

    // Process the top and bottom rows
    for (int j = 0; j < columns; j++) {
        if (Bit2_get(bit2, 0, j) == 1) {
            black_squares[black_square_count++] = (Coordinate){0, j};
            Bit2_put(bit2, 0, j, 0);  // Turn white
        }
        if (Bit2_get(bit2, rows - 1, j) == 1) {
            black_squares[black_square_count++] = (Coordinate){rows - 1, j};
            Bit2_put(bit2, rows - 1, j, 0);  // Turn white
        }
    }

    // Process the left and right columns
    for (int i = 0; i < rows; i++) {
        if (Bit2_get(bit2, i, 0) == 1) {
            black_squares[black_square_count++] = (Coordinate){i, 0};
            Bit2_put(bit2, i, 0, 0);  // Turn white
        }
        if (Bit2_get(bit2, i, columns - 1) == 1) {
            black_squares[black_square_count++] = (Coordinate){i, columns - 1};
            Bit2_put(bit2, i, columns - 1, 0);  // Turn white
        }
    }
}

// Function to read the PBM file into the Bit2_T structure
void read_pbm(FILE *input, Bit2_T bit2) {
    int rows = Bit2_height(bit2);
    int columns = Bit2_width(bit2);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int value;
            fscanf(input, "%d", &value);
            Bit2_put(bit2, i, j, value);
        }
    }
}

// Function to print the corrected PBM content to stdout
void print_pbm(Bit2_T bit2) {
    int rows = Bit2_height(bit2);
    int columns = Bit2_width(bit2);

    printf("P1\n");
    printf("%d %d\n", columns, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int value = Bit2_get(bit2, i, j);
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

    pbm_array = Bit2_new(rows, columns);  // Create the Bit2_T array

    read_pbm(input, pbm_array);
    process_perimeter(pbm_array);

    // Apply function in row-major order
    Bit2_map_row_major(pbm_array, apply_row_major, pbm_array);

    print_pbm(pbm_array);

    Bit2_free(&pbm_array);

    fclose(input);

    return 0;
}
