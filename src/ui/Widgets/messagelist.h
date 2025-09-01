//
// Created by 残梦 on 2025/8/31.
//

#ifndef MESSAGELIST_H
#define MESSAGELIST_H

#include <QVBoxLayout>
#include <QWidget>
#include<QListWidget>
#include "messagewidget.h"
#include "ui/Custom/SmoothListWidget.h"
#include "ui/Custom/YumeLabel.h"
#include<QButtonGroup>

class MessageList : public QWidget
{
    Q_OBJECT

public:
    explicit MessageList(QWidget *parent = nullptr);

    ~MessageList() override;
protected:

private:
    QVBoxLayout* _main_layout;
    YumeLabel* _label;
    SmoothListWidget *_list;
    QButtonGroup *buttonGroup ;
    messagewidget* _messagewidget;
};


#endif //MESSAGELIST_H
