//
// Created by 残梦 on 2025/7/25.
//

#include "TcpMgr.h"



#include "../../../Message.pb.h"

TcpMgr::~TcpMgr()
{
    _socket.close();
    _buffer.clear();
}


TcpMgr::TcpMgr()
    : _host(""), _port(0), _b_recv_pending(false), _message_id(0), _message_len(0)
{


    QObject::connect(&_socket, &QTcpSocket::connected, [&]()
    {
        qDebug() << "Tcp连接成功";
        emit sig_con_success(true);
    });
    QObject::connect(&_socket, &QTcpSocket::readyRead, [&]()
    {
        // 增量追加数据到缓冲区
        _buffer.append(_socket.readAll());
        QDataStream _stream(&_buffer, QIODevice::ReadOnly);
        _stream.setVersion(QDataStream::Qt_5_0);
        forever
        {
            if (!_b_recv_pending)
            {
                if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2))
                {
                    return;
                };
                _stream >> _message_id >> _message_len;

                _buffer.remove(0, sizeof(quint16)*2);
                _b_recv_pending = true;

                // 输出读取的数据
                qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;
            }
            if (_buffer.size() < _message_len)
            {
                return;
            }
            // 读取消息体
             QByteArray messageBody = _buffer.mid(0, _message_len);
            qDebug() << "Received message ID:" << _message_id << "Body:" << messageBody;
             _buffer.remove(0, _message_len);
               _b_recv_pending = false;

            emit message_receive_success();
        }
    });
    //处理错误
    QObject::connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
                     [&](QAbstractSocket::SocketError socketError)
                     {
                         Q_UNUSED(socketError)
                         qDebug() << "Error:" << _socket.errorString();
                     });
    //断开连接
    QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
           qDebug() << "Disconnected from server.";
       });
}

void TcpMgr::initHandlers()
{
}

void TcpMgr::handleMsg(ReqId req_id, int len, QByteArray data)
{
}

void TcpMgr::slot_tcp_connect(const ServerInfo& server_info)
{
    /*
     * 将登录模块连接到此槽函数
     */
    qDebug()<< "receive tcp connect signal";
    // 尝试连接到服务器
    qDebug() << "Connecting to server...";
    _host = server_info.Host;
    _port = server_info.Port;
    _socket.connectToHost(server_info.Host, _port);
    _token=server_info.Token;

    message::MsgNode verify_node;
    verify_node.set_text(_token);

    ///发送验证信息
    message::MessageMeta meta;
    meta.set_message_id(QUuid::createUuid().toString(QUuid::WithoutBraces));
    meta.set_sender_id(Global_id);
    meta.set_conversation_id(Global_id);
    meta.set_timestamp(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
    meta.set_unix_timestamp(QDateTime::currentMSecsSinceEpoch());
    meta.set_type(message::Verify);

    verify_node.set_allocated_meta(&meta);
    slot_tcp_sendMsg(ID_CHAT_LOGIN,verify_node);
}

void TcpMgr::slot_tcp_sendMsg(const ReqId& reqId,const message::MsgNode& node)
{
    /*
     * 发送按钮连接到此槽函数
     * 此函数还有问题，没有发送的目标群组或个人，待开发
     * 应该发送结构化数据，发送目标，发送人，消息内容，发送时间，从消息窗口获取信号槽连接
     */

    uint16_t id = reqId;
    try {
        // 1. 序列化 protobuf 消息
        std::string serializedMsg;
        if (!node.SerializeToString(&serializedMsg)) {
            qWarning() << "Failed to serialize protobuf message";
            return;
        }

        // 2. 创建消息头 (ID + 长度)
        QByteArray header;
        QDataStream headerStream(&header, QIODevice::WriteOnly);
        headerStream.setByteOrder(QDataStream::BigEndian); // 网络字节序

        // 使用 protobuf 序列化后的长度
        quint16 msgLength = static_cast<quint16>(serializedMsg.size());
        headerStream << static_cast<quint16>(reqId) << msgLength;

        // 3. 组合消息
        QByteArray block;
        block.append(header);
        block.append(serializedMsg.data(), serializedMsg.size());

        // 4. 发送数据
        qint64 bytesWritten = _socket.write(block);
        if (bytesWritten == -1) {
            qWarning() << "Failed to write to socket:" << _socket.errorString();
        } else if (!_socket.waitForBytesWritten()) {
            qWarning() << "Failed to flush socket:" << _socket.errorString();
        }

    } catch (const std::exception& e) {
        qCritical() << "Exception in slot_tcp_sendMsg:" << e.what();
    }
}
