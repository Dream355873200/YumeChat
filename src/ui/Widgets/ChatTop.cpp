//
// Created by 残梦 on 2025/11/17.
//

#include "ChatTop.h"

ChatTop::ChatTop(QWidget* parent,const QString& name)
    :QWidget(parent)
{
    _main_layout=new QHBoxLayout;
    _main_layout->setContentsMargins(0,0,0,0);
    this->setLayout(_main_layout);
    this->setFixedHeight(30);

    _name=new YumeLabel(this);
    _name->setContentsMargins(10,0,40,5);
    _main_layout->addWidget(_name);
    _name->set_text(name);
    _name->setAlignment(Qt::AlignCenter);
    _name->setAlignment(Qt::AlignLeft);
    _name->set_font_size(18);
    _name->set_font_type(":/Resource/font/flache.ttf");
    _name->setCursor(Qt::CustomCursor);

}

ChatTop::~ChatTop()
{
}
