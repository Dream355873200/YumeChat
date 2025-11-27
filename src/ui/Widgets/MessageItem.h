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

enum ItemMode
{
    Self,
    Other
};
class MessageItem :public QWidget
{
    Q_OBJECT
    public:
    MessageItem(QWidget* parent=nullptr);
    MessageItem(QWidget* parent,const QPixmap& avatar,const QString& name,const QString& text);
   void  set_avatar(const QPixmap& avatar);
    void set_name(const QString & name);
    void set_text(const QString & text);
    void set_mode(const ItemMode& mode);

private:
    YumeBubble* _bubble;
    CircleAvatar* _avatar;
    YumeLabel* _name;
    std::string _conversation_id;
    QHBoxLayout* _main_layout;
    QVBoxLayout* _v_layout;
};




#endif //MESSAGEITEM_H
