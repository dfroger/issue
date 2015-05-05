#!/usr/bin/bash

POWER=16
RATIO=1.
NITER=1000

for variation_proc_max in 1.0 1.1 1.2 1.3 1.4 1.5
do
    RESULT_FILE=variation_proc_max_$variation_proc_max.txt
    rm -f $RESULT_FILE

    for nproc in 1 2 4 8
    do
        echo -n "$nproc " >> $RESULT_FILE

        /usr/bin/time \
            --format=%e \
            --output=$RESULT_FILE \
            --append \
            mpiexec -n $nproc -bind-to hwthread \
                ./bench_mpi $POWER $RATIO $variation_proc_max $NITER
    done

done
