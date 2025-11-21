//
// Created by 残梦 on 2025/11/21.
//

#include "MessageMgr.h"

MessageMgr::~MessageMgr()
{
}

MessageMgr::MessageMgr()
{
}

void MessageMgr::message_divided(const std::shared_ptr<message::MsgNode> &message)
{
    if(message->meta().type()!=message::UNKNOWN)
    {
        emit chat_message(message->meta().conversation_id(),message);
    }

}
