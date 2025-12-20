//
// Created by 残梦 on 2025/12/20.
//

#ifndef VERIFYMESSAGEWINDOW_H
#define VERIFYMESSAGEWINDOW_H
#include "../../../framelesswidget.h"
#include "logic/Global/global.h"
#include "ui/Custom/SmoothListWidget.h"
#include "ui/Custom/YumeTitleBar.h"


class VerifyMessageWindow:public FramelessWidget
{
    Q_OBJECT
public:
    VerifyMessageWindow(QWidget* parent=nullptr);
    ~VerifyMessageWindow();
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(this->rect(),6,6);
    }

private:
    YumeTitleBar* _title_bar;
    QVBoxLayout* _main_layout;
    SmoothListWidget* _list;

};



#endif //VERIFYMESSAGEWINDOW_H
