//
// Created by 残梦 on 2025/9/6.
//

#include "ChatInput.h"

ChatInput::ChatInput(QWidget *parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    _main_layout=new QVBoxLayout;
    _main_layout->setContentsMargins(0,0,10,10);
    this->setLayout(_main_layout);
    _main_layout->setAlignment(Qt::AlignTop);
    _main_layout->setAlignment(Qt::AlignCenter);

    _tool_bar=new YumeTitleBar(this);
    _tool_bar->x()->hide();
    _main_layout->addWidget(_tool_bar);



    _message_input=new QTextEdit(this);
    _message_input->setStyleSheet("QTextEdit { background: transparent; border: none; }");
    _main_layout->addWidget(_message_input);

    _send_button=new YumeButton(this);
    _send_button->setText("发送");
    _send_button->setFixedWidth(80);
    _send_button->setFixedHeight(25);
    _send_button->label()->set_font_color(Qt::white);



    _main_layout->addWidget(_send_button,0,Qt::AlignRight);


    connect(_send_button,&YumeButton::clicked,this,&ChatInput::send_button_clicked);
}

void ChatInput::send_button_clicked()
{
    _message_input->clear();
    emit _message_send();
}
