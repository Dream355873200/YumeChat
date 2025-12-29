//
// Created by 残梦 on 2025/8/1.
//

#include"global.h"

#include <qjsonvalue.h>


qreal Global_ScaleDpi = 1.25;


std::optional<std::tm> toStdTm(const QJsonValue& val) {
    if (val.isNull() || val.isUndefined()) return std::nullopt;

    QDateTime dt;
    if (val.isDouble()) { // 假设是 Unix 时间戳
        dt = QDateTime::fromSecsSinceEpoch(val.toVariant().toLongLong());
    } else { // 假设是 ISO 字符串
        dt = QDateTime::fromString(val.toString(), Qt::ISODate);
    }

    if (!dt.isValid()) return std::nullopt;

    std::tm result = {};
    QDateTime qdt = dt.toUTC(); // 建议统一用 UTC
    result.tm_year = qdt.date().year() - 1900;
    result.tm_mon = qdt.date().month() - 1;
    result.tm_mday = qdt.date().day();
    result.tm_hour = qdt.time().hour();
    result.tm_min  = qdt.time().minute();
    result.tm_sec  = qdt.time().second();
    return result;
}

QPixmap setPixmapDpi(const QSize &size, const QPixmap &pixmap)
{
    QPixmap resultPixmap = pixmap.scaled(size * Global_ScaleDpi, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    return resultPixmap;
}

QString Global_id="1696806296@qq.com";
QString  Global_host;
uint16_t  Global_port;
QString Global_token;