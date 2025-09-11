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
    _host = QString::fromStdString(server_info.Host);
    _port = server_info.Port;
    _socket.connectToHost(server_info.Host.data(), _port);
}

void TcpMgr::slot_tcp_sendMsg(ReqId reqId, QString data)
{
    /*
     * 发送按钮连接到此槽函数
     * 此函数还有问题，没有发送的目标群组或个人，待开发
     * 应该发送结构化数据，发送目标，发送人，消息内容，发送时间，从消息窗口获取信号槽连接
     */
    message::MsgNode node;
    message::MessageMeta *meta = node.mutable_meta();
    //meta->set_message_id();
/*    meta->set_conversation_id();
    meta->set_sender_id();
    meta->set_timestamp();
    meta->set_type(message::TEXT);
    */
    uint16_t id = reqId;
    // 将字符串转换为UTF-8编码的字节数组
    QByteArray dataBytes = data.toUtf8();
    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(data.size());
    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);
    // 写入ID和长度
    out << id << len;
    // 添加字符串数据
    block.append(dataBytes);
    // 发送数据
    _socket.write(block);
}
