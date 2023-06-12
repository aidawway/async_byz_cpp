#!/bin/bash
make main.exe
mpirun -np "$@" -oversubscribe main.exe