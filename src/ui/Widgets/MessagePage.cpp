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
    _v_layout=new QVBoxLayout;


    _list=new MessageList(this);
    _area=new ChatArea(this);
    _input=new ChatInput(this);

    _v_layout->addWidget(_area,3);
    _v_layout->addWidget(_input,1);
    _v_layout->setSpacing(0);
    _v_layout->setContentsMargins(0,0,0,0);

    _main_layout->addWidget(_list);
    _main_layout->addLayout(_v_layout);


    for(int i=0;i<20;i++)
    {
        auto *test=new MessageItem(this);
        QPixmap addd;
        addd.load(":Resource/ico/yume.jpg");
        test->set_avatar(addd);
        test->set_text("aaaaaAAAAAaa啊啊aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa啊aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        test->set_name("Yume");
        _area->add_bubble(test);
    }

}
