//
// Created by 残梦 on 2025/9/1.
//

#include "CircleAvatar.h"



CircleAvatar::CircleAvatar(QWidget *parent)
: QLabel(parent)
{
    setFixedSize(40, 40);
}

void CircleAvatar::set_icon(const QString &path)
{
    _avatar.load(path);
    this->setPixmap(setPixmapDpi(this->size(),_avatar));
}



