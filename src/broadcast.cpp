#include <iostream>
#include <mpi.h>
#include <stdint.h>

#include "broadcast.h"
#include "broadcast_message.h"
#include "broadcast_sender.h"


Broadcast::Broadcast(uint32_t id, uint32_t thread_count)
{
        BroadcastSender* sender = new BroadcastSender(id, thread_count);
        
        
        struct BroadcastMessage message  = {
               id,
               0,
               MessageType::Initiate
               
        };
        
        sender -> send(message);
        delete sender;
}