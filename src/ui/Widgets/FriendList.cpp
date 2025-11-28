//
// Created by 残梦 on 2025/10/15.
//

#include "FriendList.h"
//
// Created by 残梦 on 2025/8/31.

// You may need to build the project (run Qt uic code generator) to get "ui_MessageList.h" resolved

#include "messagelist.h"
#include<QScrollBar>

#include "FriendWidget.h"

FriendList::FriendList(QWidget *parent)
    : QWidget(parent)
{


    //调用tcp去请求获取服务器friends列表信息，存入数据库



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
    _search->set_text("Friend");


    _main_layout->addWidget(_search);
    _main_layout->addWidget(_list);

    QString data="123456";

    _friendwidget=new FriendWidget(this,"Yume",data.toStdString());
    _friendwidget->setFixedWidth(width-10);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,data);
    item->setSizeHint(QSize(_friendwidget->sizeHint().width(),60) );
    _list->addItem(item);
    _list->setItemWidget(item, _friendwidget);
    buttonGroup->addButton(_friendwidget, button_num++);
    for(int i=0;i<20;i++)
    {
        auto test=new FriendWidget(this,"Yume",data.toStdString());
        test->setFixedWidth(width-10);
        QListWidgetItem *t_item = new QListWidgetItem();
        t_item->setData(Qt::UserRole,data);
        
        t_item->setSizeHint(QSize(test->sizeHint().width(),60) );
        _list->addItem(t_item);
        _list->setItemWidget(t_item, test);
        buttonGroup->addButton(test, button_num++);
    }
}

FriendList::~FriendList()
{
}

void FriendList::add_friend_widget()
{
    auto test=new FriendWidget(this,"Yume","123456");
    test->setFixedWidth(width-10);
    QListWidgetItem *t_item = new QListWidgetItem();
    t_item->setSizeHint(QSize(test->sizeHint().width(),60) );
    _list->addItem(t_item);
    _list->setItemWidget(t_item, test);
    buttonGroup->addButton(test, button_num++);
}







