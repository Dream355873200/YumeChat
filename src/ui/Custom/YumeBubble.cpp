//
// Created by 残梦 on 2025/9/2.
//

#include "YumeBubble.h"


class QVBoxLayout;

YumeBubble::YumeBubble(QWidget *parent)
    :QWidget(parent)
{
    // 主部件设置


    // 内容部件
    _content = new QWidget(this);
    _content->setObjectName("bubbleContent");

    // 主布局 - 直接设置到主部件
   _mainLayout = new QVBoxLayout;
    this->setLayout(_mainLayout);
    _mainLayout->setContentsMargins(0, 0, 0, 0);
    _mainLayout->addWidget(_content);

    // 文本标签 - 直接添加到内容部件
    _text = new UnScrollTextEdit(_content);
    _text->setTextColor(Qt::white);
    _text->setReadOnly(true);
    _text->setWordWrapMode(QTextOption::WrapAnywhere);
    //去掉文字背景色
    _text->setStyleSheet("background: transparent; border: none;");

    _text->setFrameStyle(QFrame::NoFrame);
    _text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 内容布局 - 确保正确设置
    _contentLayout = new QVBoxLayout(_content);
    _contentLayout->setContentsMargins(5, 3, 120, 0);
    _contentLayout->addWidget(_text);

    // 确保内容部件可以扩展
    _content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

void YumeBubble::set_text(const QString &text)
{
    _text->setText(text);
}
