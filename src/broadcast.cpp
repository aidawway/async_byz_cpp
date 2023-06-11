#include <iostream>
#include <mpi.h>
#include <string.h>
#include "broadcast.h"


Broadcast::Broadcast(int id)
{
        std::string message = "Hello from: " + std::to_string(id);

        int dest = 0;
        int message_tag = 0;
        MPI_Request req;
        int message_handle = MPI_Isend(&message, message.length() + 1, MPI_CHAR, dest, message_tag, MPI_COMM_WORLD, &req); //TODO update communicatior
        MPI_Request_free(&req);
};