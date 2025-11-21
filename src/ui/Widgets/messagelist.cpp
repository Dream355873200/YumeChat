//
// Created by 残梦 on 2025/8/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MessageList.h" resolved

#include "messagelist.h"

#include <QFontDatabase>
#include<QScrollBar>

#include "FriendWidget.h"

MessageList::MessageList(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(width);

    _main_layout=new QVBoxLayout;
    _main_layout->setAlignment(Qt::AlignCenter);
    this->setLayout(_main_layout);
    _main_layout->setAlignment(Qt::AlignCenter);
    _main_layout->setContentsMargins(0,0,0,0);

    _list=new SmoothListWidget(this);
    buttonGroup= new QButtonGroup(this);
    buttonGroup->setExclusive(true);

    _search=new SearchWidget(this);
    _search->set_text("Message");


    _main_layout->addWidget(_search);
    _main_layout->addWidget(_list);


    _messagewidget=new messagewidget(this,"Yume","你好","18:30");
    _messagewidget->setFixedWidth(width-10);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(_messagewidget->sizeHint().width(),60) );
    _list->addItem(item);
    _list->setItemWidget(item, _messagewidget);
    buttonGroup->addButton(_messagewidget, button_num++);
    for(int i=0;i<20;i++)
    {
        auto test=new messagewidget(this,"Yume","你好aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaawwwwwwwwwwwwwwwwwww","18:30");
        test->setFixedWidth(width-20);
        QListWidgetItem *t_item = new QListWidgetItem();
        QWidget* container = new QWidget(this);
        container->setFixedWidth(width-10);
        QHBoxLayout* containerLayout = new QHBoxLayout(container);
        containerLayout->setAlignment(Qt::AlignCenter);
        containerLayout->setContentsMargins(0, 0, 0, 0);
        containerLayout->addWidget(test);

        t_item->setSizeHint(QSize(test->sizeHint().width(), 60));

        _list->addItem(t_item);
        _list->setItemWidget(t_item, container);  // 将容器设置为item的widget
        buttonGroup->addButton(test, button_num++);
    }
}

MessageList::~MessageList()
{
}

void MessageList::add_message_widget()
{
    auto test=new messagewidget(this,"Yume","你好","18:30");
    QListWidgetItem *t_item = new QListWidgetItem();
    QWidget* container = new QWidget(this);
    container->setFixedWidth(width-10);
    QHBoxLayout* containerLayout = new QHBoxLayout(container);
    containerLayout->setAlignment(Qt::AlignCenter);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->addWidget(test);

    t_item->setSizeHint(QSize(test->sizeHint().width(), 60));

    _list->addItem(t_item);
    _list->setItemWidget(t_item, container);  // 将容器设置为item的widget



    buttonGroup->addButton(test, button_num++);
}






