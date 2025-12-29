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
    SearchFriendWidget(QWidget* parent,const QString& conversation_id);
    ~SearchFriendWidget();
    void set_name(const QString& name);
    void set_avatar(const QPixmap& avatar);
    void set_button_text(const QString& text);
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
    QString _conversation_id;
    QString _note="";

private slots:
    void send_friend_request_http();
    void send_friend_request_tcp();
    void process_friend_request_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes);
};



#endif //SEARCHFRIENDWIDGET_H
