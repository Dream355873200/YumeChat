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
    void add_message_widget();
protected:
void paintEvent(QPaintEvent *event) override
{

};
private:
    QVBoxLayout* _main_layout;
    YumeLabel* _label;
    SmoothListWidget *_list;
    QButtonGroup *buttonGroup ;
    messagewidget* _messagewidget;
    int button_num=0;
    int width=220;
};


#endif //MESSAGELIST_H
