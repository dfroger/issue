#include <iostream>
#include <unistd.h>
#include <math.h>

#include <mpi.h>

using namespace std;

/* For example, with size 4 and overhead_percent_max 5:
 *    
 *            rank=0  rank=1  rank=2  rank=3
 *    iter=0  0.      1.66    3.33    5.
 *    iter=1  1.66    3.33    5.      0.
 *    iter=2  3.33    5.      0.      1.66
 *    iter=3  5.      0.      1.66    3.33
 *    iter=4  0.      1.66    3.33    5.
 *    iter=5  1.66    3.33    5.      0.
 *    iter=6  3.33    5.      0.      1.66
 *    etc
 *
 */
double get_overhead_percent(int rank, int size, int iter,
                            double overhead_percent_max)
{
    if (size==1)
        return overhead_percent_max;
    int turning_rank = (rank + iter) % size;
    return double(turning_rank) / (size-1) * overhead_percent_max;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned int niter = 1000;
    unsigned int usecs_to_compute_one_iteration = pow(2,16) / size;
    unsigned int usecs_cumul = 0;
    double overhead_percent_max = 5.;

    for (unsigned int iter = 0 ; iter < niter ; iter++)
    {
        // Get overhead beetween 0. and overhead_percent_max.
        double overhead = get_overhead_percent(rank,size,iter,
                                               overhead_percent_max) / 100.;
        
        unsigned int usecs = (unsigned int) usecs_to_compute_one_iteration * (1 + overhead);

        // Simulate some computations
        usleep( usecs);

        // Perform MPI communications.
        unsigned int usecs_max;
        MPI_Allreduce(&usecs, &usecs_max, 1, MPI_UNSIGNED, MPI_MAX, MPI_COMM_WORLD);

        usecs_cumul += usecs_max;

        if (rank==0)
            cout << size << ": " << iter << " / " << niter << " " << usecs_cumul << endl;
    }

    MPI_Finalize();
    return 0;
}
