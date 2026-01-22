#include "../include/double_matrix.h"
#include <stdio.h>

DoubleMatrix double_matrix_init(const size_t rows, const size_t cols) {
    double *temp_items = calloc(rows * cols, sizeof(double));
    if (temp_items == NULL) {
        fprintf(stderr, "ERROR: failed to allocate temp_items\n");
        exit(1);
    }
    DoubleMatrix matrix = {
        .items = temp_items,
        .rows = rows,
        .cols = cols
    };
    return matrix;
}

double double_matrix_get(const DoubleMatrix *matrix, const size_t row, const size_t col) {
    if (row >= matrix->rows || col >= matrix->cols) {
        fprintf(stderr, "ERROR: invalid index of %zux%zu matrix: (%zu,%zu)\n",
                matrix->rows, matrix->cols, row, col);
        exit(1);
    }
    return matrix->items[row * matrix->cols + col];
}

void double_matrix_set(DoubleMatrix *matrix, const size_t row, const size_t col, const double value) {
    if (row >= matrix->rows || col >= matrix->cols) {
        fprintf(stderr, "ERROR: invalid index of %zux%zu matrix: (%zu,%zu)\n",
                matrix->rows, matrix->cols, row, col);
        exit(1);
    }
    matrix->items[row * matrix->cols + col] = value;
}

void double_matrix_display(const DoubleMatrix *matrix) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->cols; ++j) {
            printf("%.2lf ", double_matrix_get(matrix, i, j));
        }
        printf("\n");
    } 
}

void double_matrix_free(DoubleMatrix *matrix) {
    free(matrix->items);
}
