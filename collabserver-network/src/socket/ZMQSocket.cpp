#include "collabserver/network/socket/ZMQSocket.h"

#include <cassert>
#include <cstring>

namespace collabserver {

zmq::context_t g_context(1);

// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------

ZMQSocket::ZMQSocket(ZMQSocketConfig& config) {
    _factory = config.factory;
    _socket = new zmq::socket_t(g_context, config.zmqPattern);
    assert(_factory != nullptr);
    assert(_socket != nullptr);
}

ZMQSocket::~ZMQSocket() {
    assert(_socket != nullptr);
    delete _socket;
}

// -----------------------------------------------------------------------------
// Connection / Binding
// -----------------------------------------------------------------------------

void ZMQSocket::bind(const char* address, const uint16_t port) {
    assert(_socket != nullptr);
    assert(address != nullptr);
    if (address != nullptr) {
        size_t size = strlen(address) + 13;  // 13 because tcp:// + port size + \0
        char endpoint[size];
        snprintf(endpoint, size, "tcp://%s:%d", address, port);
        _socket->bind(endpoint);
        _address = address;
        _port = port;
    }
}

void ZMQSocket::unbind() {
    assert(_socket != nullptr);
    size_t size = strlen(_address.c_str()) + 13;
    char endpoint[size];
    snprintf(endpoint, size, "tcp://%s:%d", _address.c_str(), _port);
    _socket->unbind(endpoint);
    _address.clear();
    _port = 0;
}

void ZMQSocket::connect(const char* address, const uint16_t port) {
    assert(_socket != nullptr);
    assert(address != nullptr);
    if (address != nullptr) {
        size_t size = strlen(address) + 13;  // 13 since tcp:// + port size + \0
        char endpoint[size];
        snprintf(endpoint, size, "tcp://%s:%d", address, port);
        _socket->connect(endpoint);
        _address = address;
        _port = port;
    }
}

void ZMQSocket::disconnect() {
    assert(_socket != nullptr);
    size_t size = strlen(_address.c_str()) + 13;
    char endpoint[size];
    snprintf(endpoint, size, "tcp://%s:%d", _address.c_str(), _port);
    _socket->disconnect(endpoint);
    _address = "";
    _port = 0;
}

// -----------------------------------------------------------------------------
// Message methods
// -----------------------------------------------------------------------------

// Internal use: calculate size of stream
static size_t _calculStreamSize(std::stringstream& stream) {
    // TODO: There might be a way better way to do that!
    stream.seekg(0, std::ios::end);
    const size_t size = stream.tellg();
    stream.seekg(0);
    return size;
}

void ZMQSocket::sendMessage(const Message& msg) {
    std::stringstream buffer;
    msg.serialize(buffer);

    const size_t msgSize = _calculStreamSize(buffer);
    const int msgType = static_cast<int>(msg.getType());

    zmq::message_t request(msgSize + 1);  // +1 for the msg type byte

    char* ptrBufferStart = static_cast<char*>(request.data()) + 1;

    memcpy(request.data(), &msgType, 1);
    memcpy(ptrBufferStart, buffer.str().c_str(), msgSize);

    _socket->send(request);
}

Message* ZMQSocket::receiveMessage() {
    Message* m = nullptr;
    while (m == nullptr) {
        zmq::message_t request_msg;
        _socket->recv(&request_msg);

        char* msg = static_cast<char*>(request_msg.data());
        const int size = request_msg.size();
        const int msgType = static_cast<int>(msg[0]);
        const char* msgData = msg + 1;
        const size_t msgSize = size - 1;

        m = _factory->newMessage(msgType);
        assert(msg != nullptr);

        std::stringstream stream;
        stream.str(std::string(msgData, msgSize));
        m->unserialize(stream);
    }
    return m;
}

// -----------------------------------------------------------------------------
// Various
// -----------------------------------------------------------------------------

void ZMQSocket::setsockopt(int optName, const void* optValue, size_t optLength) {
    assert(_socket != nullptr);
    _socket->setsockopt(optName, optValue, optLength);
}

}  // namespace collabserver
