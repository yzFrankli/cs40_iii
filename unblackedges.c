#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>  // Required for strcmp
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
void apply_row_major(int i, int j, Bit2_T bit2, int value, void *cl) {
    (void)cl;  // Mark the cl parameter as unused to avoid warnings

    if (value == 1) {  // If this square is black
        if (is_adjacent(black_squares, black_square_count, i, j)) {
            if (black_square_count < MAX_BLACK_SQUARES) { // Prevent overflow
                black_squares[black_square_count++] = (Coordinate){i, j};
                Bit2_put(bit2, i, j, 0);  // Turn white
                printf("Turned white at (%d, %d)\n", i, j);  // Debugging output
            }
        }
    }
}

// Function to process the perimeter of the PBM array
void process_perimeter(Bit2_T bit2) {
    int rows = Bit2_height(bit2);
    int columns = Bit2_width(bit2);

    printf("Processing perimeter: rows=%d, columns=%d\n", rows, columns);  // Debugging output

    // Process the top and bottom rows
    for (int j = 0; j < columns; j++) {
        if (Bit2_get(bit2, 0, j) == 1) {
            if (black_square_count < MAX_BLACK_SQUARES) { // Prevent overflow
                black_squares[black_square_count++] = (Coordinate){0, j};
                Bit2_put(bit2, 0, j, 0);  // Turn white
                printf("Top row turned white at (0, %d)\n", j);  // Debugging output
            }
        }
        if (Bit2_get(bit2, rows - 1, j) == 1) {
            if (black_square_count < MAX_BLACK_SQUARES) { // Prevent overflow
                black_squares[black_square_count++] = (Coordinate){rows - 1, j};
                Bit2_put(bit2, rows - 1, j, 0);  // Turn white
                printf("Bottom row turned white at (%d, %d)\n", rows - 1, j);  // Debugging output
            }
        }
    }

    // Process the left and right columns
    for (int i = 0; i < rows; i++) {
        if (Bit2_get(bit2, i, 0) == 1) {
            if (black_square_count < MAX_BLACK_SQUARES) { // Prevent overflow
                black_squares[black_square_count++] = (Coordinate){i, 0};
                Bit2_put(bit2, i, 0, 0);  // Turn white
                printf("Left column turned white at (%d, 0)\n", i);  // Debugging output
            }
        }
        if (Bit2_get(bit2, i, columns - 1) == 1) {
            if (black_square_count < MAX_BLACK_SQUARES) { // Prevent overflow
                black_squares[black_square_count++] = (Coordinate){i, columns - 1};
                Bit2_put(bit2, i, columns - 1, 0);  // Turn white
                printf("Right column turned white at (%d, %d)\n", i, columns - 1);  // Debugging output
            }
        }
    }
}

// Function to read the PBM file into the Bit2_T structure
void read_pbm(FILE *input, Bit2_T bit2) {
    int rows = Bit2_height(bit2);
    int columns = Bit2_width(bit2);

    // Read pixel data for binary PBM (P4)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j += 8) {
            unsigned char byte;
            if (fread(&byte, sizeof(unsigned char), 1, input) != 1) {
                fprintf(stderr, "Error reading PBM file at byte (%d, %d)\n", i, j);
                exit(1);
            }
            // Set bits for this byte into the Bit2 array
            for (int bit = 0; bit < 8 && j + bit < columns; bit++) {
                Bit2_put(bit2, i, j + bit, (byte & (1 << (7 - bit))) ? 1 : 0);
            }
        }
    }
}

// Function to print the corrected PBM content to stdout
void print_pbm(Bit2_T bit2) {
    int rows = Bit2_height(bit2);
    int columns = Bit2_width(bit2);

    printf("P1\n");  // Change to P1 for output
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

    FILE *input = fopen(argv[1], "rb");  // Open in binary mode
    assert(input != NULL);

    char header[3];  // "P4" or other headers
    if (fscanf(input, "%2s", header) != 1 || strcmp(header, "P4") != 0) {
        fprintf(stderr, "Not a valid PBM file (must start with P4).\n");
        exit(1);
    }

    int rows, columns;
    if (fscanf(input, "%d %d", &columns, &rows) != 2 || rows <= 0 || columns <= 0) {
        fprintf(stderr, "Error reading dimensions from PBM file.\n");
        exit(1);
    }

    pbm_array = Bit2_new(columns, rows);  // Create the Bit2_T array

    read_pbm(input, pbm_array);
    process_perimeter(pbm_array);

    // Apply function in row-major order
    Bit2_map_row_major(pbm_array, apply_row_major, NULL);

    print_pbm(pbm_array);

    Bit2_free(&pbm_array);  // Free allocated memory

    fclose(input);  // Close the file

    return 0;
}
