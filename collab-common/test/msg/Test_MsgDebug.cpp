#include "collabcommon/messaging/MessageList.h"

#include <sstream>
#include <gtest/gtest.h>

namespace collab {


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


} // End namespace


