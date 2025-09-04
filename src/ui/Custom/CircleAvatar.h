//
// Created by 残梦 on 2025/9/1.
//

#ifndef CIRCLEAVATAR_H
#define CIRCLEAVATAR_H
#include <QLabel>
#include <QPainter>
#include<QPainterPath>
#include "logic/Global/global.h"
class CircleAvatar:public QLabel
{
public:
    explicit CircleAvatar(QWidget *parent = nullptr);
    void set_icon(const QString& path);
    void set_icon(const QPixmap& avatar);
protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // 绘制圆形剪裁区域
        QPainterPath path;
        path.addEllipse(rect());
        painter.setClipPath(path);

        // 绘制头像图片或背景
        if (!_avatar.isNull()) {
            painter.drawPixmap(rect(), _avatar);
        } else {
            painter.fillRect(rect(), QColor("#f0f0f0"));

            // 可选：绘制默认图标或文字
            painter.setPen(Qt::darkGray);
           painter.drawText(rect(), Qt::AlignCenter, "头像");
        }

        // 可选：绘制边框
       // painter.setPen(QPen(Qt::lightGray, 1));
        //painter.drawEllipse(rect());
    }
private:
    QPixmap _avatar;
};



#endif //CIRCLEAVATAR_H
