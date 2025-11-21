//
// Created by 残梦 on 2025/10/15.
//

#include "FriendPage.h"

FriendPage::FriendPage(QWidget *parent)
    :QWidget(parent)
{
    _main_layout=new QHBoxLayout;
    this->setLayout(_main_layout);
    _main_layout->setContentsMargins(0,0,0,0);
    _main_layout->setAlignment(Qt::AlignLeft);

    _friend_list=new FriendList(this);
    _main_layout->addWidget(_friend_list);


}

FriendPage::~FriendPage()
{
}
