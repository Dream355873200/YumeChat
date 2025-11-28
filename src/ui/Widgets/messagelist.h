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

#include "SearchWidget.h"
#include "../../../Message.pb.h"
#include "ui/Add/SelectWindow.h"

class MessageList : public QWidget
{
    Q_OBJECT
    friend class MessagePage;
public:
    explicit MessageList(QWidget *parent = nullptr);

    ~MessageList() override;
    void add_message_widget();

private:
    QVBoxLayout* _main_layout;
    SearchWidget* _search;
    SmoothListWidget *_list;
    QButtonGroup *buttonGroup ;
    messagewidget* _messagewidget;
    int button_num=0;
    int width=220;

    std::unique_ptr<SelectWindow> _select_window;
    QAbstractButton* getActiveButton();
private slots:
    void recv_chatMessage(const std::string& conversation_id,const message::MsgNode& message);
};


#endif //MESSAGELIST_H
