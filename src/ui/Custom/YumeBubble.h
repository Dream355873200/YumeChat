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
class YumeBubble :public QWidget
{
    Q_OBJECT
public:
    YumeBubble(QWidget* parent=nullptr);
    void set_text(const QString& text);
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
        _text->pos().x()+5,          // x
        _text->pos().y()+5,          // y
        idealWidth + 10,           // width (+左右边距)
        docHeight + 10             // height (+上下边距)
    );

    // 绘制圆角矩形背景
    painter.drawRoundedRect(bgRect, 8, 8);
}
private:

    QTextEdit *_text;
};



#endif //YUMEBUBBLE_H
