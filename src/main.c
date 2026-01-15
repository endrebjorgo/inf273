#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("ERROR: please pass a file\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("ERROR: unable to open file %s\n", argv[1]);
        exit(1);
    }

    return 0;
}
