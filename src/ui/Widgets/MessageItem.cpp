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


}

MessageItem::MessageItem(QWidget *parent, const QPixmap &avatar, const QString &name,const QString& text)
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
    _v_layout->setAlignment(Qt::AlignTop);
    _main_layout->addLayout(_v_layout);
    _v_layout->addWidget(_name);
    _v_layout->addWidget(_bubble);
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
    if(mode==ItemMode::Self)
    {
      auto item=_main_layout->itemAt(0);
        if(item->widget())
        {
            _main_layout->removeItem(item);
            _main_layout->addItem(item);
            _name->setAlignment(Qt::AlignRight);
            _bubble->content_layout()->setContentsMargins(120,3,0,0);
        }
    }
    if(mode==ItemMode::Other)
    {
        auto item=_main_layout->itemAt(0);
        if(item->layout())
        {
            _main_layout->removeItem(item);
            _main_layout->addItem(item);
            _name->setAlignment(Qt::AlignLeft);
            _bubble->content_layout()->setContentsMargins(5,3,120,0);
        }
    }
}

int MessageItem::height()
{
    return _bubble->sizeHint().height()+15+_name->sizeHint().height()+10;
}

int MessageItem::width()
{
    return  _bubble->sizeHint().width()+20;
}
