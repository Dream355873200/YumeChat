//
// Created by 残梦 on 2025/6/3.
//

#ifndef HTTPMGR_H
#define HTTPMGR_H
#include <QString>
#include <QUrl>
#include <QObject>
#include<QJsonObject>
#include<QJsonDocument>
#include<QByteArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "Singleton/Singleton.h"
#include "logic/Global/global.h"
//HTTP请求响应的中转站以及信号发送，对接各模块
class HttpMgr:public QObject,public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
    friend class Singleton<HttpMgr>;
public:

    ~HttpMgr();
    void PostHttpReq(const QUrl &url, const QJsonObject &json, const ReqId &req_id, const Modules &mod);

private:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
private slots:
    void slot_http_finish(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes, const Modules &mod);

signals:
    void sig_http_finish(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes, const Modules &mod);
    void sig_reg_mod_finish(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes);
    void sig_login_mod_finish(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes);
    void sig_select_mod_finish(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes);
};



#endif //HTTPMGR_H
