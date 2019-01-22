#pragma once

#include <cstdint>
#include <string>
#include <zmq.hpp>

#include "collabcommon/messaging/MessageFactory.h"
#include "collabcommon/messaging/Message.h"

namespace collab {


/**
 * \brief
 * Configuration for a ZMQSocket.
 */
struct ZMQSocketConfig {
    int                 zmqPattern; // From ZMQ constants (ex: ZMQ_SUB)
    MessageFactory*     factory;
};


/**
 * \brief
 * Abstraction of a ZeroMQ socket.
 *
 * \par Error handling
 * See note from zmq-cpp documentation (http://api.zeromq.org/2-1:zmq-cpp)
 * """
 * All errors reported by the underlying ØMQ C library functions are
 * automatically converted to exceptions by the C++ language binding.
 * The zmq::error_t class is derived from the std::exception class and uses
 * the zmq_strerror() function to convert the error code to
 * human-readable string.
 * """
 *
 * \see http://api.zeromq.org/2-1:zmq-cpp
 */
class ZMQSocket {
    private:
        zmq::socket_t*      _socket;
        MessageFactory*     _factory;
        std::string         _address;
        uint16_t            _port;

    public:

        ZMQSocket(ZMQSocketConfig& config);
        ~ZMQSocket();

    public:

        // ---------------------------------------------------------------------
        // Connection / Binding
        // ---------------------------------------------------------------------

        /**
         * Set socket port/address and start to accept incoming connections.
         * Common bind address may be simply "*" for instance.
         * Throw zmq::error_t if error (See error handling note).
         *
         * \see http://api.zeromq.org/2-1:zmq-cpp
         * \see http://api.zeromq.org/3-2:zmq-bind
         *
         * \param address   Address to be bound with the socket.
         * \param port      Port accepting connections.
         */
        void bind(const char* address, const uint16_t port);

        /**
         * Stop accepting connections on this socket.
         * bind should have been called first.
         * Throw zmq::error_t if error (See error handling note).
         *
         * \see http://api.zeromq.org/2-1:zmq-cpp
         * \see http://api.zeromq.org/3-2:zmq-unbind
         */
        void unbind();

        /**
         * Create outgoing connection from this socket.
         * Throw zmq::error_t if error (See error handling note).
         *
         * \see http://api.zeromq.org/2-1:zmq-cpp
         * \see http://api.zeromq.org/3-2:zmq-connect
         *
         * \param address   Address to connect.
         * \param port      Port to connect the distant address.
         */
        void connect(const char* address, const uint16_t port);

        /**
         * Disconnect this socket.
         * Throw zmq::error_t if error (See error handling note).
         *
         * \see http://api.zeromq.org/2-1:zmq-cpp
         * \see http://api.zeromq.org/3-2:zmq-disconnect
         */
        void disconnect();


    // -------------------------------------------------------------------------
    // Message methods
    // -------------------------------------------------------------------------

    public:

        /**
         * Send a message on this socket transport.
         * Block until message is sent.
         *
         * \param msg The message to send.
         */
        void sendMessage(const Message& msg);

        /**
         * Wait until receive a message from this socket.
         * This is blocking until a message is received.
         *
         * \warning
         * Message is created from on the head and must be free.
         * You may use the factory freeMessage method.
         *
         * \return Received message.
         */
        Message* receiveMessage();


    // -------------------------------------------------------------------------
    // Various
    // -------------------------------------------------------------------------

    public:

        void setsockopt(int optName, const void* optValue, size_t optLength);
};


} // End namespace


