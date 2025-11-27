//
// Created by 残梦 on 2025/11/21.
//

#include "ConversationWidget.h"

ConversationWidget::ConversationWidget(QWidget* parent)
    :QWidget(parent)
{
    _main_layout=new QVBoxLayout;
    this->setLayout(_main_layout);
    _main_layout->setContentsMargins(0,0,0,0);

    _area=new ChatArea(this);
    _input=new ChatInput(this);
    _top=new ChatTop(this);

    _main_layout->addWidget(_top,1);
    _main_layout->addWidget(_area,3);
    _main_layout->addWidget(_input,1);
    _main_layout->setSpacing(0);
    for(int i=0;i<20;i++)
    {
        auto *test=new MessageItem(this);
        QPixmap addd;
        addd.load(":Resource/ico/yume.jpg");
        test->set_avatar(addd);
        test->set_text("111");
        test->set_name("Yume");

        test->set_mode(ItemMode::Other);
        _area->add_bubble(test);
    }

    _self_avatar.load(":Resource/ico/yume.jpg");
}

ConversationWidget::~ConversationWidget()
{
}

void ConversationWidget::add_message_item(const std::string &conversation_id,
    const message::MsgNode& message)
{
    MessageItem* item = nullptr;
    if(conversation_id == _conversation_id)
    {
        item = new MessageItem(this, _conversation_avatar, _conversation_name, message.text().data());
        _area->add_bubble(item);
    }
     if(conversation_id == Global_id.toStdString())
    {
        qDebug() << message.meta().sender_id();
        item = new MessageItem(this, _self_avatar, _self_name, message.text().data());
        item->set_mode(ItemMode::Self);
        _area->add_bubble(item);
    }



}
