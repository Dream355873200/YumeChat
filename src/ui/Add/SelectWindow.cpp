//
// Created by 残梦 on 2025/11/28.
//

#include "SelectWindow.h"

#include <QDateTime>
#include <QUuid>

#include "logic/HttpMgr/HttpMgr.h"
#include "logic/TcpMgr/TcpMgr.h"
#include "ui/Widgets/SearchFriendWidget.h"

SelectWindow::SelectWindow(QWidget* parent)
    :FramelessWidget(parent)
{
    this->setFixedSize(600, 700);


    _main_layout = new QVBoxLayout;
    _main_layout->setContentsMargins(0, 5, 0, 0);
    _main_layout->setAlignment(Qt::AlignTop);
    this->setLayout(_main_layout);

    _title_bar = new YumeTitleBar(this);
    _main_layout->addWidget(_title_bar);

    _search_layout = new QHBoxLayout;
    _search_layout->setContentsMargins(10, 5, 10, 5);
    _main_layout->addLayout(_search_layout);

    _search = new YumeLineEdit(this);
    _search->setMode(LineEditMode::Search);
    _search->setFixedSize(450, 30);
    _search_layout->addWidget(_search);

    _button = new YumeButton;
    _button->setText("搜索");
    _button->setFixedSize(100, 30);
    _search_layout->addWidget(_button);

    _list = new SmoothListWidget(this);

    _main_layout->addWidget(_list);


    _title_bar->setIconEffect(1.0, 0.2, Qt::black);

    connect(_title_bar->x(), &YumeLabel::clicked, [this]()
    {
        this->hide();
    });
    connect(_button, &YumeButton::clicked, this, &SelectWindow::select_button_clicked);

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_select_mod_finish, this, &SelectWindow::process_json);

}

void SelectWindow::select_button_clicked()
{
    auto httpMgr = HttpMgr::GetInstance();
    QString param = _search->line_edit()->text();
    QJsonObject json_object;
    json_object["param"] = param;
    json_object["type"] = SELECT_ADD_FRIEND;
    QString url = "http://127.0.0.1:8080/user_add_select";

    httpMgr->PostHttpReq(url, json_object, SELECT_ADD_FRIEND, SELECTMOD);
}

void SelectWindow::process_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes)
{
    //qDebug() << "当前时间:" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    // qDebug() << "对象地址:" << this;
    QJsonDocument jsonDoc;
    QJsonArray usersArray; // 用于存储用户数组
    QVector<UserInfo> Users;

    if (error_codes == ErrorCodes::ERR_NETWORK)
    {
        //错误处理
    } else if (error_codes == ErrorCodes::SUCCESS&&req_id == SELECT_ADD_FRIEND)
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

                            Users.append(user_info);
                        }
                    }
                    qDebug()<<"成功获取user列表"<<"列表size: "<<Users.size();


                    foreach(UserInfo user,Users)
                    {
                        SearchFriendWidget* friend_widget=new SearchFriendWidget(this);


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
                        friend_widget->set_name(user.name);
                        friend_widget->set_avatar(pixmap);
                            QListWidgetItem* item=new QListWidgetItem;
                            item->setSizeHint(QSize(this->width()-10,50));
                            _list->addItem(item);
                            _list->setItemWidget(item,friend_widget);


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
