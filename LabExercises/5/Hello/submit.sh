#!/bin/bash

#PBS -N Hw

#PBS -q default

#PBS -l nodes=7:ppn=20

#PBS -j oe

#PBS -V


cd $PBS_O_WORKDIR/



mpirun -machinefile $PBS_NODEFILE -np 140 ./HW
