#include <iostream>
#include <unistd.h>

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
    int turning_rank = (rank + iter) % size;
    return double(turning_rank) / (size-1) * overhead_percent_max;
}

int main(int argc, char* argv[]) {

    // Initialize MPI
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned int micro = 1E+06;
    unsigned int niter = 1000;
    double seconds_cumul = 0.;
    double seconds_to_compute_one_iteration = 0.2 / size;
    double overhead_percent_max = 5.;

    cout << "iter / niter seconds_cumul" << endl;
    for (unsigned int iter = 0 ; iter < niter ; iter++)
    {
        // Get overhead beetween 0. and overhead_percent_max.
        double overhead = get_overhead_percent(rank,size,iter,
                                               overhead_percent_max) / 100.;
        
        double seconds = seconds_to_compute_one_iteration * (1 + overhead);
        unsigned int microseconds = (unsigned int) (seconds * micro);
        seconds = (double) microseconds / micro;

        // Simulate some computations
        usleep(microseconds);

        // Perform MPI communications.
        double seconds_max;
        MPI_Allreduce(&seconds, &seconds_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

        seconds_cumul += seconds_max;

        if (rank==0)
            cout << iter << " / " << niter << " " << seconds_cumul << endl;
    }

    // Finalize MPI.
    MPI_Finalize();

    return 0;
}
