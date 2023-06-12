#include <mpi.h>
#include <stdint.h>
#include "broadcast_sender.h"
#include "broadcast_message.h"


BroadcastSender::BroadcastSender(uint32_t id_, uint32_t thread_count_)
{
    id = id_;
    thread_count = thread_count_;
    InitializeBroadcastMessage();
}

void BroadcastSender::send(struct BroadcastMessage message)
{
    for (int i = 0; i < thread_count; i++)
    {
        MPI_Request req;
        int message_handle = MPI_Isend(&message, 1, MPI_BROADCAST_MESSAGE_DATATYPE, i, broadcast_source_id, MPI_COMM_WORLD, &req); //TODO update communicatior
        MPI_Request_free(&req);
    }
};