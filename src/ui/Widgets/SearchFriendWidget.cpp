//
// Created by 残梦 on 2025/12/16.
//

#include "SearchFriendWidget.h"

SearchFriendWidget::SearchFriendWidget(QWidget *parent)
    : QWidget(parent)
{
    _main_layout = new QHBoxLayout;
    _main_layout->setAlignment(Qt::AlignVCenter);
    this->setLayout(_main_layout);
    _name_layout = new QVBoxLayout;
    _name_layout->setAlignment(Qt::AlignLeft);


    _avatar = new CircleAvatar(this);
    _name_label = new YumeLabel(this);
    _name_label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _add_button = new YumeButton(this);
    _add_button->setFixedSize(70,30);
    _add_button->setText("添加");
    _main_layout->addWidget(_avatar, 2, Qt::AlignLeft);
    _name_layout->addWidget(_name_label);
    _main_layout->addLayout(_name_layout, 6);
    _main_layout->addWidget(_add_button, 2, Qt::AlignRight);

    this->setFixedHeight(50);
    this->installEventFilter(this);
}

SearchFriendWidget::~SearchFriendWidget()
{
}

void SearchFriendWidget::set_name(const QString &name)
{
    _name_label->set_text(name);
}

void SearchFriendWidget::set_avatar(const QPixmap &avatar)
{
    _avatar->set_icon(avatar);
}

bool SearchFriendWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        if (event->type() == QEvent::Enter)
        {
            _color = QColor::fromString("#F5F5F5");
            this->update();
            return true;
        } else if (event->type() == QEvent::Leave)
        {
            _color = Qt::white;
            this->update();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}
