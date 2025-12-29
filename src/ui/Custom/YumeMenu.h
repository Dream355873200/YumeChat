//
// Created by 残梦 on 2025/12/29.
//

#ifndef YUMEMENU_H
#define YUMEMENU_H

#include <QPainter>
#include <QWidget>
#include <QVBoxLayout>

class YumeMenu : public QWidget {
    Q_OBJECT
public:
    explicit YumeMenu(QWidget* parent = nullptr) : QWidget(parent) {
        // 关键：设置为弹出窗口，且去掉标题栏
        setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        // 允许背景透明（如果你想画圆角）
        setAttribute(Qt::WA_TranslucentBackground);

        _layout = new QVBoxLayout(this);
        _layout->setContentsMargins(5, 5, 5, 5);
        _layout->setSpacing(0);
    }

    // 提供一个添加“菜单项”的方法，你可以添加自定义的按钮
    void addWidget(QWidget* w) {
        _layout->addWidget(w);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        // 画自定义背景，例如深灰色圆角矩形
        painter.setBrush(QColor(255, 255, 255));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), 6, 6);
    }

private:
    QVBoxLayout* _layout;
};


#endif //YUMEMENU_H
