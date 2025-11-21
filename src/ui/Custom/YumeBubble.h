//
// Created by 残梦 on 2025/9/2.
//

#ifndef YUMEBUBBLE_H
#define YUMEBUBBLE_H
#include <QLabel>
#include <QWidget>
#include<QPainter>
#include<QTextEdit>
#include<QAbstractTextDocumentLayout>

#include "UnScrollTextEdit.h"
#include<QVBoxLayout>
class YumeBubble :public QWidget
{
public:
    [[nodiscard]] QVBoxLayout * content_layout() const
    {
        return _contentLayout;
    }

private:
    Q_OBJECT

public:
    YumeBubble(QWidget* parent=nullptr);
    void set_text(const QString& text);
    QSize sizeHint() const {
        int idealWidth = _text->document()->idealWidth() + 16;  // 加上边距
        int idealHeight = _text->document()->size().height() + 6;
        return QSize(idealWidth, idealHeight);
    }
protected:
void paintEvent(QPaintEvent *event) override
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor::fromString("#0099FF"));

    QPen pen;
    pen.setColor(Qt::transparent);
    painter.setPen(pen);

    // 获取文档的理想宽度（自动调整到文本实际宽度）
    qreal idealWidth = _text->document()->idealWidth();
    qreal docHeight = _text->document()->size().height();

    // 计算背景矩形（基于文本控件的位置）
    QRectF bgRect(
        _text->pos().x()-3,          // x
        _text->pos().y()-3 ,         // y
        idealWidth+5  ,           // width (+左右边距)
        docHeight +5             // height (+上下边距)
    );

    // 绘制圆角矩形背景
    painter.drawRoundedRect(bgRect, 6, 6);
}
private:
    QWidget *_content;
    QVBoxLayout *_contentLayout;
    UnScrollTextEdit *_text;
    QVBoxLayout *_mainLayout;
};



#endif //YUMEBUBBLE_H
