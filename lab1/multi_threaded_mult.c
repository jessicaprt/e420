#include <stdio.h>
#include <stdlib.h>
#include "lab1_IO.h"
#include "timer.h"

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage %s TOTAL_CORES", argv[0]);
        return -1;
    }

    int n; // matrix size
    int i; // loop counters
    int total_cores = atoi(argv[1]);
    int start_time, end_time; // time measurement
    int** A;
    int** B; // loaded matricies

    // prepare output matrix
    int** C; // loaded matricies
    C = malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));

    // load input
    Lab1_loadinput(&A, &B, &n);

    GET_TIME(start_time);
    // do the maths
    GET_TIME(end_time);

    // save output
    Lab1_saveoutput(C, &n, end_time - start_time);
}