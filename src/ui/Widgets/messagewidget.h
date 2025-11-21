//
// Created by 残梦 on 2025/8/30.
//

#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

#include "ui/Custom/CircleAvatar.h"
#include "ui/Custom/YumeButton.h"


class messagewidget : public YumeButton {
Q_OBJECT

public:
    explicit messagewidget(QWidget *parent = nullptr);
    messagewidget(QWidget *parent,const QString&name,const QString&last_message,const QString& time);
    ~messagewidget() override;

protected:
    void paintEvent(QPaintEvent *event) override {
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

        // 提前终止条件：无未读消息或脏区域为空
        if (unread_num == 0 || event->region().isEmpty()) {
            return;
        }

        painter.setRenderHint(QPainter::Antialiasing);

        // --- 实时计算 ---
        // 计算文本尺寸和位置（每次实时计算）
        QFontMetrics fm(_message_num->font());
        QString currentText = _message_num->text();
        QSize textSize = fm.size(Qt::TextSingleLine, currentText);

        QPoint textTopLeft = _message_num->rect().center() -
                            QPoint(textSize.width() / 2, textSize.height() / 2);
        textTopLeft = _message_num->mapToParent(textTopLeft) - QPoint(-1, -1);

        QRect textRect = QRect(textTopLeft, textSize);
        textRect.adjust(-5, -1, 5, 1);  // Padding

        // --- 脏矩形检测 ---
        const QRegion dirtyRegion = event->region();
        if (!dirtyRegion.intersects(textRect)) {
            return;  // 红点区域未被脏区域覆盖
        }

        // --- 最小化绘制区域 ---
        painter.setClipRect(textRect);  // 关键优化：只绘制红点区域

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.drawRoundedRect(textRect, 8, 8);
    }
private:
    QVBoxLayout* _v_layout1;
    QVBoxLayout* _v_layout2;
    YumeLabel* _name=nullptr;
    YumeLabel* _last_message=nullptr;
    YumeLabel* _time=nullptr;
    YumeLabel* _message_num=nullptr;
    std::string conversation_id;
    CircleAvatar *_avatar;
    int unread_num=1;

public slots:
    void unread_num_add();
};


#endif //MESSAGEWIDGET_H
