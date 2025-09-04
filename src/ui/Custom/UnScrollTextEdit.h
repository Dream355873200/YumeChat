//
// Created by 残梦 on 2025/9/4.
//

#ifndef UNSCROLLTEXTEDIT_H
#define UNSCROLLTEXTEDIT_H


#include <qevent.h>
#include <QTextEdit>

class UnScrollTextEdit : public QTextEdit {
    Q_OBJECT
public:
    using QTextEdit::QTextEdit;

protected:
    void wheelEvent(QWheelEvent *event) override {
        event->ignore(); // 阻止滚轮事件
    }
};

#endif //UNSCROLLTEXTEDIT_H
