//
// Created by 残梦 on 2025/12/16.
//

#ifndef SEARCHFRIENDWIDGET_H
#define SEARCHFRIENDWIDGET_H
#include "ConversationWidget.h"


class SearchFriendWidget :public QWidget
{
    Q_OBJECT
public:
    SearchFriendWidget(QWidget* parent=nullptr);
    ~SearchFriendWidget();
    void set_name(const QString& name);
    void set_avatar(const QPixmap& avatar);

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setBrush(_color);
        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(this->rect(),6,6);
    };
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    QColor _color=Qt::white;

    QHBoxLayout* _main_layout;
    QVBoxLayout* _name_layout;
    YumeButton* _add_button;
    YumeLabel* _name_label;
    CircleAvatar* _avatar;

};



#endif //SEARCHFRIENDWIDGET_H
