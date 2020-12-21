#include <gtest/gtest.h>

#include <sstream>

#include "collabserver/network/messaging/MessageList.h"

namespace collabserver {

// -----------------------------------------------------------------------------
// serialize / unserialize
// -----------------------------------------------------------------------------

TEST(MsgConnectionSuccess, serializeUnserialize) {
    MsgConnectionSuccess msg1;
    MsgConnectionSuccess msg2;
    MsgConnectionSuccess msg3;

    std::stringstream buffer1;
    std::stringstream buffer2;
    std::stringstream buffer3;

    msg1.setUserID(42);
    msg2.setUserID(2048);
    msg3.setUserID(65536);

    msg1.serialize(buffer1);
    msg2.serialize(buffer2);
    msg3.serialize(buffer3);

    MsgConnectionSuccess msg1_resp;
    MsgConnectionSuccess msg2_resp;
    MsgConnectionSuccess msg3_resp;

    msg1_resp.unserialize(buffer1);
    msg2_resp.unserialize(buffer2);
    msg3_resp.unserialize(buffer3);

    ASSERT_EQ(msg1_resp.getUserID(), msg1.getUserID());
    ASSERT_EQ(msg2_resp.getUserID(), msg2.getUserID());
    ASSERT_EQ(msg3_resp.getUserID(), msg3.getUserID());
}

}  // namespace collabserver
