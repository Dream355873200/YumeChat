//
// Created by 残梦 on 2025/11/28.
//

#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H
#include "../../../framelessmainwindow.h"
#include "ui/Custom/SmoothListWidget.h"
#include "ui/Custom/YumeButton.h"
#include "ui/Custom/YumeLineEdit.h"
#include "ui/Custom/YumeTitleBar.h"


class SelectWindow:public FramelessMainWindow
{
    Q_OBJECT
public:
    SelectWindow();
private:
    YumeTitleBar* _title_bar;
    YumeLineEdit* _search;
    YumeButton* _button;
    QWidget* _central_widget;
    QVBoxLayout* _main_layout;
    QHBoxLayout* _search_layout;
    SmoothListWidget* _list;

};



#endif //SELECTWINDOW_H
