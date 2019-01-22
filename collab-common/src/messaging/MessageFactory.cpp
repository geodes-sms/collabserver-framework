#include "collabcommon/messaging/MessageFactory.h"

#include <cassert>

#include "collabcommon/messaging/Message.h"
#include "collabcommon/messaging/MessageList.h"

namespace collab {


Message* MessageFactory::newMessage(const unsigned int type) const {
    switch(type) {
        // Connection
        case MSG_CONNECTION_REQUEST:
            return new MsgConnectionRequest();
        case MSG_CONNECTION_SUCCESS:
            return new MsgConnectionSuccess();
        case MSG_DISCONNECT_REQUEST:
            return new MsgDisconnectRequest();
        case MSG_DISCONNECT_SUCCESS:
            return new MsgDisconnectSuccess();

        // Data
        case MSG_CREA_DATA_REQUEST:
            return new MsgCreaDataRequest();
        case MSG_CREA_DATA_SUCCESS:
            return new MsgCreaDataSuccess();
        case MSG_JOIN_DATA_REQUEST:
            return new MsgJoinDataRequest();
        case MSG_JOIN_DATA_SUCCESS:
            return new MsgJoinDataSuccess();
        case MSG_LEAVE_DATA_REQUEST:
            return new MsgLeaveDataRequest();
        case MSG_LEAVE_DATA_SUCCESS:
            return new MsgLeaveDataSuccess();

        // Room
        case MSG_ROOM_OPERATION:
            return new MsgRoomOperation();

        // Various
        case MSG_ERROR:
            return new MsgError();
        case MSG_DEBUG:
            return new MsgDebug();
        case MSG_UGLY:
            return new MsgUgly();
        case MSG_EMPTY:
            return new MsgEmpty();

        default:
            return nullptr;
    }
}

void MessageFactory::freeMessage(Message* msg) const {
    assert(msg != nullptr);
    if(msg != nullptr) {
        delete msg;
    }
}


}  // End namespace


