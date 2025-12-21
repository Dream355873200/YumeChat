//
// Created by 残梦 on 2025/9/4.
//

#include "ChatArea.h"
#include <QScrollBar>

ChatArea::ChatArea(QWidget *parent)
    : SmoothListWidget(parent)
{
    this->speed = 0.8;

    // 设置列表控件属性以确保正确布局

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->setUniformItemSizes(false);

}

void ChatArea::add_bubble(MessageItem *bubble)
{
    // 保存滚动位置
    int scrollPos = verticalScrollBar()->value();

    // 计算合适的宽度
    int bubbleWidth = calculateBubbleWidth();

    // 设置宽度约束
    bubble->setMaximumWidth(bubbleWidth);
    bubble->setMinimumWidth(200);

    // 创建列表项
    QListWidgetItem *item = new QListWidgetItem(this);

    // 关键修改：让气泡计算理想尺寸
    QSize idealSize;
    // 确保高度足够显示所有内容
    int contentHeight = bubble->calculateContentHeight();
    if (contentHeight > 0)
    {
        idealSize.setHeight(contentHeight);
    }

    // 设置item的大小，确保高度足够


    item->setSizeHint(QSize(bubbleWidth, qMax(idealSize.height(), 60))); // 最小高度60px

    setItemWidget(item, bubble);


    adjustAllBubbles();

    // 恢复滚动位置
    verticalScrollBar()->setValue(scrollPos);


    scrollToBottom();
}

void ChatArea::resizeEvent(QResizeEvent *event)
{
    SmoothListWidget::resizeEvent(event);

    adjustAllBubbles();
}

void ChatArea::adjustAllBubbles()
{
    // 调整所有现有气泡的宽度和高度
    int newBubbleWidth = calculateBubbleWidth();

    for (int i = 0; i < count(); ++i)
    {
        QListWidgetItem *item = this->item(i);
        MessageItem *bubble = qobject_cast<MessageItem *>(itemWidget(item));
        if (bubble)
        {
            // 更新气泡宽度约束
            bubble->setMaximumWidth(newBubbleWidth);

            // 关键修改：让气泡根据新宽度重新布局
           // bubble->adjustSize();

            // 重新计算理想高度
            int newHeight = bubble->calculateContentHeight();


            // 确保最小高度
            newHeight = qMax(newHeight, 60);

            // 更新item的大小提示
            item->setSizeHint(QSize(newBubbleWidth, newHeight));
        }
    }

    // 立即更新布局
    updateGeometry();
}

int ChatArea::calculateBubbleWidth() const
{
    // 气泡宽度 = 视图宽度 - 边距 - 滚动条宽度
    int viewportWidth = viewport()->width();
    int scrollBarWidth = verticalScrollBar()->isVisible() ? verticalScrollBar()->width() : 0;

    // 留出一些边距，确保内容不会被截断
    int margin = 10;
    int bubbleWidth = viewportWidth - scrollBarWidth - margin;


    // 限制最小宽度，避免过窄
    return qMax(bubbleWidth, 200);
}
