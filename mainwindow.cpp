#include "mainwindow.h"


#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dialog=new LoginDialog(this);
    reg_dialog=new RegisterDialog(this);
    stack_widget=new QStackedWidget(this);

    stack_widget->addWidget(login_dialog);
    stack_widget->addWidget(reg_dialog);

    setCentralWidget(stack_widget);
    stack_widget->setCurrentIndex(0);
    login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    reg_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);


    connect(login_dialog, &LoginDialog::SwitchReg, this, &MainWindow::SlotSwitchReg, Qt::QueuedConnection);
    connect(reg_dialog, &RegisterDialog::SwitchLogin, this, &MainWindow::SlotSwitchLogin, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    stack_widget->setCurrentIndex(1);

}

void MainWindow::SlotSwitchLogin()
{
    stack_widget->setCurrentIndex(0);
}
