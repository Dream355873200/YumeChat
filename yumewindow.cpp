#include "yumewindow.h"

#include <QStackedWidget>

#include "ui/Widgets/MessagePage.h"
#include "ui/Widgets/toolwidget.h"

YumeWindow::YumeWindow(QWidget *parent)
    : FramelessMainWindow(parent)
{
    // 创建中心部件
    auto central_widget = new QWidget(this);
    setCentralWidget(central_widget);
    
    // 创建主布局
    _mainlayout = new QVBoxLayout(central_widget);
    
    // 移除菜单栏和状态栏
    setMenuBar(nullptr);
    setStatusBar(nullptr);
    
    // 创建标题栏
    _titlebar = new YumeTitleBar(central_widget);

    // 设置布局
    _mainlayout->addWidget(_titlebar);
    _mainlayout->setContentsMargins(0, 0, 0, 0);
    _mainlayout->setSpacing(0);
    _mainlayout->setAlignment(Qt::AlignTop);

    // 设置中心部件的边距
    central_widget->setContentsMargins(0, 6, 0, 0);
    
    // 确保标题栏可见
    _titlebar->setVisible(true);
    _titlebar->raise(); // 确保标题栏在最上层

    _titlebar->setIconEffect(1.0,0.2,Qt::black);
    _titlebar->setFixedHeight(40);

    _h_layout=new QHBoxLayout;
    _h_layout->setContentsMargins(0,0,0,0);
    _h_layout->setAlignment(Qt::AlignLeft);
    _mainlayout->addLayout(_h_layout);

    _toolwidget=new ToolWidget(central_widget);
    _h_layout->addWidget(_toolwidget);

    _chat_area=new ChatArea(this);




    _message_page=new MessagePage(this);
    stacked_widget=new QStackedWidget(this);
    stacked_widget->addWidget(_message_page);
    stacked_widget->setContentsMargins(0,0,0,0);






    _h_layout->addWidget(stacked_widget);
    stacked_widget->setCurrentIndex(0);

    connect(_toolwidget->message(),&QAbstractButton::clicked,this,&YumeWindow::SlotMessage,Qt::QueuedConnection);
    connect(_toolwidget->friends(),&QAbstractButton::clicked,this,&YumeWindow::SlotFriends,Qt::QueuedConnection);
    connect(_titlebar->_x,&YumeLabel::clicked,this,&YumeWindow::SlotClose);
}

YumeWindow::~YumeWindow()
{

}

void YumeWindow::SlotClose()
{
    this->close();
}

void YumeWindow::SlotMessage()
{
    stacked_widget->show();
    stacked_widget->setCurrentIndex(0);
}

void YumeWindow::SlotFriends()
{
    stacked_widget->hide();
}
