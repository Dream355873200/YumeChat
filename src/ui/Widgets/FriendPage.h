//
// Created by 残梦 on 2025/10/15.
//

#ifndef FRIENDPAGE_H
#define FRIENDPAGE_H
#include "FriendList.h"
#include "FriendWidget.h"


class FriendPage :public QWidget
{
    Q_OBJECT
public:
    FriendPage(QWidget* parent=nullptr);
    ~FriendPage();
protected:

private:
    QHBoxLayout* _main_layout;
    FriendList* _friend_list;
};



#endif //FRIENDPAGE_H
