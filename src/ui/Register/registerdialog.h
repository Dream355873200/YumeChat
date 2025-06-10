//
// Created by 残梦 on 2025/6/2.
//

#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QJsonObject>

#include"logic/Global/global.h"
#include "logic/HttpMgr/HttpMgr.h"
QT_BEGIN_NAMESPACE
namespace Ui { class RegisterDialog; }
QT_END_NAMESPACE

class RegisterDialog : public QDialog {
Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog() override;

private:
    Ui::RegisterDialog *ui;
    void initHttpHandlers();
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    void showTip(QString msg,bool flag);

public slots:
  void  slot_reg_mod_finish(ReqId req_id,QByteArray res,ErrorCodes error_codes);
    void email_pushbutton_click();
signals:
    void SwitchLogin();

};


#endif //REGISTERDIALOG_H
