//
// Created by 残梦 on 2025/12/20.
//

#include "VerifyMessageWindow.h"

#include "VerifyMessageWidget.h"
#include "logic/HttpMgr/HttpMgr.h"

VerifyMessageWindow::VerifyMessageWindow(QWidget *parent)
    :FramelessWidget(parent)
{
    this->setFixedSize(600, 700);

    _main_layout=new QVBoxLayout;
    _main_layout->setContentsMargins(10,5,10,10);
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

    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_http_finish,this,&VerifyMessageWindow::process_json);
}

VerifyMessageWindow::~VerifyMessageWindow()
{


}

void VerifyMessageWindow::process_delete_slots()
{
}

void VerifyMessageWindow::process_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes)
{
    QJsonDocument jsonDoc;
    QJsonArray usersArray; // 用于存储用户数组
    QVector<UserInfo> Users;

    if (error_codes == ErrorCodes::ERR_NETWORK)
    {
        //错误处理
    }
    else if (error_codes == ErrorCodes::SUCCESS&&req_id == FRIEND_REQUEST_SELECT)
    {
        // 解析 JSON
        QJsonParseError parseError;
        jsonDoc = QJsonDocument::fromJson(res, &parseError);

        if (parseError.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON 解析错误:" << parseError.errorString();
            return;
        }

        if (!jsonDoc.isObject())
        {
            qDebug() << "JSON 不是对象格式";
            return;
        }

        QJsonObject rootObj = jsonDoc.object();

        // 检查返回码
        if (rootObj.contains("code"))
        {
            int code = rootObj["code"].toInt();

            if (code == 200)
            {
                // 获取 data 字段（应该是数组）
                if (rootObj.contains("data"))
                {
                    usersArray = rootObj["data"].toArray();

                    // 处理用户数据
                    for (const QJsonValue &userValue: usersArray)
                    {
                        if (userValue.isObject())
                        {
                            QJsonObject userObj = userValue.toObject();

                            UserInfo user_info;
                            user_info.name = userObj["name"].toString();
                            user_info.email  = userObj["email"].toString();
                            user_info.avatar  = userObj["avatar"].toString();
                            user_info.note = userObj["note"].toString().toStdString();
                            user_info.update_time=toStdTm(userObj["update_time"]);
                            Users.append(user_info);
                        }
                    }
                    qDebug()<<"成功获取user列表"<<"列表size: "<<Users.size();


                    foreach(UserInfo user,Users)
                    {


                        QString binaryString = user.avatar;  // 你的图片数据

                        // 1. 移除 data URL 前缀（如果有）
                        QString base64Data = binaryString;
                        if (binaryString.startsWith("data:image/")) {
                            // 去掉 "data:image/jpeg;base64," 这样的前缀
                            int commaIndex = binaryString.indexOf(',');
                            if (commaIndex != -1) {
                                base64Data = binaryString.mid(commaIndex + 1);
                            }
                        }

                        // 2. 从 Base64 解码
                        QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());

                        // 3. 加载到 QPixmap
                        QPixmap pixmap;
                        if (!imageData.isEmpty() && pixmap.loadFromData(imageData))
                        {
                            // 成功加载
                            qDebug() << "Base64 图片加载成功";
                        }
                        auto verify_message=new VerifyMessageWidget(this,user.email);
                        verify_message->set_name(user.name);
                        verify_message->set_avatar(pixmap);
                            QListWidgetItem* item=new QListWidgetItem;
                            item->setSizeHint(QSize(this->width()-20,50));
                            _list->addItem(item);
                            _list->setItemWidget(item,verify_message);


                    }

                } else if (code == 404)
                {
                    qDebug() << "未找到用户";
                    QString message = rootObj["message"].toString();
                    qDebug() << "错误信息:" << message;
                }
            }
        }
    }
}
