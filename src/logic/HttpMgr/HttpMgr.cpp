//
// Created by 残梦 on 2025/6/3.
//

#include "HttpMgr.h"
#include "HttpMgr.h"

#include<memory>
HttpMgr::~HttpMgr()
{
}

HttpMgr::HttpMgr()
    :_manager(this)
{
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data=QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self=shared_from_this();//避免回调前销毁
    QNetworkReply *reply=_manager.post(request,data);
    //POST响应回调函数
    connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod]()
    {
        if(reply->error()!=QNetworkReply::NoError)
        {
            //有错误
            qDebug()<<reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            reply->deleteLater();
            return;
        }
        else
        {
            //无错误
            QByteArray res=reply->readAll();
            //发送信号通知完成
            emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod);
            reply->deleteLater();
            return;
        }

    });
}

void HttpMgr::slot_http_finish(ReqId req_id, QByteArray res, ErrorCodes error_codes, Modules mod)
{
    if(mod==Modules::REGISITERMOD)
    {
        //发送信号通知指定模块http相应结束
        emit sig_reg_mod_finish(req_id,res,error_codes);
    }

}

