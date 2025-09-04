//
// Created by 残梦 on 2025/9/1.
//

#include "CircleAvatar.h"

#include <QWindow>


CircleAvatar::CircleAvatar(QWidget *parent)
: QLabel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setFixedSize(40, 40);
}

void CircleAvatar::set_icon(const QString &path)
{
    _avatar.load(path);
    if (!_avatar.isNull())
    {
        _avatar = setPixmapDpi(size(),_avatar);
    }

}

void CircleAvatar::set_icon(const QPixmap &avatar)
{
    _avatar = setPixmapDpi(size(),avatar);
}



