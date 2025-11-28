//
// Created by 残梦 on 2025/9/1.
//

#ifndef SMOOTHLISTWIDGET_H
#define SMOOTHLISTWIDGET_H

#include <qevent.h>
#include <QListWidget>
#include<QWidget>
#include<QScrollBar>
#include<QPropertyAnimation>
#include<QScroller>

#include "SmoothScrollBar.h"

class SmoothListWidget : public QListWidget
{
    Q_OBJECT

public:
    SmoothListWidget(QWidget *parent = nullptr) : QListWidget(parent)
    {
        this->setContentsMargins(0,0,0,0);
        setUniformItemSizes(true);
        setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        //QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture); // 启用惯性滚动 (这个是鼠标拖拽)
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        setSelectionMode(QAbstractItemView::NoSelection);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setAttribute(Qt::WA_Hover, false);

        installEventFilter(this);

        scrollbar_beauty();

        setStyleSheet(
            "QListWidget {"
            "   border: none;"
            "   background: transparent;"
            "}"
            "QListWidget::item {"
            "   border: none;"
            "   background: transparent;"
            "}"
            "QListWidget::item:hover {"
            "   background: transparent;" // 悬停时透明
            "}"
        );
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (watched ==this)
        {
            if (event->type() == QEvent::Enter)
            {
                verticalScrollBar()->setVisible(true);
            } else if (event->type() == QEvent::Leave)
            {
                // 鼠标离开时隐藏滚动条
                verticalScrollBar()->setVisible(false);
            }
        }
        // 让滚动条的滚轮事件也走统一处理流程
        if (watched == verticalScrollBar() && event->type() == QEvent::Wheel)
        {
            wheelEvent(static_cast<QWheelEvent *>(event));
            return true;
        }
        return QListWidget::eventFilter(watched, event);
    }

    void wheelEvent(QWheelEvent *event) override
    {
        int currentPos = verticalScrollBar()->value();
        int step = event->angleDelta().y() / speed; // 调整除数控制步长

        // 使用动画平滑滚动
        QPropertyAnimation *animation = new QPropertyAnimation(verticalScrollBar(), "value");
        animation->setDuration(250);
        animation->setStartValue(currentPos);
        animation->setEndValue(currentPos - step);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->start(QPropertyAnimation::DeleteWhenStopped);

        event->accept();
    }
    float speed=0.8;
private:
    void scrollbar_beauty();
    bool is_added(const QString& id);

};


#endif //SMOOTHLISTWIDGET_H
