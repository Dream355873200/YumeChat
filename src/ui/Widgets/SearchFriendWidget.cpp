//
// Created by 残梦 on 2025/12/16.
//

#include "SearchFriendWidget.h"

#include "logic/HttpMgr/HttpMgr.h"

SearchFriendWidget::SearchFriendWidget(QWidget* parent,const QString& conversation_id)
    : QWidget(parent),_conversation_id(conversation_id)
{
    _main_layout = new QHBoxLayout;
    _main_layout->setAlignment(Qt::AlignVCenter);
    this->setLayout(_main_layout);
    _name_layout = new QVBoxLayout;
    _name_layout->setAlignment(Qt::AlignLeft);


    _avatar = new CircleAvatar(this);
    _name_label = new YumeLabel(this);
    _name_label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _add_button = new YumeButton(this);
    _add_button->setFixedSize(70,30);
    _add_button->setText("添加");
    _main_layout->addWidget(_avatar, 2, Qt::AlignLeft);
    _name_layout->addWidget(_name_label);
    _main_layout->addLayout(_name_layout, 6);
    _main_layout->addWidget(_add_button, 2, Qt::AlignRight);

    this->setFixedHeight(50);
    this->installEventFilter(this);
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_select_mod_finish,this,&SearchFriendWidget::process_friend_request_json);
    connect(_add_button,&YumeButton::clicked,this,&SearchFriendWidget::send_friend_request);
}

SearchFriendWidget::~SearchFriendWidget()
{
}

void SearchFriendWidget::set_name(const QString &name)
{
    _name_label->set_text(name);
}

void SearchFriendWidget::set_avatar(const QPixmap &avatar)
{
    _avatar->set_icon(avatar);
}

void SearchFriendWidget::set_button_text(const QString &text)
{
    _add_button->setText(text);
}

bool SearchFriendWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        if (event->type() == QEvent::Enter)
        {
            _color = QColor::fromString("#F5F5F5");
            this->update();
            return true;
        } else if (event->type() == QEvent::Leave)
        {
            _color = Qt::white;
            this->update();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void SearchFriendWidget::send_friend_request()
{
    auto httpMgr = HttpMgr::GetInstance();

    QJsonObject json_object;
    json_object["conversation_id"] = _conversation_id;
    json_object["sender_id"]=Global_id;
    json_object["type"] = FriendRequest::pending;
    json_object["note"]=_note;
    QString url = "http://127.0.0.1:8080/user_friend_request";

    httpMgr->PostHttpReq(url, json_object, FRIEND_REQUEST, SELECTMOD);
}

void SearchFriendWidget::process_friend_request_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes)
{
    if(req_id==FRIEND_REQUEST)
    {
        if(error_codes==SUCCESS)
        {
            //提示发送成功
            auto json_doc=QJsonDocument::fromJson(res);
            if(json_doc["code"]==SUCCESS)
            {
               qDebug()<<"发送成功";
            }
            else if(json_doc["code"]==Failed)
            {
                qDebug()<<"发送失败";
            }
        }
        else
        {
            qDebug()<<"网络错误";
        }
    }
}
