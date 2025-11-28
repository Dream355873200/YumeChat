//
// Created by 残梦 on 2025/9/1.
//

#include "SmoothListWidget.h"

void SmoothListWidget::scrollbar_beauty()
{
    verticalScrollBar()->setVisible(false);
    QScrollBar* nativeScrollBar = this->verticalScrollBar();
    nativeScrollBar->installEventFilter(this);

    nativeScrollBar->setStyleSheet(R"(
    QScrollBar:vertical {
        width: 10px;
        background: transparent;
        margin: 0px 0px 0px 0px;
    }
    QScrollBar::handle:vertical {
         background: rgba(217, 217, 217, 150);
        min-height: 150px;
        border-radius: 4px;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        background: none;
    }
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background: none;
    }
)");



}

bool SmoothListWidget::is_added(const QString &id)
{

    for(int i=0;i<this->count();i++)
    {
        QListWidgetItem* item=this->item(i);
        if(item->data(Qt::UserRole).toString()==id)
        {
            return true;
        }
    }
    return false;
}
