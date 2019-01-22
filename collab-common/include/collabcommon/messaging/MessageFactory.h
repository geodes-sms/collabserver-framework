#pragma once

#include "collabcommon/utils/Singleton.h"
#include "collabcommon/messaging/Message.h"

namespace collab {


/**
 * \brief
 * Factory for CollabServer messages.
 *
 * Each message has a special ID.
 * Factory may return the specific message implementation from its ID.
 */
class MessageFactory : private Singleton<MessageFactory> {
    // -------------------------------------------------------------------------
    // Message types
    // -------------------------------------------------------------------------
    public:

        /**
         * List all kind of messages possible for CollabServer.
         * Each message has a unique ID.
         */
        enum Type : unsigned int {
            MSG_CONNECTION_REQUEST,
            MSG_CONNECTION_SUCCESS,
            MSG_DISCONNECT_REQUEST,
            MSG_DISCONNECT_SUCCESS,

            MSG_CREA_DATA_REQUEST,
            MSG_CREA_DATA_SUCCESS,
            MSG_JOIN_DATA_REQUEST,
            MSG_JOIN_DATA_SUCCESS,
            MSG_LEAVE_DATA_REQUEST,
            MSG_LEAVE_DATA_SUCCESS,

            MSG_ROOM_OPERATION,

            MSG_ERROR,
            MSG_DEBUG,
            MSG_UGLY,
            MSG_EMPTY,

            // Internal use (TO KEEP LAST).
            // Has the total number of defined messages
            _COUNTER
        };


    // -------------------------------------------------------------------------
    // Init
    // -------------------------------------------------------------------------

    private:
        friend Singleton<MessageFactory>;
    public:
        using Singleton<MessageFactory>::getInstance;
    protected:
        MessageFactory() = default;
        ~MessageFactory() = default;


    // -------------------------------------------------------------------------
    // Factory methods
    // -------------------------------------------------------------------------

    public:

        /**
         * Create a new concrete message from its ID.
         * If ID is not valid, nullptr is returned.
         *
         * \warning
         * Message must be free manually
         *
         * \param type  ID of the message type to create.
         * \return      Smart pointer to the new created Message.
         */
        Message* newMessage(const unsigned int type) const;

        /**
         * Free the message previously created by the factory.
         *
         * \param msg Message to free
         */
        void freeMessage(Message* msg) const;
};


} // End namespace


