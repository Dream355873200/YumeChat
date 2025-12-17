//
// Created by 残梦 on 2025/8/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MessageList.h" resolved

#include "messagelist.h"

#include <QFontDatabase>
#include<QScrollBar>

#include "FriendWidget.h"
#include "logic/MessageMgr/MessageMgr.h"

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
    _search->notice_button()->hide();



    _main_layout->addWidget(_search);
    _main_layout->addWidget(_list);

    QString data="123456";


    _messagewidget=new messagewidget(this,data.toStdString());
    _messagewidget->setFixedWidth(width-10);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,data);


    item->setSizeHint(QSize(_messagewidget->sizeHint().width(),60) );
    _list->addItem(item);
    _list->setItemWidget(item, _messagewidget);
    buttonGroup->addButton(_messagewidget, button_num++);
    for(int i=0;i<20;i++)
    {
        auto test=new messagewidget(this,data.toStdString());
        test->setFixedWidth(width-20);
        QListWidgetItem *t_item = new QListWidgetItem();
        t_item->setData(Qt::UserRole,data);


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

    connect(_search->add_friend(),&YumeButton::clicked,[this]()
    {
        _select_window.show();
    });
    connect(MessageMgr::GetInstance().get(),&MessageMgr::chat_message,this,&MessageList::recv_chatMessage);
}

MessageList::~MessageList()
{

}

void MessageList::add_message_widget()
{
    QString data="123456";

    auto test=new messagewidget(this,data.toStdString());
    QListWidgetItem *t_item = new QListWidgetItem();
    t_item->setData(Qt::UserRole,data);


    QWidget* container = new QWidget(this);
    container->setFixedWidth(width-10);

    QHBoxLayout* containerLayout = new QHBoxLayout;
    container->setLayout(containerLayout);
    containerLayout->setAlignment(Qt::AlignCenter);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->addWidget(test);

    t_item->setSizeHint(QSize(test->sizeHint().width(), 60));

    _list->addItem(t_item);
    _list->setItemWidget(t_item, container);  // 将容器设置为item的widget



    buttonGroup->addButton(test, button_num++);
}

QAbstractButton* MessageList::getActiveButton() {
    if (!buttonGroup) return nullptr;

    QAbstractButton *activeButton = buttonGroup->checkedButton();
    if (activeButton) {
        qDebug() << "当前激活的按钮:" << activeButton->text();
        return activeButton;
    } else {
        qDebug() << "没有按钮被选中";
        return nullptr;
    }
}

void MessageList::recv_chatMessage(const std::string &conversation_id, const message::MsgNode& message)
{
    for(int i=0;i<_list->count();i++)
    {
       QListWidgetItem * item= _list->item(i);
       QWidget* widget= _list->itemWidget(item);

        auto message_widget= qobject_cast<messagewidget*>(widget->layout()->widget());
        if (!message_widget)
            {
            qDebug() << "错误：widget不是messagewidget类型";
            continue;  // 安全跳过，不会崩溃
        }
        if(conversation_id==message_widget->get_conversation_id())
        {
            _list->takeItem(i);
            _list->insertItem(0,item);
            if(message_widget!=getActiveButton())
            {
                message_widget->unread_num_add();
            }
        };
    }
}






