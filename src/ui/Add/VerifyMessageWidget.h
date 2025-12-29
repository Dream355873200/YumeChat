//
// Created by 残梦 on 2025/12/23.
//

#ifndef VERIFYMESSAGEWIDGET_H
#define VERIFYMESSAGEWIDGET_H
#include "ui/Custom/SplitButton.h"
#include "ui/Widgets/ConversationWidget.h"


class VerifyMessageWidget:public QWidget
{

public:
    VerifyMessageWidget(QWidget* parent,const QString& conversation_id);
    ~VerifyMessageWidget();
    void set_name(const QString& name);
    void set_avatar(const QPixmap& avatar);
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(this->rect(),8,8);
    };
private:
    QHBoxLayout* _main_layout;
    CircleAvatar* _avatar;
    YumeLabel* _name;
    SplitButton* _split_button;
    QString _conversation_id="";

};



#endif //VERIFYMESSAGEWIDGET_H
