#include <stdio.h>
#include <stdlib.h>
#include "lab1_IO.h"
#include "timer.h"
#include <math.h>
#include <pthread.h>

typedef struct {
    int** left_matrix;
    int** right_matrix;
    int** result_matrix;
    int matrix_width;
    int thread_rank;
    int root_num_threads;
} matrix_parition_t;

void* multiply_matrix_partition(void* params)
{
    matrix_parition_t* matrix_partition_parms = (matrix_parition_t*) params;

    int x = matrix_partition_parms->thread_rank % matrix_partition_parms->root_num_threads;
    int y = floor(matrix_partition_parms->thread_rank / matrix_partition_parms->root_num_threads);

    int min_x = (matrix_partition_parms->matrix_width / matrix_partition_parms->root_num_threads) * x;
    int max_x =(matrix_partition_parms->matrix_width / matrix_partition_parms->root_num_threads) * (x + 1) - 1;

    int min_y = (matrix_partition_parms->matrix_width / matrix_partition_parms->root_num_threads) * y;
    int max_y =(matrix_partition_parms->matrix_width / matrix_partition_parms->root_num_threads) * (y + 1) - 1;

    int i, j, k;

    for (i = min_y; i <= max_y; i++)
    {
        for(j = min_x; j <= max_x; j++)
        {
            matrix_partition_parms->result_matrix[i][j] = 0;
            for (k = 0; k < matrix_partition_parms->matrix_width; k++)
            {
                matrix_partition_parms->result_matrix[i][j] +=
                    matrix_partition_parms->left_matrix[i][k] *
                    matrix_partition_parms->right_matrix[k][j];
            }
        }
    }

    return NULL;
}

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage %s TOTAL_CORES", argv[0]);
        return -1;
    }

    int n; // matrix size
    int i, j, k; // loop counters
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

    int thread_rank = 0;
    int thread_count = atoi(argv[1]);
    pthread_t* thread_handles = malloc(thread_count * sizeof(pthread_t));
    int threads_root = (int) sqrt(thread_count);

    for (thread_rank = 0; thread_rank < thread_count; thread_rank++)
    {
        matrix_parition_t* partition_params = malloc(sizeof(matrix_parition_t));
        partition_params->left_matrix = A;
        partition_params->right_matrix = B;
        partition_params->result_matrix = C;
        partition_params->matrix_width = n;
        partition_params->thread_rank = thread_rank;
        partition_params->root_num_threads = threads_root;

        pthread_create(&thread_handles[thread_rank], NULL,
            multiply_matrix_partition, (void *) partition_params);
    }

    for (thread_rank = 0; thread_rank < thread_count; thread_rank++)
    {
        pthread_join(thread_handles[thread_rank], NULL);
    }

    GET_TIME(end_time);

    // save output
    Lab1_saveoutput(C, &n, end_time - start_time);
}