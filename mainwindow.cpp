#include "mainwindow.h"

#include <QVBoxLayout>



#include "ui/Custom/YumeTitleBar.h"

MainWindow::MainWindow(QWidget *parent)
    : FramelessMainWindow(parent)
{

    Global_ScaleDpi=window()->windowHandle()->devicePixelRatio();


    setMenuBar(nullptr);
    setStatusBar(nullptr);

    login_dialog=new LoginDialog(this);
    reg_dialog=new RegisterDialog(this);
    stack_widget=new QStackedWidget(this);

    stack_widget->addWidget(login_dialog);
    stack_widget->addWidget(reg_dialog);

    auto central_widget=new QWidget(this);
    central_widget->setContentsMargins(0,6,0,0);

    auto title_bar=new YumeTitleBar(central_widget);
    auto v_layout=new QVBoxLayout(central_widget);



    v_layout->addWidget(title_bar);
    v_layout->addWidget(stack_widget);
    //去除布局边距
    v_layout->setContentsMargins(0, 0, 0, 0);


    setCentralWidget(central_widget);
    stack_widget->setCurrentIndex(0);



    connect(login_dialog, &LoginDialog::SwitchReg, this, &MainWindow::SlotSwitchReg, Qt::QueuedConnection);
    connect(reg_dialog, &RegisterDialog::SwitchLogin, this, &MainWindow::SlotSwitchLogin, Qt::QueuedConnection);
    connect(title_bar->_x,&YumeLabel::clicked,this,&MainWindow::SlotClose);
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

void MainWindow::SlotClose()
{
    this->close();
}
