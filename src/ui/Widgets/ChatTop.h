//
// Created by 残梦 on 2025/11/17.
//

#ifndef CHATTOP_H
#define CHATTOP_H
#include <QHBoxLayout>
#include <QWidget>

#include "ui/Custom/YumeLabel.h"


class ChatTop:public QWidget
{
    Q_OBJECT
public:
    ChatTop(QWidget* parent,const QString& name);
    ~ChatTop();
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(Qt::transparent);
        painter.setPen(QPen(QColor(128, 128, 128, 24), 1));

        painter.drawLine(this->rect().bottomLeft(),this->rect().bottomRight());
    };
private:
    QHBoxLayout* _main_layout;
    YumeLabel* _name;

};



#endif //CHATTOP_H
