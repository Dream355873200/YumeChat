//
// Created by 残梦 on 2025/12/20.
//

#include "VerifyMessageWindow.h"

#include "logic/HttpMgr/HttpMgr.h"

VerifyMessageWindow::VerifyMessageWindow(QWidget *parent)
    :FramelessWidget(parent)
{
    this->setFixedSize(600, 700);

    _main_layout=new QVBoxLayout;
    _main_layout->setContentsMargins(0,5,0,0);
    this->setLayout(_main_layout);

    _title_bar=new YumeTitleBar(this);
    _main_layout->addWidget(_title_bar);

    _title_bar->setIconEffect(1.0, 0.2, Qt::black);

    _h_layout=new QHBoxLayout;
    _h_layout->setContentsMargins(15,0,25,0);
    _main_layout->addLayout(_h_layout);



    _title=new YumeLabel(this);
    _title->setText("好友通知");
    _title->set_font_size(16);
    _title->setAttribute(Qt::WA_TransparentForMouseEvents);

    _delete=new YumeLabel(this);
    _delete->set_icon(":Resource/ico/message_delete.png");
    _delete->setFixedSize(20,20);


    _h_layout->addWidget(_title,Qt::AlignLeft);
    _h_layout->addWidget(_delete,Qt::AlignRight);




    _list=new SmoothListWidget(this);
    _main_layout->addWidget(_list);

    //进行一次主动拉取
    auto httpMgr = HttpMgr::GetInstance();
    QString param = Global_id;
    QJsonObject json_object;
    json_object["param"] = param;
    json_object["type"] = FRIEND_REQUEST_SELECT;
    QString url = "http://127.0.0.1:8080/friend_request_select";

    httpMgr->PostHttpReq(url, json_object, FRIEND_REQUEST_SELECT, SELECTMOD);

    connect(_title_bar->x(), &YumeLabel::clicked, [this]()
    {
      this->hide();
    });

    connect(_delete,&YumeLabel::clicked,this,&VerifyMessageWindow::process_delete_slots);
}

VerifyMessageWindow::~VerifyMessageWindow()
{


}

void VerifyMessageWindow::process_delete_slots()
{
}

void VerifyMessageWindow::process_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes)
{
}
