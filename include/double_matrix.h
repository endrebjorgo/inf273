#ifndef DOUBLE_MATRIX_H
#define DOUBLE_MATRIX_H

#include <stdlib.h>

typedef struct {
    double *items;
    size_t rows;
    size_t cols;
} DoubleMatrix;

DoubleMatrix double_matrix_init(const size_t rows, const size_t cols);
double double_matrix_get(const DoubleMatrix *matrix, const size_t row, const size_t col);
void double_matrix_set(DoubleMatrix *matrix, const size_t row, const size_t col, const double value);
void double_matrix_display(const DoubleMatrix *matrix);
void double_matrix_free(DoubleMatrix *matrix);

#endif // DOUBLE_MATRIX_H
