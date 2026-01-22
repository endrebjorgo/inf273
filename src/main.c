#include "../include/problem.h"
#include <stdio.h>

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
