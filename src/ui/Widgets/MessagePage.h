//
// Created by 残梦 on 2025/9/4.
//

#ifndef MESSAGEPAGE_H
#define MESSAGEPAGE_H
#include <QWidget>

#include "ChatArea.h"
#include "messagelist.h"


class MessagePage:public QWidget
{
    Q_OBJECT
public:
    MessagePage(QWidget* parent=nullptr);

private:
    MessageList* _list;
    ChatArea* _area;
    QHBoxLayout* _main_layout;
};



#endif //MESSAGEPAGE_H
