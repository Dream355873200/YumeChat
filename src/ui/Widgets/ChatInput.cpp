//
// Created by 残梦 on 2025/9/6.
//

#include "ChatInput.h"

#include "logic/Global/global.h"
#include "logic/TcpMgr/TcpMgr.h"

ChatInput::ChatInput(QWidget *parent)
    :QWidget(parent),_parent(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    _main_layout=new QVBoxLayout;
    _main_layout->setContentsMargins(0,0,10,10);
    this->setLayout(_main_layout);
    _main_layout->setAlignment(Qt::AlignTop);
    _main_layout->setAlignment(Qt::AlignCenter);

    _tool_bar=new YumeTitleBar(this);
    _tool_bar->x()->hide();
    _main_layout->addWidget(_tool_bar);



    _message_input=new QTextEdit(this);
    _message_input->setStyleSheet("QTextEdit { background: transparent; border: none; }");
    _main_layout->addWidget(_message_input);

    _send_button=new YumeButton(this);
    _send_button->setText("发送");
    _send_button->setFixedWidth(80);
    _send_button->setFixedHeight(25);
    _send_button->label()->set_font_color(Qt::white);



    _main_layout->addWidget(_send_button,0,Qt::AlignRight);


    connect(_send_button,&YumeButton::clicked,this,&ChatInput::send_button_clicked);
    connect(this,&ChatInput::_message_send,TcpMgr::GetInstance().get(),&TcpMgr::slot_tcp_sendMsg);
}

void ChatInput::send_button_clicked()
{
    // 创建消息元数据
    auto* meta = new message::MessageMeta();

    // 设置消息ID（必须转换为std::string）
    meta->set_message_id(
        QUuid::createUuid()
        .toString(QUuid::WithoutBraces)
        .toStdString()  // 关键修改点1
    );

    // 设置发送者ID（假设Global_id是QString）
    meta->set_sender_id(Global_id.toStdString());  // 关键修改点2

    meta->set_conversation_id(qobject_cast<ConversationWidget*>(_parent)->_conversation_id);

    // 设置Unix时间戳（毫秒）
    meta->set_unix_timestamp(QDateTime::currentMSecsSinceEpoch());

    // 设置消息类型
    meta->set_type(message::TEXT);

    // 创建消息节点
     message::MsgNode node;

    // 转移meta所有权（注意：调用后不能再使用meta对象）
    node.set_allocated_meta(meta);  // 关键修改点4

    // 设置消息内容（必须转换为std::string）
    node.set_text(
        _message_input->toPlainText()
        .toStdString()  // 关键修改点5
    );
    qobject_cast<ConversationWidget*>(_parent)->add_message_item(node.meta().sender_id(),node);
    // 清空输入框
    _message_input->clear();
    emit _message_send(ReqId::Null,node);
}
