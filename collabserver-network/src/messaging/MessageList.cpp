#include "collabserver/network/messaging/MessageList.h"

#include <cassert>
#include <msgpack.hpp>
#include <sstream>

namespace collabserver {

// -----------------------------------------------------------------------------
// Connection Messages
// -----------------------------------------------------------------------------

bool MsgConnectionRequest::serialize(std::stringstream& buffer) const { return true; }

bool MsgConnectionRequest::unserialize(std::stringstream& buffer) { return true; }

bool MsgConnectionSuccess::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _userID);
    return true;
}

bool MsgConnectionSuccess::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_userID);

    assert(off == size);
    return off == size;
}

bool MsgDisconnectRequest::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _userID);
    return true;
}

bool MsgDisconnectRequest::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_userID);

    assert(off == size);
    return off == size;
}

bool MsgDisconnectSuccess::serialize(std::stringstream& buffer) const { return true; }

bool MsgDisconnectSuccess::unserialize(std::stringstream& buffer) { return true; }

// -----------------------------------------------------------------------------
// Data Messages
// -----------------------------------------------------------------------------

bool MsgCreaDataRequest::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _userID);
    return true;
}

bool MsgCreaDataRequest::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_userID);

    assert(off == size);
    return off == size;
}

bool MsgCreaDataSuccess::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _dataID);
    return true;
}

bool MsgCreaDataSuccess::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_dataID);

    assert(off == size);
    return off == size;
}

bool MsgJoinDataRequest::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _userID);
    msgpack::pack(buffer, _dataID);
    return true;
}

bool MsgJoinDataRequest::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    msgpack::unpacked r2 = msgpack::unpack(data, size, off);

    r1.get().convert(_userID);
    r2.get().convert(_dataID);

    assert(off == size);
    return off == size;
}

bool MsgJoinDataSuccess::serialize(std::stringstream& buffer) const { return true; }

bool MsgJoinDataSuccess::unserialize(std::stringstream& buffer) { return true; }

bool MsgLeaveDataRequest::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _userID);
    return true;
}

bool MsgLeaveDataRequest::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_userID);

    assert(off == size);
    return off == size;
}

bool MsgLeaveDataSuccess::serialize(std::stringstream& buffer) const { return true; }

bool MsgLeaveDataSuccess::unserialize(std::stringstream& buffer) { return true; }

// -----------------------------------------------------------------------------
// Room
// -----------------------------------------------------------------------------

bool MsgRoomOperation::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _roomID);
    msgpack::pack(buffer, _userID);
    msgpack::pack(buffer, _opTypeID);
    msgpack::pack(buffer, _opBuffer);

    return true;
}

bool MsgRoomOperation::unserialize(std::stringstream& buffer) {
    std::string str(buffer.str());
    std::size_t off = 0;

    msgpack::object_handle r1 = msgpack::unpack(str.data(), str.size(), off);
    msgpack::object_handle r2 = msgpack::unpack(str.data(), str.size(), off);
    msgpack::object_handle r3 = msgpack::unpack(str.data(), str.size(), off);
    msgpack::object_handle r4 = msgpack::unpack(str.data(), str.size(), off);

    r1.get().convert(_roomID);
    r2.get().convert(_userID);
    r3.get().convert(_opTypeID);
    r4.get().convert(_opBuffer);

    assert(off == str.size());
    return off == str.size();
}

// -----------------------------------------------------------------------------
// Various / Debug / Error Messages
// -----------------------------------------------------------------------------

bool MsgDebug::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _content);
    return true;
}

bool MsgDebug::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_content);

    assert(off == size);
    return off == size;
}

bool MsgError::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _errorID);
    return true;
}

bool MsgError::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    r1.get().convert(_errorID);

    assert(off == size);
    return off == size;
}

bool MsgUgly::serialize(std::stringstream& buffer) const {
    msgpack::pack(buffer, _userID);
    msgpack::pack(buffer, _response);
    return true;
}

bool MsgUgly::unserialize(std::stringstream& buffer) {
    const char* data = buffer.str().data();
    const size_t size = buffer.str().size();
    std::size_t off = 0;

    msgpack::unpacked r1 = msgpack::unpack(data, size, off);
    msgpack::unpacked r2 = msgpack::unpack(data, size, off);

    r1.get().convert(_userID);
    r2.get().convert(_response);

    assert(off == size);
    return off == size;
}

bool MsgEmpty::serialize(std::stringstream& buffer) const { return true; }

bool MsgEmpty::unserialize(std::stringstream& buffer) { return true; }

}  // namespace collabserver
