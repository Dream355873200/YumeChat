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
public:
    ConversationWidget(QWidget* parent=nullptr);
    ~ConversationWidget();
private:
    QVBoxLayout* _main_layout;
    ChatArea* _area;
    ChatInput* _input;
    ChatTop* _top;
    std::string conversation_id;
};



#endif //CONVERSATIONWIDGET_H
