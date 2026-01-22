#ifndef PROBLEM_H
#define PROBLEM_H

#include "../include/double_matrix.h"
#include <stdlib.h>

void buffer_strip_nl(char *buffer);

typedef struct {
    size_t node_count;
    size_t drone_flight_limit;
    DoubleMatrix truck_travel_times;
    DoubleMatrix drone_travel_times;
} Problem;

Problem problem_from_file(char *file_path);
void problem_display(Problem *problem);
void problem_free(Problem *problem);

#endif // PROBLEM_H
