#ifndef HEADER_BROADCAST_MESSAGE
#define HEADER_BROADCAST_MESSAGE
    enum class MessageType {Initiate, Echo, Ready};

    struct BroadcastMessage
    {
        uint32_t source_id;
        uint32_t data;
        MessageType type;
    };


    static MPI_Datatype CreateMpiBroadcastMessageDatatype() 
    {
        const int block_lengths[2] = {2, 1};
        const MPI_Datatype datatypes[2] = {MPI_UINT32_T, MPI_INT};
        const MPI_Aint displacements[2] = {offsetof(BroadcastMessage, source_id), offsetof(BroadcastMessage, type)};

        MPI_Datatype message_type;
        int err = MPI_Type_create_struct(2, block_lengths, displacements, datatypes, &message_type);
        err = MPI_Type_commit(&message_type);
        return message_type;
    };

    static MPI_Datatype MPI_BROADCAST_MESSAGE_DATATYPE;

    static void InitializeBroadcastMessage() {
        MPI_BROADCAST_MESSAGE_DATATYPE = CreateMpiBroadcastMessageDatatype();
    }
#endif