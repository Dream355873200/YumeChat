//
// Created by 残梦 on 2025/9/3.
//

#include "MessageItem.h"


MessageItem::MessageItem(QWidget *parent)
    :QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    _main_layout=new QHBoxLayout;
    _main_layout->setAlignment(Qt::AlignTop);
    _main_layout->setContentsMargins(0,0,120,0);
    this->setLayout(_main_layout);

    _name=new YumeLabel(this);
    _name->setAttribute(Qt::WA_TransparentForMouseEvents);
    _name->setAlignment(Qt::AlignRight);

    _bubble=new YumeBubble(this);



    _avatar=new CircleAvatar(this);
    _main_layout->addWidget(_avatar, 0, Qt::AlignTop);

    _v_layout=new QVBoxLayout;
    _v_layout->setAlignment(Qt::AlignTop);
    _main_layout->addLayout(_v_layout);
    _v_layout->addWidget(_name);
    _v_layout->addWidget(_bubble);

    _bubble_layout=new QHBoxLayout;
    _bubble_layout->addStretch();
    _bubble_layout->addWidget(_bubble);


    _v_layout->addWidget(_name);
    _v_layout->addLayout(_bubble_layout);

}



MessageItem::MessageItem(QWidget *parent, const QPixmap &avatar, const QString &name, const QString &text)
    :QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    _name=new YumeLabel(this);
    _name->setAttribute(Qt::WA_TransparentForMouseEvents);
    _name->set_text(name);

    _avatar=new CircleAvatar(this);
    _avatar->set_icon(avatar);

    _bubble=new YumeBubble(this);
    _bubble->set_text(text);

    _main_layout=new QHBoxLayout;
    _main_layout->setAlignment(Qt::AlignTop);
    _main_layout->setContentsMargins(5,15,0,5);
    this->setLayout(_main_layout);
    _main_layout->addWidget(_avatar, 0, Qt::AlignTop);



    _v_layout=new QVBoxLayout;
    _v_layout->setContentsMargins(0,0,0,0);
    _v_layout->setAlignment(Qt::AlignTop);
    _main_layout->addLayout(_v_layout);

    _bubble_layout=new QHBoxLayout;
    _bubble_layout->addStretch();
    _bubble_layout->addWidget(_bubble);


    _v_layout->addWidget(_name);
    _v_layout->addLayout(_bubble_layout);



}

void MessageItem::set_avatar(const QPixmap &avatar)
{
    _avatar->set_icon(avatar);
}

void MessageItem::set_name(const QString &name)
{
    _name->set_text(name);
}

void MessageItem::set_text(const QString &text)
{
    _bubble->set_text(text);
}

void MessageItem::set_mode(const ItemMode &mode)
{
    // 先清空布局但保留控件
    QLayoutItem* avatarItem = nullptr;
    QLayoutItem* vLayoutItem = nullptr;
    QLayoutItem* bubbleItem=nullptr;
    // 保存布局项
    while (_main_layout->count() >0)
    {
        QLayoutItem* temp =  _main_layout->takeAt(0);
        if(temp->widget()&&temp->widget()==_avatar)
        {
            avatarItem = temp;
        }
        else if(temp->layout()&&temp->layout()==_v_layout)
        {
            vLayoutItem = temp;
        }
        else
        {
            delete temp;
        }
    }

        while (_bubble_layout->count() > 0)
        {
            QLayoutItem* temp = _bubble_layout->takeAt(0);
            if(temp->widget() && temp->widget() == _bubble)
            {
                bubbleItem = temp;
            }
            else
            {
                delete temp;
            }
        }

    if (mode == ItemMode::Self) {
        // 自己模式：靠右显示 [stretch] + [内容] + [头像]
        _main_layout->addStretch();
        _bubble_layout->addStretch();
        if (vLayoutItem) _main_layout->addItem(vLayoutItem);
        if (avatarItem) _main_layout->addItem(avatarItem);
        if (bubbleItem) _bubble_layout->addItem(bubbleItem);

        _name->setAlignment(Qt::AlignRight);
        _main_layout->setContentsMargins(120,0,0,0);
    }
    else if (mode == ItemMode::Other) {
        // 他人模式：靠左显示 [头像] + [内容] + [stretch]

        if (avatarItem) _main_layout->addItem(avatarItem);
        if (vLayoutItem) _main_layout->addItem(vLayoutItem);
        if (bubbleItem) _bubble_layout->addItem(bubbleItem);
        _main_layout->addStretch();
        _bubble_layout->addStretch();
        _name->setAlignment(Qt::AlignLeft);
        _main_layout->setContentsMargins(0,0,120,0);
    }
}

