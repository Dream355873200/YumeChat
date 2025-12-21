//
// Created by 残梦 on 2025/9/2.
//

#include "YumeBubble.h"


class QVBoxLayout;

YumeBubble::YumeBubble(QWidget *parent)
    :QWidget(parent)
{
    this->setMaximumWidth(QWIDGETSIZE_MAX);
    // 主布局 - 直接设置到主部件
   _mainLayout = new QVBoxLayout;
    this->setLayout(_mainLayout);
    _mainLayout->setContentsMargins(4, 4, 0, 0);


    // 文本标签 - 直接添加到内容部件
    _text = new UnScrollTextEdit();


    _text->setReadOnly(true);
    _text->setWordWrapMode(QTextOption::WrapAnywhere);
    //去掉文字背景色
    _text->setStyleSheet("background: transparent; border: none;");
    _text->setFrameStyle(QFrame::NoFrame);
    _text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 内容布局 - 确保正确设置

    _mainLayout->addWidget(_text);

}

void YumeBubble::set_text(const QString &text)
{
    _text->setText(text);


    // 获取字体度量
    QFontMetrics fm(_text->font());

    // 按换行符分割文本
    QStringList lines = text.split('\n');

    // 找到最长行的宽度
    int maxLineWidth = 0;
    for (const QString& line : lines) {
        int lineWidth = fm.horizontalAdvance(line);
        if (lineWidth > maxLineWidth) {
            maxLineWidth = lineWidth;
        }
    }

    // 边距
    int textWidth = maxLineWidth + 16;

    // 设置最大宽度为最长行的宽度
    this->setMaximumWidth(textWidth);
}
