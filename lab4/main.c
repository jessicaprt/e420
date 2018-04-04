#include <mpi.h>
#include <stdio.h>
#include "Lab4_IO.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int npes, myrank;
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    printf("Hello from process %d out of %d\n", myrank, npes);
    MPI_Finalize();
    return 0;
}