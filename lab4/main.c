#define LAB4_EXTEND
#define EPSILON 0.00001
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lab4_IO.h"

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

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (rank == 0) {
        get_node_stat(&nodecount, &num_in_links, &num_out_links);
        node_init(&nodes, num_in_links, num_out_links, 0, nodecount);
    }

    MPI_Bcast(&nodecount, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        num_in_links = malloc(sizeof(int) * nodecount);
        num_out_links = malloc(sizeof(int) * nodecount);
        nodes = malloc(sizeof(struct node) * nodecount);
    }

    MPI_Bcast(num_in_links, nodecount, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(num_out_links, nodecount, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < nodecount; i++) {
        MPI_Bcast(&(nodes[i].num_in_links), 1,  MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&(nodes[i].num_out_links), 1,  MPI_INT, 0, MPI_COMM_WORLD);
        if (i != 0) {
            nodes[i].inlinks = malloc(sizeof(int) * nodes[i].num_in_links);
        }
        MPI_Bcast(&(nodes[i].inlinks), 1,  MPI_INT, 0, MPI_COMM_WORLD);
    }

    partition_size = nodecount / num_procs;
    partition_start = rank * partition_size;
    partition_end = partition_start + partition_size;
    damp_const = (1.0 - damp_factor) / nodecount;

    ranks = malloc(sizeof(double) * nodecount);
    last_ranks = malloc(sizeof(double) * nodecount);

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

        MPI_Gather(ranks + partition_start, nodecount, MPI_DOUBLE, ranks, nodecount, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        current_error = rel_error(ranks, last_ranks, nodecount);
        MPI_Bcast(&current_error, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } while (current_error >= EPSILON);

    if (rank == 0) {
        printf("Error: %f\n", current_error);
    }

    MPI_Finalize();
}