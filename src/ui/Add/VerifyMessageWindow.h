//
// Created by 残梦 on 2025/12/20.
//

#ifndef VERIFYMESSAGEWINDOW_H
#define VERIFYMESSAGEWINDOW_H
#include "../../../framelesswidget.h"
#include "logic/Global/global.h"
#include "ui/Custom/SmoothListWidget.h"
#include "ui/Custom/YumeTitleBar.h"
#include<QJsonArray>

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

        painter.setBrush(QColor::fromString("#F2F2F2"));
        painter.setPen(Qt::NoPen);

        painter.drawRoundedRect(this->rect(),6,6);
    }

private:
    YumeTitleBar* _title_bar;
    QVBoxLayout* _main_layout;
    QHBoxLayout* _h_layout;
    YumeLabel* _title;
    YumeLabel* _delete;
    SmoothListWidget* _list;

private slots:
    void process_delete_slots();
    void process_json(const ReqId &req_id, const QByteArray &res, const ErrorCodes &error_codes);
};



#endif //VERIFYMESSAGEWINDOW_H
