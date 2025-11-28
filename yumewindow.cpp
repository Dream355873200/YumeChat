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


    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_InputMethodEnabled);

    // 安装事件过滤器
    this->installEventFilter(this);

    // 确保中心部件可以接收事件
    central_widget->setMouseTracking(true);
    central_widget->installEventFilter(this);

    _message_page=new MessagePage(this);
    _friend_page=new FriendPage(this);

    stacked_widget=new QStackedWidget(this);
    stacked_widget->addWidget(_message_page);
    stacked_widget->addWidget(_friend_page);
    stacked_widget->setContentsMargins(0,0,0,0);






    _h_layout->addWidget(stacked_widget);
    stacked_widget->setCurrentIndex(0);

    connect(_toolwidget->message(),&QAbstractButton::clicked,this,&YumeWindow::SlotMessage,Qt::QueuedConnection);
    connect(_toolwidget->friends(),&QAbstractButton::clicked,this,&YumeWindow::SlotFriends,Qt::QueuedConnection);
    connect(_titlebar->_x,&YumeLabel::clicked,this,&YumeWindow::SlotClose);


    resize(1200,800);
    setMinimumWidth(600);
}

YumeWindow::~YumeWindow()
{

}
bool YumeWindow::eventFilter(QObject *watched, QEvent *event)
{
    // 监控窗口点击事件
    if ((watched == this || watched == centralWidget()) && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint clickPos = mouseEvent->pos();

        // 检查是否点击了真正的空白区域
        if (isClickInBlankArea(clickPos))
        {
            qDebug() << "点击空白区域，设置焦点到窗口";
            this->setFocus(); // 主动设置焦点
            return true; // 事件已处理
        }
    }

    return FramelessMainWindow::eventFilter(watched, event);
}

bool YumeWindow::isClickInBlankArea(const QPoint &pos)
{
    // 检查点击位置是否在所有子控件的外部
    return !_titlebar->geometry().contains(pos) &&
           !_toolwidget->geometry().contains(pos) &&
           !stacked_widget->geometry().contains(pos) &&
           !_chat_area->geometry().contains(pos);
}
void YumeWindow::SlotClose()
{
    this->close();
}

void YumeWindow::SlotMessage()
{
    stacked_widget->setCurrentIndex(0);
}

void YumeWindow::SlotFriends()
{
    stacked_widget->setCurrentIndex(1);

}

void YumeWindow::SlotOpen()
{
    this->show();
}
