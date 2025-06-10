//
// Created by 残梦 on 2025/5/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_login_dialog.h" resolved

#include "login_dialog.h"
#include "ui_login_dialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    connect(ui->reg_pushButton,&QPushButton::clicked,this,&LoginDialog::SwitchReg);
}

LoginDialog::~LoginDialog() {
    delete ui;
}
