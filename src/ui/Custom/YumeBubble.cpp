//
// Created by 残梦 on 2025/9/2.
//

#include "YumeBubble.h"

#include <QVBoxLayout>

class QVBoxLayout;

YumeBubble::YumeBubble(QWidget *parent)
{
    // 主部件设置


    // 内容部件
    QWidget *content = new QWidget(this);
    content->setObjectName("bubbleContent");

    // 主布局 - 直接设置到主部件
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 15);
    mainLayout->addWidget(content);

    // 文本标签 - 直接添加到内容部件
    _text = new QTextEdit(content);
    _text->setTextColor(Qt::white);
    _text->setReadOnly(true);
    _text->setWordWrapMode(QTextOption::WrapAnywhere);

    _text->setFrameStyle(QFrame::NoFrame);
    _text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 内容布局 - 确保正确设置
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(8, 8, 8, 8);
    contentLayout->addWidget(_text);

    // 确保内容部件可以扩展
    content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

void YumeBubble::set_text(const QString &text)
{
    _text->setText(text);
}
