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
    void set_show_status_dot(bool show_status_dot)
    {
        _showStatusDot = show_status_dot;
    }

    void set_is_online(bool is_online)
    {
        _isOnline = is_online;
    }

    explicit CircleAvatar(QWidget *parent = nullptr);
    void set_icon(const QString& path);
    void set_icon(const QPixmap& avatar);
protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.save();
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

        painter.restore();
        if (_showStatusDot) {
            int dotSize = 10;      // 圆点直径
            int margin = 0;        // 距离边缘的边距
            QPoint dotCenter(
                width() - margin - dotSize / 2,
                height() - margin - dotSize / 2
            );

            // 根据在线状态选择颜色
            QColor dotColor = _isOnline ? QColor(0, 200, 0) : Qt::gray;

            // 绘制圆点
            painter.setPen(Qt::NoPen);
            painter.setBrush(dotColor);
            painter.drawEllipse(dotCenter, dotSize / 2, dotSize / 2);

            // 可选：白色边框
            painter.setPen(QPen(Qt::white, 1));  // 线宽1像素
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(dotCenter, dotSize / 2, dotSize / 2);  // 使用相同半径
        }

    }
private:
    QPixmap _avatar;
    bool _showStatusDot = false; // 默认不显示圆点
    bool _isOnline = false;
};



#endif //CIRCLEAVATAR_H
