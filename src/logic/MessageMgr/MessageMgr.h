//
// Created by 残梦 on 2025/11/21.
//

#ifndef MESSAGEMGR_H
#define MESSAGEMGR_H
#include <QObject>
#include <qobjectdefs.h>
#include <qtmetamacros.h>

#include "Singleton/Singleton.h"
#include "../../../Message.pb.h"


class MessageMgr:public QObject,public Singleton<MessageMgr>
{
    Q_OBJECT
    friend class Singleton;
public:
    ~MessageMgr();
private:
    MessageMgr();

public slots:
    void message_divided(const std::shared_ptr<message::MsgNode>& message);

    signals:
    void chat_message(const std::string& conversation_id,const std::shared_ptr<message::MsgNode>& message);
};



#endif //MESSAGEMGR_H
