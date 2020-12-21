#pragma once

#include <sstream>

#include "collabserver/network/messaging/Message.h"
#include "collabserver/network/messaging/MessageFactory.h"

namespace collabserver {

// -----------------------------------------------------------------------------
// Connection Messages
// -----------------------------------------------------------------------------

class MsgConnectionRequest : public Message {
   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    unsigned int getType() const override { return MessageFactory::MSG_CONNECTION_REQUEST; }
};

class MsgConnectionSuccess : public Message {
   private:
    unsigned int _userID;  // ID the server gave to the user just connected.
   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setUserID(const unsigned int id) { _userID = id; }
    unsigned int getUserID() const { return _userID; }
    unsigned int getType() const override { return MessageFactory::MSG_CONNECTION_SUCCESS; }
};

class MsgDisconnectRequest : public Message {
   private:
    unsigned int _userID;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setUserID(const unsigned int id) { _userID = id; }
    unsigned int getUserID() const { return _userID; }
    unsigned int getType() const override { return MessageFactory::MSG_DISCONNECT_REQUEST; }
};

class MsgDisconnectSuccess : public Message {
   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    unsigned int getType() const override { return MessageFactory::MSG_DISCONNECT_SUCCESS; }
};

// -----------------------------------------------------------------------------
// Data Messages
// -----------------------------------------------------------------------------

class MsgCreaDataRequest : public Message {
   private:
    unsigned int _userID;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setUserID(const unsigned int id) { _userID = id; }
    unsigned int getUserID() const { return _userID; }
    unsigned int getType() const override { return MessageFactory::MSG_CREA_DATA_REQUEST; }
};

class MsgCreaDataSuccess : public Message {
   private:
    unsigned int _dataID;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setDataID(const unsigned int id) { _dataID = id; }
    unsigned int getDataID() const { return _dataID; }
    unsigned int getType() const override { return MessageFactory::MSG_CREA_DATA_SUCCESS; }
};

class MsgJoinDataRequest : public Message {
   private:
    unsigned int _userID;
    unsigned int _dataID;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setUserID(const unsigned int id) { _userID = id; }
    void setDataID(const unsigned int id) { _dataID = id; }
    unsigned int getUserID() const { return _userID; }
    unsigned int getDataID() const { return _dataID; }
    unsigned int getType() const override { return MessageFactory::MSG_JOIN_DATA_REQUEST; }
};

class MsgJoinDataSuccess : public Message {
   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    unsigned int getType() const override { return MessageFactory::MSG_JOIN_DATA_SUCCESS; }
};

class MsgLeaveDataRequest : public Message {
   private:
    unsigned int _userID;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setUserID(const unsigned int id) { _userID = id; }
    unsigned int getUserID() const { return _userID; }
    unsigned int getType() const override { return MessageFactory::MSG_LEAVE_DATA_REQUEST; }
};

class MsgLeaveDataSuccess : public Message {
   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    unsigned int getType() const override { return MessageFactory::MSG_LEAVE_DATA_SUCCESS; }
};

// -----------------------------------------------------------------------------
// Room
// -----------------------------------------------------------------------------

class MsgRoomOperation : public Message {
   private:
    unsigned int _roomID;
    unsigned int _userID;
    unsigned int _opTypeID;
    std::string _opBuffer;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setRoomID(const unsigned int id) { _roomID = id; }
    void setUserID(const unsigned int id) { _userID = id; }
    void setOpTypeID(const unsigned int id) { _opTypeID = id; }
    unsigned int getRoomID() const { return _roomID; }
    unsigned int getUserID() const { return _userID; }
    unsigned int getOpTypeID() const { return _opTypeID; }
    void setOperationBuffer(const std::string& buff) { _opBuffer = buff; }
    const std::string& getOperationBuffer() const { return _opBuffer; }
    unsigned int getType() const override { return MessageFactory::MSG_ROOM_OPERATION; }
};

// -----------------------------------------------------------------------------
// Various / Debug / Error Messages
// -----------------------------------------------------------------------------

class MsgDebug : public Message {
   private:
    std::string _content;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setContent(const std::string& str) { _content = str; }
    const std::string& getContent() const { return _content; }
    unsigned int getType() const override { return MessageFactory::MSG_DEBUG; }
};

class MsgError : public Message {
   private:
    unsigned int _errorID;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setErrorID(const unsigned int id) { _errorID = id; }
    unsigned int getErrorID() const { return _errorID; }
    unsigned int getType() const override { return MessageFactory::MSG_ERROR; }
};

class MsgUgly : public Message {
   private:
    unsigned int _userID;
    bool _response;

   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    void setUserID(const unsigned int id) { _userID = id; }
    unsigned int getUserID() const { return _userID; }
    void setResponse(bool value) { _response = value; }
    bool getResponse() const { return _response; }
    unsigned int getType() const override { return MessageFactory::MSG_UGLY; }
};

class MsgEmpty : public Message {
   public:
    bool serialize(std::stringstream& buffer) const override;
    bool unserialize(std::stringstream& buffer) override;
    unsigned int getType() const override { return MessageFactory::MSG_EMPTY; }
};

}  // namespace collabserver
