//
// Created by 残梦 on 2025/12/23.
//

#ifndef VERIFYMESSAGEWIDGET_H
#define VERIFYMESSAGEWIDGET_H
#include "ui/Widgets/ConversationWidget.h"


class VerifyMessageWidget:public QWidget
{

public:
    VerifyMessageWidget(QWidget* parent=nullptr);
    ~VerifyMessageWidget();
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter;
    };
private:
    QHBoxLayout* _main_layout;
    CircleAvatar* _avatar;
    YumeLabel* _name;
    YumeButton* _button;

};



#endif //VERIFYMESSAGEWIDGET_H
