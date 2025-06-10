//
// Created by 残梦 on 2025/8/1.
//

#include "YumeButton.h"

YumeButton::YumeButton(QWidget *parent)
    : QWidget(parent), _label(new YumeLabel(this))
{
    //避免事件过滤器冲突
    _label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _main_layout = new QHBoxLayout(this);
    _main_layout->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setFixedHeight(35);
    this->setFixedWidth(200);
    _main_layout->setContentsMargins(0, 0, 0, 0);

    QPalette pale;
    pale.setColor(QPalette::WindowText, Qt::white);
    _label->setPalette(pale);

    effect = new QGraphicsColorizeEffect;
    this->setGraphicsEffect(effect);

    effect->setStrength(0.0);
    effect->setColor(Qt::black);

    QFont font;
    font.setPixelSize(12);
    _label->setFont(font);

    _main_layout->addWidget(_label, 0, Qt::AlignCenter);
    this->setCursor(Qt::PointingHandCursor);

    this->installEventFilter(this);
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
    painter.drawRoundedRect(this->rect(), 10, 10);
}

bool YumeButton::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        if (event->type() == QEvent::Enter)
        {
            isHovered = true;
            this->update();
            return true;
        }
        if (event->type() == QEvent::Leave)
        {
            isHovered = false;
            this->update();
            return true;
        }
        if (event->type() == QEvent::MouseButtonPress)
        {
            // 转换为鼠标事件并检查左键
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                effect->setStrength(effect_rate);
                this->update();
                return true; // 左键已处理
            }
        }
        if (event->type() == QEvent::MouseButtonRelease)
        {
            // 转换为鼠标事件并检查左键
            emit clicked();
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                effect->setStrength(0.0);
                this->update();
                return true; // 左键已处理
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
