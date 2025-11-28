//
// Created by 残梦 on 2025/9/4.
//

#ifndef CHATAREA_H
#define CHATAREA_H
#include <QTimer>

#include "MessageItem.h"
#include "ui/Custom/SmoothListWidget.h"

class ChatArea : public SmoothListWidget
{
    Q_OBJECT
public:
    ChatArea(QWidget* parent = nullptr);
    void add_bubble(MessageItem *bubble);

protected:
    void resizeEvent(QResizeEvent *event);
    void adjustAllBubbles();
private:

    int calculateBubbleWidth() const;
};

#endif // CHATAREA_H