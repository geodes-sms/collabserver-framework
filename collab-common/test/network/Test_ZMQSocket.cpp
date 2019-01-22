#include "collabcommon/network/ZMQSocket.h"

#include <gtest/gtest.h>
#include "collabcommon/messaging/MessageFactory.h"

namespace collab {


ZMQSocketConfig conf {
    ZMQ_REP,
    &MessageFactory::getInstance()
};


TEST(ZMQSocket, constructor_OnStack) {
    ZMQSocket coco(conf);
    ZMQSocket carrot(conf);
    ZMQSocket rabbit(conf);
}

TEST(ZMQSocket, constructor_OnHead) {
    ZMQSocket *coco = new ZMQSocket(conf);
    ZMQSocket *ellie = new ZMQSocket(conf);
    ASSERT_NE(coco, nullptr);
    ASSERT_NE(ellie, nullptr);
    delete coco;
    delete ellie;
}


} // End namespace


