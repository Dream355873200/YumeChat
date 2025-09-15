//
// Created by 残梦 on 2025/5/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_login_dialog.h" resolved

#include "login_dialog.h"
#include "ui_login.h"
#include "logic/HttpMgr/HttpMgr.h"
#include "logic/TcpMgr/TcpMgr.h"


LoginDialog::LoginDialog(QWidget *parent)
:QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    connect(ui->reg_pushButton,&YumeButton::clicked,this,&LoginDialog::SwitchReg);
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_login_mod_finish,this,&LoginDialog::slot_login_mod_finish);
    connect(ui->login_pushButton,&YumeButton::clicked,this,&LoginDialog::login_pushbutton_click);

    connect(this,&LoginDialog::login_succeess,TcpMgr::GetInstance().get(),&TcpMgr::slot_tcp_connect);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::login_pushbutton_click()
{
    auto httpMgr=HttpMgr::GetInstance();
    QString account=ui->user_lineEdit->line_edit()->text().trimmed();
    QString password=ui->pass_lineEdit->line_edit()->text().trimmed();
    QJsonObject json_object;
    json_object["account"]=account;
    json_object["password"]=password;
    QString url="http://127.0.0.1:8080/user_Login";
    httpMgr->PostHttpReq(url,json_object,ID_LOGIN_USER,LOGINMOD);
}

void LoginDialog::slot_login_mod_finish(ReqId req_id, const QByteArray &res, ErrorCodes error_codes)
{
    if (error_codes == ErrorCodes::ERR_NETWORK)
    {
        //showTip(tr("网络请求错误"), false);
        return;
    }
    /*
     * 成功切换到聊天界面，不成功提示
     */
    //解析JSON字符串
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res);
    if (jsonDoc.isNull())
    {
       // showTip(tr("JSON解析失败"), false);
        return;
    }
    //JSON解析错误
    if (!jsonDoc.isObject())
    {
        //showTip(tr("JSON解析失败"), false);
        return;
    }
    int error=jsonDoc["error"].toInt();
    if(error==ErrorCodes::ERR_USER_UNEXSIT)
        return;
    if(error==ErrorCodes::ERR_PASSWORD_FAILED)
        return;
    if(error==ErrorCodes::SUCCESS)
    {
        qDebug()<<"登录成功";
        Global_id=jsonDoc["account"].toString();
        Global_host=jsonDoc["host"].toString();
        Global_port=jsonDoc["port"].toInt();
        Global_token=jsonDoc["token"].toString();
        ServerInfo server;
        server.Host=Global_host;
        server.Port=Global_port;
        server.Token=Global_token;
        emit login_succeess(server);
        //跳转
    }
}
