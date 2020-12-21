#include <gtest/gtest.h>

#include <sstream>

#include "collabserver/network/messaging/MessageList.h"

namespace collabserver {

// -----------------------------------------------------------------------------
// serialize / unserialize
// -----------------------------------------------------------------------------

TEST(MsgDebug, serializeUnserialize) {
    MsgDebug msg;
    MsgDebug msg_resp;

    std::stringstream buffer;
    msg.setContent("Ellie");
    msg.serialize(buffer);

    msg_resp.unserialize(buffer);
    ASSERT_EQ(msg_resp.getContent(), msg.getContent());
}

}  // namespace collabserver
