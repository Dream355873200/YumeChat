#include "mainwindow.h"

#include <QVBoxLayout>



#include "ui/Custom/YumeTitleBar.h"

MainWindow::MainWindow(QWidget *parent,std::shared_ptr<YumeWindow> yume_window)
    : FramelessMainWindow(parent),_yume_window(yume_window)
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
    connect(login_dialog,&LoginDialog::login_succeess,this,&MainWindow::SlotToYumeWindow,Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
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

void MainWindow::SlotToYumeWindow()
{
    _yume_window=std::make_shared<YumeWindow>();
    this->close();
    _yume_window->show();
}
