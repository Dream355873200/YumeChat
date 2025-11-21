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
        test->set_text("aaaaaAAAAAaa啊啊aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa啊aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        test->set_name("Yume");
        test->set_mode(ItemMode::Self);
        test->set_mode(ItemMode::Other);
        _area->add_bubble(test);
    }
}

ConversationWidget::~ConversationWidget()
{
}
