#include <gtest/gtest.h>

#include <sstream>

#include "collabserver/network/messaging/MessageList.h"

namespace collabserver {

// -----------------------------------------------------------------------------
// MsgRoomOperation
// -----------------------------------------------------------------------------

TEST(MsgRoomOperation, serializeUnserialize) {
    MsgRoomOperation msg1;
    const char* opBuffer1 = "ThisIsTheOperationBuffer Operation ONE";
    msg1.setRoomID(8);
    msg1.setUserID(4);
    msg1.setOpTypeID(1);
    msg1.setOperationBuffer(opBuffer1);

    MsgRoomOperation msg2;
    const char* opBuffer2 = "ThisIsTheOperationBuffer Operation ONE";
    msg2.setRoomID(256);
    msg2.setUserID(512);
    msg2.setOpTypeID(900);
    msg2.setOperationBuffer(opBuffer2);

    std::stringstream buffer1;
    std::stringstream buffer2;
    msg1.serialize(buffer1);
    msg2.serialize(buffer2);

    // Simulate send buffer
    buffer1.seekg(0);
    buffer2.seekg(0);

    msg1.unserialize(buffer2);
    msg2.unserialize(buffer1);

    ASSERT_EQ(msg1.getRoomID(), 256);
    ASSERT_EQ(msg1.getUserID(), 512);
    ASSERT_EQ(msg1.getOpTypeID(), 900);
    ASSERT_EQ(msg1.getOperationBuffer(), opBuffer2);

    ASSERT_EQ(msg2.getRoomID(), 8);
    ASSERT_EQ(msg2.getUserID(), 4);
    ASSERT_EQ(msg2.getOpTypeID(), 1);
    ASSERT_EQ(msg2.getOperationBuffer(), opBuffer1);
}

}  // namespace collabserver
