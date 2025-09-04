//
// Created by 残梦 on 2025/9/4.
//

#include "ChatArea.h"

ChatArea::ChatArea(QWidget *parent)
    :SmoothListWidget(parent)
{
    this->speed=0.8;
}

void ChatArea::add_bubble(MessageItem *bubble)
{

    int scrollPos = verticalScrollBar()->value();
    QListWidgetItem *item=new QListWidgetItem(this);
    item->setSizeHint(QSize(bubble->width(),bubble->height()));
    setItemWidget(item, bubble);

    verticalScrollBar()->setValue(scrollPos);
}
