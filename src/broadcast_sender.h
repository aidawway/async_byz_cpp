#ifndef HEADER_BROADCAST_SENDER
#define HEADER_BROADCAST_SENDER

    class BroadcastSender {

        public:
            BroadcastSender(uint32_t id_, uint32_t thread_count_);
            void send(struct BroadcastMessage message);
        private:
            int thread_count;
            int id;
            uint32_t broadcast_source_id;
    
    };
#endif