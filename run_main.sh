#!/bin/bash
make main.exe
export TMPDIR=/tmp
mpirun -np "$@" -oversubscribe main.exe