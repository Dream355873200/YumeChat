//
// Created by 残梦 on 2025/9/3.
//

#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H
#include <locale>
#include <QHBoxLayout>
#include <QWidget>

#include "ui/Custom/CircleAvatar.h"
#include "ui/Custom/YumeBubble.h"
#include "ui/Custom/YumeLabel.h"


class MessageItem :public QWidget
{
    Q_OBJECT
    public:
    MessageItem(QWidget* parent=nullptr);
    MessageItem(QWidget* parent,const QPixmap& avatar,const QString& name,const QString& text);
   void  set_avatar(const QPixmap& avatar);
    void set_name(const QString & name);
    void set_text(const QString & text);
    int height();
    int width();
private:
    YumeBubble* _bubble;
    CircleAvatar* _avatar;
    YumeLabel* _name;
    QHBoxLayout* _main_layout;
    QVBoxLayout* _v_layout;
};



#endif //MESSAGEITEM_H
