#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINE_BUFFER_CAPACITY 256
#define CUSTOMER_COUNT_HEADER           "# Number of customers"
#define DRONE_FLIGHT_LIMIT_HEADER       "# Drone flight limit"
#define TRUCK_TRAVEL_TIME_MATRIX_HEADER "# Travel time matrix for the truck"
#define DRONE_TRAVEL_TIME_MATRIX_HEADER "# Travel time matrix for the drones"

void buffer_strip_nl(char *buffer) {
    buffer[strcspn(buffer, "\r\n")] = 0;
}

typedef struct {
    double *items;
    size_t rows;
    size_t cols;
} DoubleMatrix;

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

typedef struct {
    size_t node_count;
    size_t drone_flight_limit;
    DoubleMatrix truck_travel_times;
    DoubleMatrix drone_travel_times;
} Problem;

Problem problem_from_file(char *file_path) {
    char *curr_token;

    Problem problem = {0};

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: unable to open file %s\n", file_path);
        exit(1);
    }
    char line_buffer[LINE_BUFFER_CAPACITY] = {0};

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, CUSTOMER_COUNT_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                CUSTOMER_COUNT_HEADER, line_buffer);
        exit(1);
    }
    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    problem.node_count = atoi(line_buffer) + 1;

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, DRONE_FLIGHT_LIMIT_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                DRONE_FLIGHT_LIMIT_HEADER, line_buffer);
        exit(1);
    }
    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    problem.drone_flight_limit = atoi(line_buffer);

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, TRUCK_TRAVEL_TIME_MATRIX_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                TRUCK_TRAVEL_TIME_MATRIX_HEADER, line_buffer);
        exit(1);
    }
    problem.truck_travel_times = double_matrix_init(problem.node_count, problem.node_count);
    for (size_t i = 0; i < problem.node_count; ++i) {
        fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
        curr_token = strtok(line_buffer, " \t"); 
        for (size_t j = 0; j < problem.node_count; ++j) {
            double_matrix_set(&problem.truck_travel_times, i, j, strtod(curr_token, NULL));
            curr_token = strtok(NULL, " \t"); 
        }
        assert(curr_token == NULL);
    }

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, DRONE_TRAVEL_TIME_MATRIX_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                DRONE_TRAVEL_TIME_MATRIX_HEADER, line_buffer);
        exit(1);
    }
    problem.drone_travel_times = double_matrix_init(problem.node_count, problem.node_count);
    for (size_t i = 0; i < problem.node_count; ++i) {
        fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
        curr_token = strtok(line_buffer, " \t"); 
        for (size_t j = 0; j < problem.node_count; ++j) {
            double_matrix_set(&problem.drone_travel_times, i, j, strtod(curr_token, NULL));
            curr_token = strtok(NULL, " \t"); 
        }
        assert(curr_token == NULL);
    }

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, "#") != 0) {
        fprintf(stderr, "ERROR: expected file to end with ´#´, found: ´%s´", 
                line_buffer);
        exit(1);
    }
    fclose(fp);

    return problem;
}

void problem_display(Problem *problem) {
    printf("node_count = %zu\n", problem->node_count);
    printf("drone_flight_limit = %zu\n", problem->drone_flight_limit);
    printf("truck_travel_times =\n");
    double_matrix_display(&problem->truck_travel_times);
    printf("drone_travel_times =\n");
    double_matrix_display(&problem->drone_travel_times);
}

void problem_free(Problem *problem) {
    double_matrix_free(&problem->truck_travel_times);
    double_matrix_free(&problem->drone_travel_times);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: input file was not passed\n");
        exit(1);
    }
    Problem problem = problem_from_file(argv[1]);
    problem_display(&problem);
    problem_free(&problem);

    return 0;
}
