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
    MessageItem(QWidget* parent,const QPixmap& avatar,const QString& name,const QString& text,const ItemMode &mode);
   void  set_avatar(const QPixmap& avatar);
    void set_name(const QString & name);
    void set_text(const QString & text);
    void set_mode(const ItemMode& mode);
    // 实现
    int calculateContentHeight() const
    {
        if (!_bubble) return -1;

        // 获取气泡的理想高度
        int bubbleHeight = _bubble->sizeHint().height();

        // 加上名字标签的高度和间距
        int nameHeight = _name->sizeHint().height();
        int spacing = _v_layout->spacing() * 2; // 估算布局间距

        return nameHeight + bubbleHeight + spacing + 30; // 额外边距
    }
private:
    YumeBubble* _bubble;
    CircleAvatar* _avatar;
    YumeLabel* _name;
    std::string _conversation_id;
    QHBoxLayout* _main_layout;
    QVBoxLayout* _v_layout;
    QHBoxLayout* _bubble_layout;

};




#endif //MESSAGEITEM_H
