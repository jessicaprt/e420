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
    int i, j, k; // loop counters
    int total_cores = atoi(argv[1]);
    double start_time, end_time; // time measurement
    int** A;
    int** B; // loaded matricies

    // load input
    Lab1_loadinput(&A, &B, &n);

    // prepare output matrix
    int** C;
    C = malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));

    GET_TIME(start_time);

    for (i = 0; i < n; i++)
        for(j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    GET_TIME(end_time);

    // save output
    Lab1_saveoutput(C, &n, end_time - start_time);
}