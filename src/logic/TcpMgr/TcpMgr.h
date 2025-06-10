//
// Created by 残梦 on 2025/7/25.
//

#ifndef TCPMGR_H
#define TCPMGR_H
#include"Singleton/Singleton.h"
#include<QTcpSocket>
#include<functional>
#include<QObject>
#include "logic/Global/global.h"
class TcpMgr :public QObject,public Singleton<TcpMgr>
{
    Q_OBJECT

public:
    ~TcpMgr();
private:
    friend class Singleton;
    TcpMgr();
    void initHandlers();
    void handleMsg(ReqId req_id,int len,QByteArray data);
    QTcpSocket _socket;
    QString _host;
    uint16_t _port;
    QByteArray _buffer;
    bool _b_recv_pending;
    quint16 _message_id;
    quint16 _message_len;
    QDataStream _stream;
    QMap<ReqId,std::function<void(ReqId req_id,int len,QByteArray data)>> _handlers;
public slots:
    void slot_tcp_connect(ServerInfo server_info);
    void slot_tcp_sendMsg(ReqId reqId, QString data);
    signals:
    void sig_con_success(bool success);
    void sig_tcp_sendMsg();
    void message_receive_success();









};



#endif //TCPMGR_H
