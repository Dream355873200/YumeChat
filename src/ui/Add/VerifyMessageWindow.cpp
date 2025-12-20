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
}

VerifyMessageWindow::~VerifyMessageWindow()
{


}
