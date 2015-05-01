#!/usr/bin/bash

RESULT_FILE=time.txt

rm -f $RESULT_FILE

for nproc in 2 4 8 16
do
    echo -n "$nproc " >> $RESULT_FILE

    /usr/bin/time \
        --format=%e \
        --output=$RESULT_FILE \
        --append \
        mpirun -n $nproc ./bench_mpi
done
