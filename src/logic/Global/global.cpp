//
// Created by 残梦 on 2025/8/1.
//

#include"global.h"
qreal Global_ScaleDpi = 1.25;
QPixmap setPixmapDpi(const QSize &size, const QPixmap &pixmap)
{
    QPixmap resultPixmap = pixmap.scaled(size * Global_ScaleDpi, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return resultPixmap;
}