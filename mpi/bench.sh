#!/usr/bin/bash

RESULT_FILE=time.txt

if [ "$#" != "1" ]
then
    echo "Usage: bench.sh EXE"
    exit 1
fi

rm -f $RESULT_FILE

for nproc in 1 2 4 8
do
    echo -n "$nproc " >> $RESULT_FILE

    /usr/bin/time \
        --format=%e \
        --output=$RESULT_FILE \
        --append \
        mpiexec -n $nproc -bind-to hwthread $1
done
