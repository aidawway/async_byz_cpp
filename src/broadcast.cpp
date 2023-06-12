#include <iostream>
#include <mpi.h>
#include <stdint.h>
#include <unordered_map>
#include <string.h>

#include "broadcast_message.h"
#include "broadcast_sender.h"
#include "broadcast_receiver.h"
#include "broadcast.h"


Broadcast::Broadcast(uint32_t id_, uint32_t thread_count)
{
      id = id_;

      sender = new BroadcastSender(id, thread_count);
      receiver = new BroadcastReceiver();
      state = Waiting;

      bad_actors_max = thread_count % 3 == 0 ? thread_count / 3 - 1 : thread_count / 3;
      echo_threshold = (thread_count + bad_actors_max) / 2;
      ready_threshold = bad_actors_max + 1;
      accept_threshold = 2 * bad_actors_max + 1;
}

void Broadcast::Send(uint32_t source_id, uint32_t data, MessageType type)
{
      struct BroadcastMessage response = {source_id, data, type};
      sender -> send(response);
}

void Broadcast::Initialize(uint32_t initial_data)
{
      Broadcast::Send(id, initial_data, MessageType::Initiate);
}

uint32_t Broadcast::Protocol(uint32_t source_id)
{

      for (;;) 
      {
            BroadcastMessage message = receiver->recv();

            switch (message.type)
            {
                  case MessageType::Echo: echo_count[message.data]++;
                  case MessageType::Ready: ready_count[message.data]++;
            }
            switch(state)
            {
                  case Waiting:
                        if (message.type == MessageType::Initiate || echo_count[message.data] == echo_threshold || 
                                    ready_count[message.data] == ready_threshold)
                        {
                              Broadcast::Send(message.source_id, message.data, MessageType::Echo);
                              state = Echoed;
                        }
                        break;
                  case Echoed:
                        if (echo_count[message.data] == echo_threshold || ready_count[message.data] == ready_threshold)
                        {
                              Broadcast::Send(message.source_id, message.data, MessageType::Ready);
                              state = Readied;
                        }
                        break;
                  case Readied:
                        if(ready_count[message.data] >= accept_threshold)
                        {
                              state = Accepted;
                              return message.data;
                        }
            }

      } 
};