//
// Created by 残梦 on 2025/9/29.
//

#include "FriendWidget.h"

FriendWidget::FriendWidget(QWidget *parent, const unsigned int conversation_id)
    :_conversation_id(conversation_id)
{

}

FriendWidget::FriendWidget(QWidget *parent, const QString &name,
    unsigned int conversation_id)
        :_conversation_id(conversation_id)
{

    this->setNormalColor(Qt::transparent);
    this->setHoverColor(QColor::fromString("#F2F3FA"));
    this->setFixedHeight(60);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->main_layout()->setAlignment(Qt::AlignLeft);
    this->main_layout()->setContentsMargins(10, 5, 10, 5);


    _v_layout=new QVBoxLayout;
    _v_layout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    main_layout()->addLayout(_v_layout);
    main_layout()->setStretch(0, 1);
    main_layout()->setStretch(1, 3);

    _avatar=new CircleAvatar(this);
    _avatar->lower();
    _avatar->set_icon(":Resource/ico/yume.jpg");
    _avatar->set_show_status_dot(true);
    _avatar->set_is_online(true);
    if (main_layout()->count() > 0)
    {
        QWidget *oldWidget = main_layout()->itemAt(0)->widget();
        main_layout()->replaceWidget(oldWidget, _avatar);
        oldWidget->deleteLater(); // 删除旧widget
    }



    _name=new YumeLabel(this);
    _name->set_text(name);
    _name->set_font_size(13);
    _name->set_font_color(QColor::fromString("#0C0C0E"));
    _name->setElideMode(Qt::ElideRight);
    _v_layout->addWidget(_name);

}

FriendWidget::~FriendWidget()
{
}
