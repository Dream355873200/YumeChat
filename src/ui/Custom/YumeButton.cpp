//
// Created by 残梦 on 2025/8/1.
//

#include "YumeButton.h"

#include <QTimer>

YumeButton::YumeButton(QWidget *parent)
    : QAbstractButton(parent), _label(new YumeLabel(this))
{

    setCheckable(true); // 让按钮可以被选中

    _timer=new QTimer(this);
    //避免事件过滤器冲突
    _label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _main_layout = new QHBoxLayout(this);
    _main_layout->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setFixedHeight(35);

    _main_layout->setContentsMargins(0, 0, 0, 0);

    QPalette pale;
    pale.setColor(QPalette::WindowText, QColor(255, 255, 255));
    _label->setPalette(pale);
    effect = new QGraphicsColorizeEffect;
    this->setGraphicsEffect(effect);

    effect->setStrength(0.0);
    effect->setColor(Qt::black);

    QFont font;
    font.setPixelSize(12);
    _label->setFont(font);

    _main_layout->addWidget(_label, 0, Qt::AlignCenter);
    _label->setAlignment(Qt::AlignCenter);
    this->setCursor(Qt::PointingHandCursor);

    this->installEventFilter(this);

    connect(_timer,&QTimer::timeout,this,&YumeButton::double_clicked_timer);

}

YumeButton::~YumeButton()
{
}

void YumeButton::setText(const QString &text)
{
    _label->setText(text);
    _label->adjustSize();
}

void YumeButton::setIcon(const QString &file)
{
    _label->set_icon(file);
    _label->update();
}

void YumeButton::setHoverColor(const QColor &color)
{
    hoverColor = color;
    this->update();
}

void YumeButton::setNormalColor(const QColor &color)
{
    normalColor = color;
    this->update();
}

void YumeButton::setFontColor(const QColor &color) const
{
    _label->set_font_color(color);
}

void YumeButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    if (isHovered)
    {
        painter.setBrush(hoverColor);
    } else
    {
        painter.setBrush(normalColor);
    }

    painter.drawRoundedRect(this->rect(), 6, 6);
}

bool YumeButton::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this) {
        if (event->type() == QEvent::Enter) {
            isHovered = true;

            update();
            return true; // 悬停事件可拦截
        }
        if (event->type() == QEvent::Leave) {
            isHovered = false;
            update();
            return true; // 悬停事件可拦截
        }
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {

                _is_clicked++;
                if(_is_clicked==1)
                {
                    _timer->setInterval(200);
                    _timer->start();
                }
                if(_is_clicked==2)
                {
                    emit double_click();
                    _timer->stop();
                }
                //实现双击

                effect->setStrength(effect_rate);
                update();
                return false; // 关键：允许事件继续传递
            }
        }
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                effect->setStrength(0.0);
                update();
                return false; // 关键：允许事件继续传递
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void YumeButton::double_clicked_timer()
{
    _is_clicked=0;
}
void YumeButton::hideEvent(QHideEvent *event) {
    this->set_is_hovered(false);
    this->set_is_selected(false);
    QAbstractButton::hideEvent(event);
}