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
#include "../../../Message.pb.h"
#include<QJsonArray>

#include "../../../framelesswidget.h"
#include "logic/Global/global.h"
class SelectWindow:public FramelessWidget
{
    Q_OBJECT
public:
    SelectWindow(QWidget* parent=nullptr);
private:
    YumeTitleBar* _title_bar;
    YumeLineEdit* _search;
    YumeButton* _button;

    QVBoxLayout* _main_layout;
    QHBoxLayout* _search_layout;
    SmoothListWidget* _list;

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(this->rect(),6,6);
    }
private slots:
    void select_button_clicked();
    void process_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes);

};



#endif //SELECTWINDOW_H
