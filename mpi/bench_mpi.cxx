#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include <mpi.h>

using namespace std;

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

    cout << "iter / niter seconds_cumul" << endl;
    for (unsigned int iter = 0 ; iter < niter ; iter++)
    {
        // Generate a number between 0 and 0.05
        double overhead_percent = (rand() % 6) / 100.;
        
        double seconds = seconds_to_compute_one_iteration
                       * (1 + overhead_percent);
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
