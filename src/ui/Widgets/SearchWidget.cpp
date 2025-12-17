#include "SearchWidget.h"

#include <QApplication>
#include <QTimer>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent)
{
    _main_layout = new QHBoxLayout(this);
    _main_layout->setContentsMargins(0, 0, 5, 0);
    _main_layout->setAlignment(Qt::AlignRight);

    _label = new YumeLabel(this);
    _label->set_text("Message");
    _label->setAlignment(Qt::AlignLeft);
    _label->setContentsMargins(15, 0, 15, 0);
    _label->set_font_size(17);
    _label->set_font_type(":/Resource/font/flache.ttf");
    _label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _search = new YumeLineEdit(this);
    _search->setMode(LineEditMode::Search);
    _search->setFixedHeight(25);
    _search->setFixedWidth(_search_width);

    _add_friend = new YumeButton(this);
    _add_friend->setFixedSize(25, 25);
    _add_friend->label()->setFixedSize(15, 15);
    _add_friend->setNormalColor(QColor(230, 230, 230));
    _add_friend->setHoverColor(QColor(200, 200, 200));
    _add_friend->setIcon(":/Resource/ico/IconAdd.png");

    _notice_button = new YumeButton(this);
    _notice_button->setFixedSize(25, 25);
    _notice_button->label()->setFixedSize(15, 15);
    _notice_button->setNormalColor(QColor(230, 230, 230));
    _notice_button->setHoverColor(QColor(200, 200, 200));
    _notice_button->setIcon(":/Resource/ico/RiNotification3Line.png");

    _main_layout->addWidget(_label);
    _main_layout->addWidget(_search);
    _main_layout->addWidget(_add_friend);
    _main_layout->addWidget(_notice_button);

    // 安装事件过滤器

    _search->lineEdit()->installEventFilter(this); // 新增这行
    // 初始化动画
    _search_animation = new QPropertyAnimation(_search, "minimumWidth"); // 使用minimumWidth属性
    _search_animation->setDuration(300);
    _search_animation->setEasingCurve(QEasingCurve::OutCubic);

    _label_animation = new QPropertyAnimation(_label, "windowOpacity");
    _label_animation->setDuration(300);
}

SearchWidget::~SearchWidget()
{
}

void SearchWidget::set_text(const QString &message)
{
    _label->set_text(message);
}


bool SearchWidget::eventFilter(QObject *watched, QEvent *event)
{
    // 新增：监控内部QLineEdit的焦点事件
    if (watched == _search->lineEdit())
    {
        if (event->type() == QEvent::FocusIn)
        {
            //  qDebug() << "内部QLineEdit获得焦点";
            if (!_isExpanded)
            {
                expandSearch();
                _isExpanded = true;
            }
        } else if (event->type() == QEvent::FocusOut)
        {
            //    qDebug() << "内部QLineEdit失去焦点";
            if (_isExpanded)
            {
                QTimer::singleShot(100, this, [this]()
                {
                    QWidget *focusWidget = QApplication::focusWidget();
                    if (focusWidget != _search->lineEdit())
                    {
                        collapseSearch();
                        _isExpanded = false;
                    }
                });
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void SearchWidget::expandSearch()
{
    // 停止当前动画

    _search_animation->stop();
    _label_animation->stop();

    // 展开搜索框
    _search_animation->setStartValue(_search_width);
    _search_animation->setEndValue(_search_width + 90);
    _search_animation->start();

    // 隐藏标签
    _label->hide();
}

void SearchWidget::collapseSearch()
{
    // 停止当前动画
    _search_animation->stop();
    _label_animation->stop();

    // 收起搜索框
    _search_animation->setStartValue(170);
    _search_animation->setEndValue(80);
    _search_animation->start();

    // 显示标签（但需要延迟，等搜索框收起后再显示）
    QTimer::singleShot(150, this, [this]()
    {
        _label->show();
    });
}
