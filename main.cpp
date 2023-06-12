#include <iostream>
#include <string>

#include "mpi.h"
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
    InitializeBroadcastMessage();
    Broadcast* broadcast = new Broadcast(id, thread_count);
    
    if (id == 0) 
    {   
        broadcast->Initialize(1);
    }
    int accepted_value = broadcast->Protocol(0);
    std::cout << accepted_value << std::endl;

    delete broadcast;
    MPI_Finalize();

    return 0;
}