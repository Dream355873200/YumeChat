//
// Created by 残梦 on 2025/8/1.
//

#ifndef YUMELABEL_H
#define YUMELABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>


class YumeLabel:public QLabel
{
public:

private:
    Q_OBJECT

public:
    YumeLabel(QWidget *parent=nullptr);

    void setElideMode(Qt::TextElideMode mode);

    void set_text(const QString& text);
    void set_font_size(int size);
    void set_icon(const QString& path);
    void set_font_color(const QColor& color);
    void set_font_type(const QString& source);
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setOpacity(this->windowOpacity());

        if (m_elideMode != Qt::ElideNone) {

            QFontMetrics metrics(font());
            QString elidedText = metrics.elidedText(text(), m_elideMode, width());
            painter.drawText(rect(), alignment(), elidedText);
        } else {
            QLabel::paintEvent(event);  // 默认绘制
        }
    };

private:
    QPixmap _icon;
    Qt::TextElideMode m_elideMode = Qt::ElideNone;
protected:

    bool eventFilter(QObject *watched, QEvent *event) override;
    signals:
    void clicked();
};



#endif //YUMELABEL_H
