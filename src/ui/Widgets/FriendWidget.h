//
// Created by 残梦 on 2025/9/29.
//

#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H
#include "ui/Custom/CircleAvatar.h"
#include "ui/Custom/YumeButton.h"


class FriendWidget:public YumeButton
{
    Q_OBJECT
public:
    FriendWidget(QWidget* parent,const std::string& conversation_id);
    FriendWidget(QWidget* parent,const QString& name,const std::string& conversation_id);
    ~FriendWidget();
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (isHovered||isChecked())
        {
            painter.setBrush(hoverColor);
            QPen pen;
            pen.setColor(QColor::fromString("#D0D5DD"));
            painter.setPen(pen);
        } else
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(normalColor);
        }
        painter.drawRoundedRect(this->rect(), 10, 10);

    };
private:
    const std::string _conversation_id;
    CircleAvatar* _avatar;
    QVBoxLayout* _v_layout;
    YumeLabel* _name;

    signals:
    void double_clicked_friendWidget(const std::string& conversation_id);

};



#endif //FRIENDWIDGET_H
