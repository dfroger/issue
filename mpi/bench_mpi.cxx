#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include <mpi.h>

using namespace std;

double *
linspace(double start, double stop, unsigned int number)
{
    double* x = new double[number];
    double step = (stop - start) / (number-1);
    for (unsigned int i = 0 ; i < number ; i ++)
        x[i] = start + i*step;
    return x;
}

unsigned int
get_turning_rank(int mpi_rank, int mpi_size, int iter)
{
    return (mpi_rank + iter) % mpi_size;
}

unsigned int
one_iteration_time(double ratio, unsigned int power, double variation_proc,
                   double variation_proc_max, int mpi_size)
{
    return ratio * pow(2,power) * variation_proc / (mpi_size*variation_proc_max);
}

int main(int argc, char* argv[]) {

    // Parse command line.
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " POWER RATIO VARIATION_PROC_MAX NITER" << endl;
        return 1;
    }
    unsigned int power = atoi(argv[1]);
    double ratio = atof(argv[2]);
    double variation_proc_max = atof(argv[3]);
    unsigned int niter = atoi(argv[4]);

    // Initialize MPI
    MPI_Init(&argc, &argv);
    int mpi_rank, mpi_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    double *variations_proc = linspace(1., variation_proc_max, mpi_size);
    if (mpi_size==1)
        variations_proc[0] = variation_proc_max;
    unsigned int usecs_cumul = 0;

    for (unsigned int iter = 0 ; iter < niter ; iter++)
    {
        unsigned int turning_rank = get_turning_rank(mpi_rank, mpi_size, iter);
        double variation_proc =  variations_proc[turning_rank];

        unsigned int usecs = one_iteration_time(ratio, power, variation_proc,
                                                variation_proc_max, mpi_size);

        // Simulate some computations
        usleep(usecs);

        // Perform MPI communications.
        unsigned int usecs_max;
        MPI_Allreduce(&usecs, &usecs_max, 1, MPI_UNSIGNED, MPI_MAX, MPI_COMM_WORLD);

        usecs_cumul += usecs_max;

        if (mpi_rank==0 && iter%10==0)
            cout << mpi_size << ": " << iter << " / " << niter << " " << usecs_cumul << endl;
    }

    if (mpi_rank==0)
        cout << (double) usecs_cumul / 1.E+06 << endl;

    delete[] variations_proc;

    MPI_Finalize();
    return 0;
}
