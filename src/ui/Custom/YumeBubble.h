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
#include <QStyle>

#include "UnScrollTextEdit.h"
#include<QVBoxLayout>
class YumeBubble :public QWidget
{
public:

private:
    Q_OBJECT

public:
    YumeBubble(QWidget* parent=nullptr);
    void set_text(const QString& text);
    QSize sizeHint() const {
        // 使用当前设置的maximumWidth作为宽度，或者计算理想宽度
        int idealWidth = this->maximumWidth();
        if (idealWidth == QWIDGETSIZE_MAX) { // 如果没有设置最大宽度
            idealWidth = _text->document()->idealWidth() + 16;
        }
        int idealHeight = _text->document()->size().height() + 6;
        return QSize(idealWidth, idealHeight);
    }
protected:
void paintEvent(QPaintEvent *event) override
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(_current_color);

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
    QColor _self_color=QColor::fromString("#0099FF");
    QColor _other_color=Qt::white;
    QColor _current_color=QColor::fromString("#0099FF");

public:
    void set_text_color(const QColor& color)
    {
        QPalette pal = _text->palette();
        pal.setColor(QPalette::Text, color);
        _text->setPalette(pal);//设置未来的颜色

        QTextCursor cursor = _text->textCursor();
        cursor.select(QTextCursor::Document);

        // 2. 应用颜色格式
        QTextCharFormat fmt;
        fmt.setForeground(color);
        cursor.mergeCharFormat(fmt);

        // 3. 【最关键】此时先不要清除选区，直接把这个带着“变色指令”的游标设置给控件
        _text->setTextCursor(cursor);

        // 4. 【解决蓝色高亮】设置完后，再把游标清空并重新设置一次
        cursor.clearSelection();//!!未知的bug，在setTextCursor(cursor)前清除选中会导致颜色不改变
        _text->setTextCursor(cursor);//替换现有的颜色
    }
    void set_current_color(const QColor &current_color)
    {
        _current_color = current_color;
    }
    void set_to_other_color()
    {
        _current_color = _other_color;

        set_text_color(Qt::black);

        this->update(); // 触发 paintEvent 重新绘制背景圆角矩形
    }
    void set_to_self_color()
    {
        _current_color = _self_color;

        set_text_color(Qt::white);

        this->update(); // 触发 paintEvent 重新绘制背景圆角矩形
    }
private:
    UnScrollTextEdit *_text;
    QVBoxLayout *_mainLayout;
};



#endif //YUMEBUBBLE_H
