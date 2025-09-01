//
// Created by 残梦 on 2025/6/2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RegisterDialog.h" resolved

#include "registerdialog.h"
#include "yume_ui_reg.h"


RegisterDialog::RegisterDialog(QWidget *parent) : QDialog(parent), ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->cancel_pushButton, &QPushButton::clicked, this, &RegisterDialog::SwitchLogin);

    connect(ui->email_pushButton, &QPushButton::clicked, this, &RegisterDialog::email_pushbutton_click);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
    connect(ui->confirm_pushButton, &QPushButton::clicked, this, &RegisterDialog::userReg_pushbutton_click);
    initHttpHandlers();
    ui->show_label->setText("");


    timer = new QTimer(ui->email_pushButton);
    connect(timer, &QTimer::timeout,
            [this, originalText = ui->email_pushButton->text(), count = 60]() mutable
            {
                ui->email_pushButton->setText(QString::number(--count));

                if (count <= 0)
                {
                    timer->stop();
                    ui->email_pushButton->setEnabled(true);
                    ui->email_pushButton->setStyleSheet("");
                    ui->email_pushButton->setText(originalText);
                    timer->deleteLater();
                }
            });
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject &json_object)
    {
        int error = json_object["error"].toInt();
        qDebug() << "Error code:" << error;
        if (error == ErrorCodes::ERR_JSON)
        {
            showTip(tr("服务器JSON解析失败或无email对象"), false);
            return;
        }
        if (error == ErrorCodes::ERR_USER_EXSIT)
        {
            showTip(tr("邮箱已存在"), false);
            return;
        }
        if (error != ErrorCodes::SUCCESS)
        {
            showTip(tr("参数错误,验证码发送失败"), false);
            qDebug() << "False";
            return;
        }
        auto email = json_object["email"].toString();
        qDebug() << "True";
        showTip(tr("验证码已经发送到邮箱，请查收"), true);
        qDebug() << "email is" << email;
    });

    _handlers.insert(ReqId::ID_REG_USER, [this](const QJsonObject &json_object)
    {
        int error = json_object["error"].toInt();
        qDebug() << "Error code:" << error;
        if (error == ErrorCodes::ERR_CODE_REG)
        {
            showTip(tr("验证码不存在"), false);
            return;
        }
        if (error == ErrorCodes::ERR_USER_EXSIT)
        {
            showTip(tr("邮箱已存在"), false);
            return;
        }
        if (error != ErrorCodes::SUCCESS)
        {
            showTip(tr("注册失败"), false);
            qDebug() << "False";
            return;
        }
        qDebug() << "True";
        showTip(tr("注册成功"), true);
    });
}

void RegisterDialog::showTip(QString msg, bool flag)
{
    ui->show_label->setText(msg);
}

void RegisterDialog::slot_reg_mod_finish(ReqId req_id, const QByteArray &res, ErrorCodes error_codes)
{
    if (error_codes == ErrorCodes::ERR_NETWORK)
    {
        showTip(tr("网络请求错误"), false);
        return;
    }

    //解析JSON字符串
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res);
    if (jsonDoc.isNull())
    {
        showTip(tr("JSON解析失败"), false);
        return;
    }
    //JSON解析错误
    if (!jsonDoc.isObject())
    {
        showTip(tr("JSON解析失败"), false);
        return;
    }
    // 检查是否存在该req_id的处理器
    if (!_handlers.contains(req_id))
    {
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
    if (email.isEmpty())
    {
        showTip(tr("邮箱不能为空"), false);
        return;
    }

    ui->email_pushButton->setStyleSheet(
        "QPushButton:disabled { background-color: gray; }"
        "QPushButton:disabled:hover { background: gray; }" // 禁用状态下按下时不变化
    );
    ui->email_pushButton->setEnabled(false);
    ui->email_pushButton->setText("60");
    timer->start(1000);

    QString url = "http://127.0.0.1:8080/get_varifycode";
    QJsonObject json_object;
    json_object["email"] = email;
    httpMgr->PostHttpReq(url, json_object, ID_GET_VARIFY_CODE, REGISITERMOD);
}

void RegisterDialog::userReg_pushbutton_click()
{
    auto httpMgr = HttpMgr::GetInstance();
    QString password = ui->pass_lineEdit->text().trimmed();
    QString email = ui->email_lineEdit->text().trimmed();
    QString verify_code = ui->code_lineEdit->text().trimmed();
    if (email.isEmpty())
    {
        showTip(tr("邮箱不能为空"), false);
        return;
    }
    if (password.isEmpty())
    {
        showTip(tr("密码不能为空"), false);
        return;
    }
    if (verify_code.isEmpty())
    {
        showTip(tr("验证码不能为空"), false);
        return;
    }
    if (ui->pass1_lineEdit->text() != ui->pass_lineEdit->text())
    {
        showTip(tr("两次输入密码不同"), false);
        return;
    }
    qDebug() << "开始注册";
    QString url = "http://127.0.0.1:8080/user_Reg";
    QJsonObject json_object;
    json_object["password"] = password;
    json_object["email"] = email;
    json_object["code"] = verify_code;
    httpMgr->PostHttpReq(url, json_object, ID_REG_USER, REGISITERMOD);
}
