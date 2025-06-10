//
// Created by 残梦 on 2025/6/2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RegisterDialog.h" resolved

#include "registerdialog.h"
#include "ui_RegisterDialog.h"


RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
    connect(ui->cancel_pushButton,&QPushButton::clicked,this,&RegisterDialog::SwitchLogin);

    connect(ui->email_pushButton,&QPushButton::clicked,this,&RegisterDialog::email_pushbutton_click);
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,&RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();

}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE,[this](const QJsonObject& json_object)
    {
        int error=json_object["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
        {
            showTip(tr("参数错误,验证码发送失败"),false);
            return;
        }
        auto email=json_object["email"].toString();
        /*
         * 待写邮件发送逻辑
         */
        showTip(tr("验证码已经发送到邮箱，请查收"),true);
        qDebug()<<"email is"<<email;
    });
}

void RegisterDialog::showTip(QString msg, bool flag)
{
    /*
     * 待写UI显示逻辑
     */
}

void RegisterDialog::slot_reg_mod_finish(ReqId req_id, QByteArray res, ErrorCodes error_codes)
{
    if(error_codes!=ErrorCodes::SUCCESS)
    {
        showTip(tr("网络请求错误"),false);
        return;
    }
    //解析JSON字符串
    QJsonDocument jsonDoc=QJsonDocument::fromJson(res);
    if(jsonDoc.isNull())
    {
        showTip(tr("JSON解析失败"),false);
        return;
    }
    //JSON解析错误
    if(!jsonDoc.isObject())
    {
        showTip(tr("JSON解析失败"),false);
        return;
    }
    // 检查是否存在该req_id的处理器
    if (!_handlers.contains(req_id)) {
        showTip(tr("未找到对应的处理器"), false);
        return;
    }
    _handlers[req_id](jsonDoc.object());
    return;

}

void RegisterDialog::email_pushbutton_click()
{
    auto httpMgr = HttpMgr::GetInstance();
    QString email = ui->email_lineEdit->text().trimmed();
    if(email.isEmpty()) {
        showTip(tr("邮箱不能为空"), false);
        return;
    }
    QString url = "http://127.0.0.1:8080/get_varifycode";
    QJsonObject json_object;
    json_object["email"]=email;
    httpMgr->PostHttpReq(url,json_object,ID_GET_VARIFY_CODE,REGISITERMOD);
}

