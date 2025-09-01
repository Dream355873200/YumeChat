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

        // --- 缓存所有计算 ---
        // 静态变量缓存计算结果（假设_textRect在消息数变化时才需要更新）
        static QRect cachedTextRect;
        static QString lastText;

        if (_message_num->text() != lastText) {
            lastText = _message_num->text();

            // 计算文本尺寸和位置（仅在文本变化时执行）
            QFontMetrics fm(_message_num->font());
            QSize textSize = fm.size(Qt::TextSingleLine, lastText);

            QPoint textTopLeft = _message_num->rect().center() -
                                QPoint(textSize.width() / 2, textSize.height() / 2);
            textTopLeft = _message_num->mapToParent(textTopLeft) - QPoint(-1, -1);

            cachedTextRect = QRect(textTopLeft, textSize);
            cachedTextRect.adjust(-5, -1, 5, 1);  // Padding
        }

        // --- 脏矩形检测 ---
        const QRegion dirtyRegion = event->region();
        if (!dirtyRegion.intersects(cachedTextRect)) {
            return;  // 红点区域未被脏区域覆盖
        }

        // --- 最小化绘制区域 ---
        painter.setClipRect(cachedTextRect);  // 关键优化：只绘制红点区域

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.drawRoundedRect(cachedTextRect, 8, 8);
    }
private:
    QVBoxLayout* _v_layout1;
    QVBoxLayout* _v_layout2;
    YumeLabel* _name=nullptr;
    YumeLabel* _last_message=nullptr;
    YumeLabel* _time=nullptr;
    YumeLabel* _message_num=nullptr;

    CircleAvatar *_avatar;
    int unread_num=1;

private slots:
    void unread_num_add();
};


#endif //MESSAGEWIDGET_H
