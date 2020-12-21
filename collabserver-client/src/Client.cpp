#include "collabserver/client/Client.h"

#include <cassert>
#include <sstream>
#include <string>
#include <thread>
#include <zmq.hpp>

#include "collabserver/network/messaging/Message.h"
#include "collabserver/network/messaging/MessageFactory.h"
#include "collabserver/network/messaging/MessageList.h"
#include "collabserver/network/socket/ZMQSocket.h"
#include "constants.h"

namespace collabserver {

// Local variables: prefixed with l_
static ZMQSocket* l_socketREQ = nullptr;
static ZMQSocket* l_socketSUB = nullptr;
static MessageFactory& l_msgFactory = MessageFactory::getInstance();

// -----------------------------------------------------------------------------
// SUB Socket methods
// -----------------------------------------------------------------------------

// Listen incoming RoomOperation messages
// WARNING: Call it only once (No check done)
static void listenSocketSUB(Client* client) {
    assert(client != nullptr);

    while (true) {
        Message* received = nullptr;
        try {
            received = l_socketSUB->receiveMessage();
        } catch (std::exception& e) {
            // Usually zmq::error_t meaning SIGINT received for instance.
            break;
        }

        if (received->getType() != MessageFactory::MSG_ROOM_OPERATION) {
            continue;
        } else if (!client->isDataLoaded()) {
            // This thread is running even when no data loaded.
            // Thanks to ZMQ subscription, no msg should be received if no data
            // loaded. But, in case of, this will skip it anyway.
            continue;
        }

        // These are only aliases (Compiler should kill them! Ooooh!)
        MsgRoomOperation* msg = static_cast<MsgRoomOperation*>(received);
        const int opID = msg->getOpTypeID();
        const int roomID = msg->getRoomID();

        // Listen only for OP from current room
        // Note: you may receive your own op (ex: Join -> leave -> rejoin room)
        if (roomID == client->getDataID()) {
            const std::string& buffer = msg->getOperationBuffer();
            assert(client->getData() != nullptr);
            client->getData()->applyExternOperation(opID, buffer);
        }

        l_msgFactory.freeMessage(received);
    }
}

// Start running thread that run the SUB socket listening loop.
// WARNING: Call it only once (No check done)
static void runThreadSUB(Client* client) {
    assert(l_socketSUB != nullptr);
    assert(client != nullptr);

    std::thread(listenSocketSUB, client).detach();
}

static void setSubscriptionSUB(Client* client) {
    // TODO tmp (Accept everything for now)
    //      For now, users receive all operation from all rooms!
    //      note however that only the right operation are applied
    //      (But this is not using the ZMQ subscription power...)
    // Unsubscribe all previous subscriptions
    assert(client != nullptr);
    const char* filter = "";
    l_socketSUB->setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));
}

static void resetSubscriptionSUB() {
    // TODO: Check if the subscribe actually work (I'm not sure).
    l_socketSUB->setsockopt(ZMQ_UNSUBSCRIBE, "", strlen(""));
}

// -----------------------------------------------------------------------------
// Client init
// -----------------------------------------------------------------------------

Client::Client() {
    ZMQSocketConfig configREQ = {ZMQ_REQ, &(MessageFactory::getInstance())};
    ZMQSocketConfig configSUB = {ZMQ_SUB, &(MessageFactory::getInstance())};

    l_socketREQ = new ZMQSocket(configREQ);
    l_socketSUB = new ZMQSocket(configSUB);

    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);
}

Client::~Client() {
    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);

    this->leaveData();
    this->disconnect();

    delete l_socketREQ;
    delete l_socketSUB;
    l_socketREQ = nullptr;
    l_socketSUB = nullptr;
}

// -----------------------------------------------------------------------------
// Connection / Disconnect
// -----------------------------------------------------------------------------

bool Client::connect(const char* ip, const int port) {
    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);

    if (this->isConnected()) {
        return false;
    }
    l_socketREQ->connect(ip, port);
    l_socketSUB->connect(ip, COLLABSERVER_CLIENT_SOCKET_SUB_PORT);

    Message* msg = l_msgFactory.newMessage(MessageFactory::MSG_CONNECTION_REQUEST);
    assert(msg != nullptr);
    l_socketREQ->sendMessage(*msg);
    l_msgFactory.freeMessage(msg);

    Message* response = l_socketREQ->receiveMessage();
    assert(response != nullptr);
    if (response->getType() != MessageFactory::MSG_CONNECTION_SUCCESS) {
        l_msgFactory.freeMessage(response);
        this->disconnect();
        return false;
    }

    _userID = static_cast<MsgConnectionSuccess*>(response)->getUserID();

    resetSubscriptionSUB();
    runThreadSUB(this);

    l_msgFactory.freeMessage(response);

    return true;
}

bool Client::disconnect() {
    assert(l_socketREQ != nullptr);
    assert(l_socketSUB != nullptr);

    if (!this->isConnected()) {
        return false;
    } else if (this->isDataLoaded()) {
        this->leaveData();
    }

    Message* req = l_msgFactory.newMessage(MessageFactory::MSG_DISCONNECT_REQUEST);
    assert(req != nullptr);
    static_cast<MsgDisconnectRequest*>(req)->setUserID(_userID);
    l_socketREQ->sendMessage(*req);
    l_msgFactory.freeMessage(req);

    Message* response = l_socketREQ->receiveMessage();
    if (response->getType() != MessageFactory::MSG_DISCONNECT_SUCCESS) {
        l_msgFactory.freeMessage(response);
        return false;
    }

    _userID = 0;

    l_socketSUB->disconnect();
    l_socketREQ->disconnect();

    l_msgFactory.freeMessage(response);

    return true;
}

// -----------------------------------------------------------------------------
// Data
// -----------------------------------------------------------------------------

bool Client::createData(CollabData* data) {
    assert(data != nullptr);
    if (!this->isConnected() || this->isDataLoaded()) {
        return false;
    }

    Message* req = l_msgFactory.newMessage(MessageFactory::MSG_CREA_DATA_REQUEST);
    assert(req != nullptr);
    static_cast<MsgCreaDataRequest*>(req)->setUserID(_userID);
    l_socketREQ->sendMessage(*req);
    l_msgFactory.freeMessage(req);

    Message* response = l_socketREQ->receiveMessage();
    if (response->getType() != MessageFactory::MSG_CREA_DATA_SUCCESS) {
        l_msgFactory.freeMessage(response);
        return false;
    }

    _data = data;
    _dataID = static_cast<MsgCreaDataSuccess*>(response)->getDataID();

    assert(_data != nullptr);
    assert(_dataID != 0);

    resetSubscriptionSUB();
    setSubscriptionSUB(this);
    data->setOperationBroadcaster(*this);

    l_msgFactory.freeMessage(response);

    return true;
}

bool Client::joinData(CollabData* data, unsigned int dataID) {
    assert(data != nullptr);
    assert(dataID > 0);
    if (!this->isConnected() || this->isDataLoaded()) {
        return false;
    }

    // It is actually important to set the SUB socket BEFORE sending the
    // join request. This is because join request will possibly send all the
    // operation done on the data. This is really fast and user may not
    // have received the MSG_JOIN_DATA_SUCCESS yet
    _dataID = dataID;
    _data = data;
    resetSubscriptionSUB();
    setSubscriptionSUB(this);

    Message* req = l_msgFactory.newMessage(MessageFactory::MSG_JOIN_DATA_REQUEST);
    static_cast<MsgJoinDataRequest*>(req)->setUserID(_userID);
    static_cast<MsgJoinDataRequest*>(req)->setDataID(dataID);
    l_socketREQ->sendMessage(*req);
    l_msgFactory.freeMessage(req);

    Message* response = l_socketREQ->receiveMessage();
    if (response->getType() != MessageFactory::MSG_JOIN_DATA_SUCCESS) {
        resetSubscriptionSUB();
        _dataID = 0;
        _data = nullptr;
        l_msgFactory.freeMessage(response);
        return false;
    }

    data->setOperationBroadcaster(*this);

    l_msgFactory.freeMessage(response);

    return true;
}

bool Client::leaveData() {
    if (!this->isConnected() || !this->isDataLoaded()) {
        return false;
    }

    Message* req = l_msgFactory.newMessage(MessageFactory::MSG_LEAVE_DATA_REQUEST);
    static_cast<MsgLeaveDataRequest*>(req)->setUserID(_userID);
    l_socketREQ->sendMessage(*req);
    l_msgFactory.freeMessage(req);

    Message* response = l_socketREQ->receiveMessage();
    if (response->getType() != MessageFactory::MSG_LEAVE_DATA_SUCCESS) {
        l_msgFactory.freeMessage(response);
        return false;
    }

    resetSubscriptionSUB();
    _data->removeOperationBroadcaster();
    _dataID = 0;
    _data = nullptr;

    l_msgFactory.freeMessage(response);

    return true;
}

// -----------------------------------------------------------------------------
// Misc
// -----------------------------------------------------------------------------

bool Client::isUgly() const {
    if (!this->isConnected()) {
        return true;
    }

    Message* req = l_msgFactory.newMessage(MessageFactory::MSG_UGLY);
    static_cast<MsgUgly*>(req)->setUserID(_userID);
    l_socketREQ->sendMessage(*req);
    l_msgFactory.freeMessage(req);

    Message* response = l_socketREQ->receiveMessage();
    if (response->getType() != MessageFactory::MSG_UGLY) {
        l_msgFactory.freeMessage(response);
        return false;
    }

    bool isUgly = static_cast<MsgUgly*>(response)->getResponse();

    l_msgFactory.freeMessage(response);

    return isUgly;
}

// DevNote: remind: this is for op done by the local user.
void Client::onOperation(const CollabDataOperation& op) {
    if (!this->isConnected() || !this->isDataLoaded()) {
        assert(false);  // Should not append (Internal error)
        return;
    }

    std::stringstream opBuffer;
    op.serialize(opBuffer);

    Message* req = l_msgFactory.newMessage(MessageFactory::MSG_ROOM_OPERATION);
    static_cast<MsgRoomOperation*>(req)->setRoomID(_dataID);
    static_cast<MsgRoomOperation*>(req)->setUserID(_userID);
    static_cast<MsgRoomOperation*>(req)->setOpTypeID(op.getType());
    static_cast<MsgRoomOperation*>(req)->setOperationBuffer(opBuffer.str());

    l_socketREQ->sendMessage(*req);
    l_msgFactory.freeMessage(req);

    Message* response = l_socketREQ->receiveMessage();
    if (response->getType() != MessageFactory::MSG_EMPTY) {
        l_msgFactory.freeMessage(response);
        return;
    }

    l_msgFactory.freeMessage(response);
}

}  // namespace collabserver
