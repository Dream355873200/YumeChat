//
// Created by 残梦 on 2025/8/1.
//

#include "YumeLabel.h"

#include <QMouseEvent>

#include "logic/Global/global.h"

YumeLabel::YumeLabel(QWidget *parent)
    :QLabel(parent)
{
    QPalette pale;
    pale.setColor(QPalette::WindowText,QColor::fromString("#2d77e5"));
    this->setPalette(pale);
    this->setCursor(Qt::PointingHandCursor);
    this->setScaledContents(true);

    this->installEventFilter(this);
}

void YumeLabel::set_text(const QString &text)
{
    this->setText(text);
    this->adjustSize();
}

void YumeLabel::set_font_size(int size)
{
    QFont font;
    font.setPixelSize(size);
    this->setFont(font);
}

void YumeLabel::set_icon(const QString& path)
{
    _icon.load(path);
    this->setPixmap(setPixmapDpi(this->size(),_icon));
}

void YumeLabel::set_font_color(const QColor &color)
{
    this->setStyleSheet(QString("color: %1;").arg(color.name()));
}


bool YumeLabel::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        
        if (event->type() == QEvent::MouseButtonPress)
        {
            // 记录按下时的位置
            QPoint m_pressPos = mouseEvent->pos();
            return true; // 拦截按下事件
        }
        else if (event->type() == QEvent::MouseMove)
        {
            return true; // 拦截移动事件
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            // 检查释放位置是否在标签区域内
            if (rect().contains(mouseEvent->pos()))
            {
                emit clicked();
                // 在标签区域内释放，拦截事件
                return true;
            }
            else
            {
                // 在标签区域外释放（比如按钮上），允许事件传递
                return false;
            }
        }
    }
    return QLabel::eventFilter(watched, event);
}


