#include <mpi.h>
#include <iostream>
#include <string>

#include "src/broadcast.h"
#include "src/broadcast_message.h"



/**
 * mpicxx -std=c++14 main.cpp src/*.cpp -o main.exe
 * export TMPDIR=/tmp
 * mpirun -np 20 -oversubscribe main.exe
*/
int main(int argc, char *argv[])
{

    int id;
    int thread_count;
    int err = MPI_Init(&argc, &argv);
    //TODO throw error if not run with enough threads
    //TODO Namespaces
    err = MPI_Comm_rank(MPI_COMM_WORLD, &id);
    err = MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
    //TODO error checks
    initialize_broadcast_message();
    Broadcast* broadcast = new Broadcast(id, thread_count);
    delete broadcast;

    if (id == 0) 
    {   
        int thread_count;
        MPI_Comm_size(MPI_COMM_WORLD, &thread_count);
        BroadcastMessage message;
        int tag = 0;

        for (int i = 0; i < thread_count; i++)
        {
            MPI_Status status;
            MPI_Recv(&message, 1, MPI_BROADCAST_MESSAGE_DATATYPE, i, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::cout << std::to_string(message.source_id) << std::endl;
        }

    }

    MPI_Finalize();

    return 0;
}