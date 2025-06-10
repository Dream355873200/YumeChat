//
// Created by 残梦 on 2025/8/2.
//

#include "YumeTitleBar.h"

YumeTitleBar::YumeTitleBar(QWidget *parent)
    : QWidget(parent), _main_layout(new QHBoxLayout(this)), _x(new YumeLabel(this))
{
    // 确保设置可见性
    setVisible(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setAttribute(Qt::WA_TranslucentBackground);
    _main_layout->setContentsMargins(7, 0, 7, 0);
    _main_layout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    _main_layout->addWidget(_x);
    setFixedHeight(20);
    effect = new QGraphicsColorizeEffect;
    effect->setColor(_effect_color);
    effect->setStrength(_normal_rate);
    _x->set_icon(":Resource/ico/IconamoonClose.png");
    _x->setFixedSize(23, 23);
    _x->setGraphicsEffect(effect);
    _x->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    _x->installEventFilter(this);
}

YumeTitleBar::~YumeTitleBar()
{
}

QHBoxLayout *YumeTitleBar::GetMainLayout()
{
    return _main_layout;
}

void YumeTitleBar::setIconEffect(const float normal_rate, const float hover_rate, const QColor &effect_color)
{
    _normal_rate=normal_rate;
    _effect_color=effect_color;
    _hover_rate=hover_rate;
    effect->setColor(_effect_color);
    effect->setStrength(_normal_rate);
    this->update();
}

// 鼠标按下事件处理
void YumeTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragStartPosition = event->globalPos();
        m_windowPosition = window()->pos(); // 直接获取窗口位置
    }
    // 不要调用父类事件处理，避免事件被过滤
}

void YumeTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {

        QPoint delta = event->globalPos() - m_dragStartPosition;
        window()->move(m_windowPosition + delta);
    }
}

bool YumeTitleBar::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == _x)
    {
        if (event->type() == QEvent::Enter)
        {
            effect->setStrength(_hover_rate);
            _x->update();
            return true;
        } else if (event->type() == QEvent::Leave)
        {
            effect->setStrength(_normal_rate);
            _x->update();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}
