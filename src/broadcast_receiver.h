#ifndef HEADER_BROADCAST_RECEIVER
#define HEADER_BROADCAST_RECEIVER

class BroadcastMessage;

class BroadcastReceiver 
{
    public:
        BroadcastReceiver();
        struct BroadcastMessage recv();
    private:
        uint32_t broadcast_source_id;
};
#endif