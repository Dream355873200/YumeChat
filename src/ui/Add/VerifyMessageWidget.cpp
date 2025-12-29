//
// Created by 残梦 on 2025/12/23.
//

#include "VerifyMessageWidget.h"

VerifyMessageWidget::VerifyMessageWidget(QWidget* parent,const QString& conversation_id)
    :QWidget(parent),_conversation_id(conversation_id)
{
    this->setFixedHeight(50);

    _main_layout=new QHBoxLayout;
    this->setLayout(_main_layout);
    _main_layout->setContentsMargins(5,5,15,5);

    _name=new YumeLabel(this);
    _name->setAttribute(Qt::WA_TransparentForMouseEvents);

    _avatar=new CircleAvatar(this);
    _split_button=new SplitButton(this);
    _name->setText("Yume");
    _split_button->setFixedSize(70,30);
    _main_layout->addWidget(_avatar,Qt::AlignLeft);
    _main_layout->addWidget(_name,Qt::AlignLeft|Qt::AlignTop);
    _main_layout->addWidget(_split_button,Qt::AlignRight);
    _main_layout->setAlignment(Qt::AlignCenter);

    _split_button->setText("同意");

    _split_button->addMenuButton("拒绝",[]()
    {

    });

}

VerifyMessageWidget::~VerifyMessageWidget()
{

}

void VerifyMessageWidget::set_name(const QString &name)
{
    _name->setText(name);
}

void VerifyMessageWidget::set_avatar(const QPixmap &avatar)
{
    _avatar->set_icon(avatar);
}
