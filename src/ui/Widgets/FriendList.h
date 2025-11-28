//
// Created by 残梦 on 2025/10/15.
//

#ifndef FRIENDLIST_H
#define FRIENDLIST_H
#include "FriendWidget.h"
#include "ui/Custom/SmoothListWidget.h"


class SearchWidget;

class FriendList : public QWidget
{
    Q_OBJECT
    friend class FriendPage;
public:
    explicit FriendList(QWidget *parent = nullptr);

    ~FriendList() override;
    void add_friend_widget();
protected:
private:
    QVBoxLayout* _main_layout;
    SearchWidget* _search;
    SmoothListWidget *_list;
    QButtonGroup *buttonGroup ;
    FriendWidget* _friendwidget;
    int button_num=0;
    int width=220;
};



#endif //FRIENDLIST_H
