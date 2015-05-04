#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    for (unsigned int iter = 0 ; iter < 1000 ; iter++)
        MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;
}
