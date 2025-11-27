//
// Created by 残梦 on 2025/11/21.
//

#ifndef CONVERSATIONWIDGET_H
#define CONVERSATIONWIDGET_H
#include "ChatArea.h"
#include "ChatInput.h"
#include "ChatTop.h"
#include "FriendWidget.h"


class ConversationWidget:public QWidget
{
    Q_OBJECT
    friend class ChatInput;
public:
    ConversationWidget(QWidget* parent=nullptr);
    ~ConversationWidget();
private:
    QVBoxLayout* _main_layout;
    ChatArea* _area;
    ChatInput* _input;
    ChatTop* _top;
    QString _conversation_name;
    QPixmap _conversation_avatar;
    QString _self_name="Yume";
    QPixmap _self_avatar;
    std::string _conversation_id;

public slots:
    void add_message_item(const std::string& conversation_id,const message::MsgNode& message);
};



#endif //CONVERSATIONWIDGET_H
