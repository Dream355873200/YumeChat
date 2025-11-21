//
// Created by 残梦 on 2025/9/6.
//

#ifndef CHATINPUT_H
#define CHATINPUT_H
#include <QWidget>

#include "../../../Message.pb.h"
#include "ui/Custom/UnScrollTextEdit.h"
#include "ui/Custom/YumeButton.h"
#include "ui/Custom/YumeTitleBar.h"
#include<QDateTime>
#include<QUuid>

#include "logic/Global/global.h"

class ChatInput :public QWidget
{
    Q_OBJECT
    friend class MessagePage;
public:
    ChatInput(QWidget *parent=nullptr);

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);

        painter.setRenderHint(QPainter::Antialiasing);



        painter.setPen(QPen(QColor(128, 128, 128, 32), 2));
        painter.setBrush(Qt::transparent);

        painter.drawLine(this->rect().topLeft(),this->rect().topRight());

    };
private:
    QVBoxLayout* _main_layout;
    QTextEdit* _message_input;
    YumeButton* _send_button;
    YumeTitleBar* _tool_bar;
    message::MsgNode node;
    signals:
    void _message_send(const ReqId& reqId,const message::MsgNode& node);

private slots:
    void send_button_clicked();
};



#endif //CHATINPUT_H
