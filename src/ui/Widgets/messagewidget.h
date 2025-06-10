//
// Created by 残梦 on 2025/8/30.
//

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

#include "ui/Custom/YumeButton.h"


class messagewidget : public YumeButton {
Q_OBJECT

public:
    explicit messagewidget(QWidget *parent = nullptr);
    messagewidget(const QString&name,const QString&last_message,const QString& time);
    ~messagewidget() override;

protected:
    void paintEvent(QPaintEvent *event) override
    {
        YumeButton::paintEvent(event);
        QPainter painter(this);
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(_message_num->rect(),4,4);
    }
private:
    QVBoxLayout* _v_layout1;
    QVBoxLayout* _v_layout2;
    YumeLabel* _name=nullptr;
    YumeLabel* _last_message=nullptr;
    YumeLabel* _time=nullptr;
    YumeLabel* _message_num=nullptr;

    int unread_num=0;

private slots:
    void unread_num_add();
};


#endif //MESSAGEWIDGET_H
