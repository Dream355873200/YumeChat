//
// Created by 残梦 on 2025/8/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ToolWidget.h" resolved

#include "toolwidget.h"


ToolWidget::ToolWidget(QWidget *parent) : QWidget(parent)
{
    this->setContentsMargins(0,0,0,0);
    _main_layout=new QVBoxLayout;
    _main_layout->setAlignment(Qt::AlignTop|Qt::AlignCenter);
    this->setLayout(_main_layout);
    this->setFixedWidth(80);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    _message=new YumeButton(this);
    _message->setFixedSize(40,40);
    _message->label()->setFixedSize(22,22);
    _message->setHoverColor( QColor(220, 220, 220));
    _message->setNormalColor(Qt::transparent);
    _buttons.emplace_back(_message);
    _message->set_is_selected_icon(":/Resource/ico/message_selected.png");
    _message->set_no_selected_icon(":/Resource/ico/message_unselected.png");

    _friends=new YumeButton(this);
    _friends->setFixedSize(40,40);
    _friends->label()->setFixedSize(22,22);
    _friends->setNormalColor( Qt::transparent);
    _friends->setHoverColor( QColor(220, 220, 220));
    _buttons.emplace_back(_friends);
    _friends->set_is_selected_icon(":/Resource/ico/friend_selected.png");
    _friends->set_no_selected_icon(":/Resource/ico/friend_unselected.png");

    update_icon_status();
    connect(_message,&YumeButton::clicked,[this]()
    {
        on_button_clicked(_message);
        update_icon_status();
    });
    connect(_friends,&YumeButton::clicked,[this]()
    {
        on_button_clicked(_friends);
        update_icon_status();
    });
    _main_layout->addWidget(_message);
    _main_layout->addWidget(_friends);

}

ToolWidget::~ToolWidget()
{
}

void ToolWidget::update_icon_status()
{
    for (YumeButton* button : _buttons)
    {
        if(button->is_selected())
        {
            button->setIcon(button->is_selected_icon());
        }
        else
        {
            button->setIcon(button->no_selected_icon());
        }
        button->update();//待优化性能,不必全部更新,存储最近的两个就可以
    }
}

void ToolWidget::on_button_clicked(YumeButton *on_clicked_button)
{
    for(YumeButton* button:_buttons)
    {
        if(button==on_clicked_button)
        {
           button->set_is_selected(true);
        }
        else
        {
            button->set_is_selected(false);
        }
    }
}

