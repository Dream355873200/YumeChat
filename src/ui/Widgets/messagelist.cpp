//
// Created by 残梦 on 2025/8/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MessageList.h" resolved

#include "messagelist.h"
#include<QScrollBar>

MessageList::MessageList(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(220);
    _main_layout=new QVBoxLayout;
    _main_layout->setAlignment(Qt::AlignCenter);
    this->setLayout(_main_layout);
    _main_layout->setAlignment(Qt::AlignCenter);
    _main_layout->setContentsMargins(0,0,0,0);

    _list=new SmoothListWidget(this);

    buttonGroup= new QButtonGroup(this);
    buttonGroup->setExclusive(true);


    _label=new YumeLabel(this);
    _label->set_text("Message");
    _label->setAlignment(Qt::AlignCenter);
    _label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _main_layout->addWidget(_label);
    _main_layout->addWidget(_list);

    _messagewidget=new messagewidget(this,"Yume","你好","18:30");
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(_messagewidget->sizeHint().width(),60) );
    _list->addItem(item);
    _list->setItemWidget(item, _messagewidget);
    buttonGroup->addButton(_messagewidget, 0);
    for(int i=0;i<20;i++)
    {
        auto test=new messagewidget(this,"Yume","你好","18:30");
        QListWidgetItem *t_item = new QListWidgetItem();
        t_item->setSizeHint(QSize(test->sizeHint().width(),60) );
        _list->addItem(t_item);
        _list->setItemWidget(t_item, test);
        buttonGroup->addButton(test, i+1);
    }
}

MessageList::~MessageList()
{
}






