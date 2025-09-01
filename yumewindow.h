//
// Created by 残梦 on 2025/8/28.
//

#ifndef YUMEWINDOW_H
#define YUMEWINDOW_H


#include <QStackedWidget>

#include "framelessmainwindow.h"
#include "ui/Custom/YumeTitleBar.h"
#include "ui/Widgets/messagelist.h"
#include "ui/Widgets/toolwidget.h"


class YumeWindow : public FramelessMainWindow
{
    Q_OBJECT

public:
    explicit YumeWindow(QWidget *parent = nullptr);

    ~YumeWindow() override;
protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);

        // 垂直渐变背景
        QLinearGradient liner(0, 0, 0, height());
        liner.setColorAt(0.0, QColor("#ffffff"));
        liner.setColorAt(0.5, QColor("#ffffff"));

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(liner);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(this->rect(), 6, 6);
    }
private:
    YumeTitleBar *_titlebar=nullptr;
    QVBoxLayout *_mainlayout=nullptr;
    QHBoxLayout* _h_layout=nullptr;
    ToolWidget *_toolwidget=nullptr;
    MessageList* _list;
    QStackedWidget stacked_widget;

private slots:
    void SlotClose();
    void SlotMessage();
    void SlotFriends();
};


#endif //YUMEWINDOW_H
