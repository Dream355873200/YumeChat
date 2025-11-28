//
// Created by 残梦 on 2025/8/28.
//

#ifndef YUMEWINDOW_H
#define YUMEWINDOW_H


#include <QStackedWidget>

#include "framelessmainwindow.h"
#include "ui/Custom/YumeTitleBar.h"
#include "ui/Widgets/ChatArea.h"
#include "ui/Widgets/ChatInput.h"
#include "ui/Widgets/FriendPage.h"
#include "ui/Widgets/messagelist.h"
#include "ui/Widgets/toolwidget.h"


class MessagePage;

class YumeWindow : public FramelessMainWindow
{
    Q_OBJECT

public:
    explicit YumeWindow(QWidget *parent = nullptr);

    ~YumeWindow() override;

    bool eventFilter(QObject *watched, QEvent *event);

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
    QStackedWidget* stacked_widget;
    ChatArea* _chat_area;
    MessagePage* _message_page;
    FriendPage* _friend_page;

public slots:
    void SlotOpen();

public slots:
    bool isClickInBlankArea(const QPoint &pos);

    void SlotClose();
    void SlotMessage();
    void SlotFriends();



};


#endif //YUMEWINDOW_H
