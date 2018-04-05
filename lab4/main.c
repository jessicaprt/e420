#define LAB4_EXTEND
#define EPSILON 0.00001
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lab4_IO.h"
#include "timer.h"

int copy_values(double* from, double* to, int start, int end) {
    int i = 0;
    for (i = start; i < end; i++) {
        to[i] = from[i];
    }
}

int main(int argc, char** argv) {
    struct node *nodes;
    int nodecount;
    int *num_in_links, *num_out_links;
    int rank, num_procs;
    int partition_start, partition_end, partition_size;
    double *ranks, *last_ranks;
    double damp_const;
    double damp_factor = 0.85;
    double current_error = 0;
    int i, j;
    double start, end;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    GET_TIME(start);

    // load input data on main process
    if (rank == 0) {
        get_node_stat(&nodecount, &num_in_links, &num_out_links);
        node_init(&nodes, num_in_links, num_out_links, 0, nodecount);
    }

    // broadcast the node count to all other processes
    MPI_Bcast(&nodecount, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // if you are not the main process then allocate memory for
    // the node information
    if (rank != 0) {
        num_in_links = malloc(sizeof(int) * nodecount);
        num_out_links = malloc(sizeof(int) * nodecount);
        nodes = malloc(sizeof(struct node) * nodecount);
    }

    // broadcast link information to remaining processes
    MPI_Bcast(num_in_links, nodecount, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(num_out_links, nodecount, MPI_INT, 0, MPI_COMM_WORLD);

    // broadcast node information to remaining processes
    for (int i = 0; i < nodecount; i++) {
        MPI_Bcast(&(nodes[i].num_in_links), 1,  MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&(nodes[i].num_out_links), 1,  MPI_INT, 0, MPI_COMM_WORLD);
        if (i != 0) {
            nodes[i].inlinks = malloc(sizeof(int) * nodes[i].num_in_links);
        }
        MPI_Bcast(&(nodes[i].inlinks), 1,  MPI_INT, 0, MPI_COMM_WORLD);
    }

    // determine partition data for current rank
    partition_size = nodecount / num_procs;
    partition_start = rank * partition_size;
    partition_end = partition_start + partition_size;
    damp_const = (1.0 - damp_factor) / nodecount;

    // allocate memory for rank information
    ranks = malloc(sizeof(double) * nodecount);
    last_ranks = malloc(sizeof(double) * nodecount);

    // main page rank algorithm
    do {
        for (i = partition_start; i < partition_end; i++) {
            ranks[i] = 1.0 / nodecount;
        }

        copy_values(ranks, last_ranks, partition_start, partition_end);

        for (i = partition_start; i < partition_end; i++) {
            ranks[i] = 0;
            for (j = 0; j < nodes[i].num_in_links; j++) {
                ranks[i] += ranks[nodes[i].inlinks[j]] / num_out_links[nodes[i].inlinks[j]];
            }
            ranks[i] *= damp_factor;
            ranks[i] += damp_const;
        }

        // gather partition date back into the main process
        MPI_Gather(ranks + partition_start, nodecount, MPI_DOUBLE, ranks, nodecount, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // calculate error on current ranks and broadcase it to the rest of the processes
        current_error = rel_error(ranks, last_ranks, nodecount);
        MPI_Bcast(&current_error, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } while (current_error >= EPSILON);

    GET_TIME(end);
    // output result to file
    if (rank == 0) {
        printf("Error: %f\n", current_error);
        Lab4_saveoutput(&current_error, nodecount, end - start);
    }

    MPI_Finalize();
    return 0;
}