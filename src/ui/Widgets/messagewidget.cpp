//
// Created by 残梦 on 2025/8/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_messagewidget.h" resolved

#include "messagewidget.h"


messagewidget::messagewidget(QWidget *parent) : YumeButton(parent)
{
    _v_layout1=new QVBoxLayout;
    _v_layout2=new QVBoxLayout;
    main_layout()->addLayout(_v_layout1);
    main_layout()->addLayout(_v_layout2);

    _v_layout1->setAlignment(Qt::AlignLeft);
    _v_layout2->setAlignment(Qt::AlignRight);



}

messagewidget::messagewidget(const QString &name, const QString &last_message, const QString &time)
{
    _v_layout1=new QVBoxLayout;
    _v_layout2=new QVBoxLayout;
    main_layout()->addLayout(_v_layout1);
    main_layout()->addLayout(_v_layout2);

    _v_layout1->setAlignment(Qt::AlignLeft);
    _v_layout2->setAlignment(Qt::AlignRight);

    _v_layout1->addWidget(_name);
    _v_layout1->addWidget(_last_message);

    _v_layout2->addWidget(_time);

    _name->set_text(name);
    _last_message->set_text(last_message);
    _time->set_text(time);

    connect(this,&YumeButton::clicked,[this]()
    {
        if (unread_num > 0) {
         unread_num = 0;
         _message_num->hide();  // 隐藏而非移除
     }
    });
}

messagewidget::~messagewidget()
{
}

void messagewidget::unread_num_add()
{
    unread_num++;
    _message_num->set_text(QString::number(unread_num));
    // 首次增加未读消息时显示红点
    if (unread_num == 1) {
        _message_num->show();
    }
}