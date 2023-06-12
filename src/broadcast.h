#ifndef HEADER_BROADCAST
#define HEADER_BROADCAST
#include <unordered_map>

class BroadcastSender; 
class BroadcastReceiver;
enum class MessageType;

enum State {Waiting, Echoed, Readied, Accepted};

class Broadcast
{
    public: 
        Broadcast(uint32_t id, uint32_t thread_count);
        void Initialize(uint32_t initial_data);
        uint32_t Protocol(uint32_t source_id);
    private:
        void Send(uint32_t source_id, uint32_t data, MessageType type);
        BroadcastSender * sender;
        BroadcastReceiver * receiver;
        std::unordered_map<uint32_t, uint32_t> echo_count;
        std::unordered_map<uint32_t, uint32_t> ready_count;
        State state;
        uint32_t id;
        uint32_t echo_threshold;
        uint32_t ready_threshold;
        uint32_t accept_threshold;
        uint32_t bad_actors_max;
};
#endif
