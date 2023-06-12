#ifndef HEADER_BROADCAST_RECEIVER
#define HEADER_BROADCAST_RECEIVER

    class BroadcastReceiver 
    {
        public:
            BroadcastReceiver(int buffer_size_);
        private:
            int buffer_size;
    };
#endif