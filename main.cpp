#include <mpi.h>
#include <iostream>
#include <string>

#include "src/broadcast.h"

/**
 * mpicxx main.cpp -o main.exe 
 * export TMPDIR=/tmp
 * mpirun -np 20 -oversubscribe main.exe
*/
int main(int argc, char *argv[])
{

    int id;
    int err = MPI_Init(&argc, &argv);

    //TODO throw error if not run with enough threads
    //TODO Namespaces
    err = MPI_Comm_rank(MPI_COMM_WORLD, &id);
    //TODO error checks
    
    Broadcast* broadcast = new Broadcast(id);
    delete broadcast;

    if (id == 0) 
    {   
        int thread_count;
        MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
        int buffer_size = 30;
        int tag = 0;

        for (int i = 0; i < thread_count; i++)
        {
            char data[buffer_size];
            MPI_Status status;
            MPI_Recv(&data, buffer_size, MPI_CHAR, i, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::cout << std::string(data) << std::endl;
        }

    }

    MPI_Finalize();

    return 0;
}