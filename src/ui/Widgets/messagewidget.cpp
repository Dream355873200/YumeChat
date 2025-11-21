//
// Created by 残梦 on 2025/8/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_messagewidget.h" resolved

#include "messagewidget.h"
#include<QFontDatabase>

#include "ui/Custom/CircleAvatar.h"

messagewidget::messagewidget(QWidget *parent) : YumeButton(parent)
{
    _v_layout1 = new QVBoxLayout;
    _v_layout2 = new QVBoxLayout;
    main_layout()->addLayout(_v_layout1);
    main_layout()->addLayout(_v_layout2);

    _v_layout1->setAlignment(Qt::AlignLeft);
    _v_layout2->setAlignment(Qt::AlignRight);
}

messagewidget::messagewidget(QWidget *parent,const QString&name,const QString&last_message,const QString& time)
    : YumeButton(parent)
{
    
    this->setNormalColor(Qt::transparent);
    this->setHoverColor(QColor::fromString("#F2F3FA"));
    this->setFixedHeight(60);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->main_layout()->setAlignment(Qt::AlignLeft);
    this->main_layout()->setContentsMargins(10, 5, 10, 5);

    _v_layout1 = new QVBoxLayout;
    _v_layout2 = new QVBoxLayout;
    _v_layout1->setContentsMargins(5, 0, 0, 0);
    _v_layout2->setContentsMargins(0, 0, 0, 0);
    main_layout()->addLayout(_v_layout1);
    main_layout()->addLayout(_v_layout2);
    main_layout()->setStretch(0, 1);
    main_layout()->setStretch(1, 3);
    main_layout()->setStretch(2, 1);


    _avatar=new CircleAvatar(this);

    if (main_layout()->count() > 0)
        {
        QWidget *oldWidget = main_layout()->itemAt(0)->widget();
        main_layout()->replaceWidget(oldWidget, _avatar);
        oldWidget->deleteLater(); // 删除旧widget
    }
    _avatar->set_icon(":Resource/ico/yume.jpg");

    _v_layout1->setAlignment(Qt::AlignLeft);
    _v_layout2->setAlignment(Qt::AlignRight);

    _name = new YumeLabel(this);
    _last_message = new YumeLabel(this);
    _time = new YumeLabel(this);
    _message_num = new YumeLabel(this);

    _name->setAttribute(Qt::WA_TransparentForMouseEvents);
    _last_message->setAttribute(Qt::WA_TransparentForMouseEvents);
    _time->setAttribute(Qt::WA_TransparentForMouseEvents);
    _message_num->setAttribute(Qt::WA_TransparentForMouseEvents);

    _v_layout1->addWidget(_name);
    _v_layout1->addWidget(_last_message);
    _v_layout2->addWidget(_time);
    _v_layout2->addWidget(_message_num);

    _name->set_text(name);
    _last_message->set_text(last_message);
    _name->set_font_size(13);
    _name->set_font_color(QColor::fromString("#0C0C0E"));
    _name->setElideMode(Qt::ElideRight);
    _last_message->set_font_color(Qt::gray);
    _last_message->setElideMode(Qt::ElideRight);


    _time->set_text(time);
    _message_num->set_text("99+");
    _time->set_font_size(10);
    _time->set_font_color(Qt::gray);
    _message_num->setAlignment(Qt::AlignCenter);
    _message_num->set_font_size(10);

    // 加载字体文件
    int fontId = QFontDatabase::addApplicationFont(":/Resource/font/Lato-Bold.ttf");
    if (fontId != -1) {
        QString family = QFontDatabase::applicationFontFamilies(fontId).first();
        QFont latoBold(family, 8); // 12pt 大小
        _message_num->setFont(latoBold);
    }
    _message_num->setStyleSheet("color: white;");


    connect(this, &QAbstractButton::clicked, [this]() {
           if (unread_num > 0) {
               unread_num = 0;
               _message_num->set_text("");
               _last_message->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
           }
        update();
       });

}

messagewidget::~messagewidget()
{
}

void messagewidget::unread_num_add()
{
    unread_num++;

    // 首次增加未读消息时显示红点
    if (unread_num == 1)
    {
        _message_num->show();
    }
    if(unread_num==99)
    {
        _message_num->set_text("99+");
        return;
    }
    _message_num->set_text(QString::number(unread_num));
}
