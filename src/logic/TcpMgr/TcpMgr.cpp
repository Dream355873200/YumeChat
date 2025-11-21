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
        _stream.setByteOrder(QDataStream::BigEndian);//处理网络字节序
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

            auto message = std::make_shared<message::MsgNode>();
            if (message->ParseFromArray(messageBody.constData(), messageBody.size())) {
                // 反序列化成功
                qDebug() << "反序列化成功，消息内容:" << message->DebugString().c_str();
                // 处理消息内容// 例如：qDebug() << "字段值:" << message.some_field().c_str();
            } else
                {
                // 反序列化失败
                qDebug() << "反序列化失败！";
                return;
            }


            qDebug() << "Received message ID:" << _message_id << "Body:" << messageBody;
             _buffer.remove(0, _message_len);
               _b_recv_pending = false;

            emit message_receive_success(message);
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

void TcpMgr::pushMsg()
{
    //读取数据库各种类型消息，发push_meta的protobuffer给TCPServer
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

    message::MsgNode verify_node;

    /// 发送验证信息
    auto* meta = new message::MessageMeta();  // 堆对象
    meta->set_message_id(QUuid::createUuid()
        .toString(QUuid::WithoutBraces)
        .toStdString()  // 关键修改：必须转换);  // 设置字段
        );

    meta->set_sender_id(Global_id.toStdString());  // 如果是QString需要转换
    meta->set_conversation_id(Global_id.toStdString());
    meta->set_type(message::UNKNOWN);
    // 时间戳处理（优化方案）
    const auto now = QDateTime::currentDateTime();
    meta->set_unix_timestamp(now.toMSecsSinceEpoch());  // 更精确的时间戳

    auto login_verify_meta=new message::LoginVerifyMeta;
    login_verify_meta->set_token(server_info.Token.toStdString());

    // 注意：set_allocated会转移指针所有权
    verify_node.set_allocated_meta(meta);  // 这里meta会被verify_node接管
    verify_node.set_allocated_login_verify_meta(login_verify_meta);

    slot_tcp_sendMsg(ID_CHAT_LOGIN, verify_node);

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
