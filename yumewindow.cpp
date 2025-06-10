#include "yumewindow.h"

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

    _toolwidget=new ToolWidget(central_widget);
    _mainlayout->addWidget(_toolwidget);

    connect(_titlebar->_x,&YumeLabel::clicked,this,&YumeWindow::SlotClose);
}

YumeWindow::~YumeWindow()
{
    // 清理资源
}

void YumeWindow::SlotClose()
{
    this->close();
}
