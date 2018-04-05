#define LAB4_EXTEND
#define EPSILON 0.00001
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lab4_IO.h"
#include "timer.h"

int main(int argc, char** argv) {
    struct node *nodes;
    int nodecount;
    int *num_in_links, *num_out_links;
    int rank, num_procs;
    int partition_start, partition_end, partition_size;
    double *ranks, *last_ranks, *local_ranks;
    double damp_const;
    double damp_factor = 0.85;
    double current_error = 0;
    int i, j;
    double start, end;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    GET_TIME(start);

    // get node stats from file
    get_node_stat(&nodecount, &num_in_links, &num_out_links);

    // determine partition data for current rank
    partition_size = nodecount / num_procs;
    partition_start = rank * partition_size;
    damp_const = (1.0 - damp_factor) / nodecount;

    // load node data for current partition
    node_init(&nodes, num_in_links, num_out_links, partition_start, partition_start + partition_size);

    // allocate memory for rank information
    ranks = malloc(sizeof(double) * nodecount);
    last_ranks = malloc(sizeof(double) * nodecount);
    local_ranks = malloc(sizeof(double) * partition_size);

    for (i = 0; i < nodecount; i++) {
        ranks[i] = 1.0 / nodecount;
    }

    // main page rank algorithm
    do {
        vec_cp(ranks, last_ranks, nodecount);

        for (i = 0; i < partition_size; i++) {
            local_ranks[i] = 0;
            for (j = 0; j < nodes[i].num_in_links; j++) {
                local_ranks[i] += last_ranks[nodes[i].inlinks[j]] /
                    num_out_links[nodes[i].inlinks[j]];
            }
            local_ranks[i] *= damp_factor;
            local_ranks[i] += damp_const;
        }

        // gather partition date back into the main process
        MPI_Allgather(local_ranks, partition_size, MPI_DOUBLE, ranks, partition_size, MPI_DOUBLE, MPI_COMM_WORLD);

        // calculate error on current ranks and broadcase it to the rest of the processes
        current_error = rel_error(ranks, last_ranks, nodecount);
    } while (current_error >= EPSILON);

    GET_TIME(end);
    // output result to file
    if (rank == 0) {
        Lab4_saveoutput(ranks, nodecount, end - start);
        printf("%f\n", end - start);
    }

    MPI_Finalize();
    return 0;
}