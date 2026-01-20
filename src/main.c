#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LINE_BUFFER_CAPACITY 256
#define CUSTOMER_COUNT_HEADER           "# Number of customers"
#define DRONE_FLIGHT_LIMIT_HEADER       "# Drone flight limit"
#define TRUCK_TRAVEL_TIME_MATRIX_HEADER "# Travel time matrix for the truck"
#define DRONE_TRAVEL_TIME_MATRIX_HEADER "# Travel time matrix for the drones"

void buffer_strip_nl(char *buffer) {
    buffer[strcspn(buffer, "\r\n")] = 0;
}

typedef struct {
    size_t customer_count;
    size_t drone_flight_limit;
    double *truck_travel_time_matrix;
    double *drone_travel_time_matrix;
} Problem;

Problem problem_from_file(char *file_path) {
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
    problem.customer_count = atoi(line_buffer);

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, TRUCK_TRAVEL_TIME_MATRIX_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                TRUCK_TRAVEL_TIME_MATRIX_HEADER, line_buffer);
        exit(1);
    }
    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    // Parse the thing

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, DRONE_FLIGHT_LIMIT_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                DRONE_FLIGHT_LIMIT_HEADER, line_buffer);
        exit(1);
    }
    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    // Parse the thing

    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    buffer_strip_nl(line_buffer);
    if (strcmp(line_buffer, DRONE_TRAVEL_TIME_MATRIX_HEADER) != 0) {
        fprintf(stderr, "ERROR: expected header ´%s´, found: ´%s´", 
                DRONE_TRAVEL_TIME_MATRIX_HEADER, line_buffer);
        exit(1);
    }
    fgets(line_buffer, LINE_BUFFER_CAPACITY, fp);
    // Parse the thing

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

void problem_free(Problem *problem) {
    free(problem->truck_travel_time_matrix);
    free(problem->drone_travel_time_matrix);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: input file was not passed\n");
        exit(1);
    }

    Problem problem = problem_from_file(argv[1]);
    (void) problem;

    return 0;
}
