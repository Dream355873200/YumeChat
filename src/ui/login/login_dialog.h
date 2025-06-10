//
// Created by 残梦 on 2025/5/31.
//

#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog {
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog() override;

private:
    Ui::LoginDialog *ui ;

signals:
   void SwitchReg();

};


#endif //LOGIN_DIALOG_H
