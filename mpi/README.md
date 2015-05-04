# `bench_mpi.cxx`

Simple example to reproduce a slowing down of the `MPI_Allreduce` function.

# Description

Execute a loop `niter` times. For each loop, sleep during `microseconds`
(to simulation computation), and call `MPI_Allreduce`.

`microseconds` is set to a constant base time divided by the number of
processors, plus an overhead between 0% and 5%, so that `MPI_Allreduce`
is not called at the same wall clock on each process.

So the maximal time `MPI_Allreduce` is blocked waiting for laggard,
summed for all loop is:

    basetime * overhead * niter / mpi_size.

We expected the program be run with wall clock:

| `mpi_size` | `wall_clock` |
|------------|--------------|
|  1         | 210          |
|  2         | 105          |
|  4         |  52.5        |
|  8         |  26.25       |
| 16         |  13.125      |

# Issue

I get a problem with 7 or more processes with version `MPICH 3.1.4`, see results
in `carla/` and `otis/`. (carla and otis are my machine names).

In a real code (Computational Fluid Dynamic software), on `otis`, I have the
same problem with `Open MPI 1.8.4`, `MPIC 1.4.1` and `MPICH 3.1.4`.
