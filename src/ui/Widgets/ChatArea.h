//
// Created by 残梦 on 2025/9/4.
//

#ifndef CHATAREA_H
#define CHATAREA_H
#include <QTimer>

#include "MessageItem.h"
#include "ui/Custom/SmoothListWidget.h"


class ChatArea :public SmoothListWidget
{
    Q_OBJECT
public:
    ChatArea(QWidget* parent=nullptr);
    void add_bubble(MessageItem *bubble);
protected:
    void resizeEvent(QResizeEvent *event) override//待优化重复更新
    {
        QListWidget::resizeEvent(event); // 调用父类方法
        int scrollPos = verticalScrollBar()->value();
        // 遍历所有 item，更新 sizeHint
        QTimer::singleShot(100, this, [this]() {
            for (int i = 0; i < count(); ++i)
            {
            QListWidgetItem *item = this->item(i);
            MessageItem *bubble = qobject_cast<MessageItem*>(itemWidget(item));
            if (bubble)
            {
                // 重新计算 sizeHint 并更新 item
                item->setSizeHint(QSize(bubble->width(),bubble->height()));
            }
            }
        });


            verticalScrollBar()->setValue(scrollPos);
    }
private:

};



#endif //CHATAREA_H
