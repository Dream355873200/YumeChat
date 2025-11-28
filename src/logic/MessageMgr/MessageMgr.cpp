//
// Created by 残梦 on 2025/11/21.
//

#include "MessageMgr.h"

#include "logic/Global/global.h"
#include "logic/TcpMgr/TcpMgr.h"

MessageMgr::~MessageMgr()
{
}

MessageMgr::MessageMgr()
{

    connect(TcpMgr::GetInstance().get(),&TcpMgr::message_receive_success,this,&MessageMgr::message_divided);
}

void MessageMgr::message_divided(const message::MsgNode& message)
{
    if(message.meta().type()!=message::UNKNOWN&&message.meta().conversation_id()==Global_id)
    {
        emit chat_message(message.meta().sender_id(),message);
    }

}
