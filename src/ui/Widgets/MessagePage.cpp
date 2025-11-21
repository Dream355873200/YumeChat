//
// Created by 残梦 on 2025/9/4.
//

#include "MessagePage.h"

#include "ChatInput.h"

MessagePage::MessagePage(QWidget *parent)
    :QWidget(parent)
{
    _main_layout=new QHBoxLayout;
    this->setLayout(_main_layout);
    _main_layout->setContentsMargins(0,0,0,0);


    _con=new ConversationWidget(this);

    _list=new MessageList(this);


    _main_layout->addWidget(_list);
    _main_layout->addWidget(_con);



}
