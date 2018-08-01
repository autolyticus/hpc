#! /bin/sh
#
# runner.sh
# Copyright (C) 2018 g <g@levi-al>
#
# Distributed under terms of the MIT license.
#

prog=./prog1.c.out
runProg() {
    echo -n "$1",
    OMP_NUM_THREADS="$1" "$prog"
}

listGenerator() {
    echo "1, 2, 4, 6, 8, 10, 12, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62" |
        sed -n 1'p' |
        tr ',' '\n'
}

for i in $(listGenerator); do
    runProg "$i"
done
