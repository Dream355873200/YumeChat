//
// Created by 残梦 on 2025/5/31.
//

#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QPainter>

#include "logic/Global/global.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog {
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog() override;
protected:

private:
    Ui::LoginDialog *ui ;
    void login_pushbutton_click();
public slots:
    void  slot_login_mod_finish(ReqId req_id,const QByteArray& res,ErrorCodes error_codes);
signals:
   void SwitchReg();

};


#endif //LOGIN_DIALOG_H
