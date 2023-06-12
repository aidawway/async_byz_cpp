#include <mpi.h>
#include <stdint.h>

#include "broadcast_message.h"
#include "broadcast_receiver.h"

BroadcastReceiver::BroadcastReceiver()
{
    InitializeBroadcastMessage();
}

struct BroadcastMessage BroadcastReceiver::recv()
{
    struct BroadcastMessage message;
    MPI_Recv(&message, 1, MPI_BROADCAST_MESSAGE_DATATYPE, MPI_ANY_SOURCE, broadcast_source_id, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return message;
}