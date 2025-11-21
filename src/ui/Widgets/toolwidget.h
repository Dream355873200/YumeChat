//
// Created by 残梦 on 2025/8/29.
//

#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QVBoxLayout>
#include <QWidget>

#include "ui/Custom/YumeLabel.h"
#include<QPainter>

#include "ui/Custom/YumeButton.h"

class ToolWidget : public QWidget
{
public:
    [[nodiscard]] YumeButton * message() const
    {
        return _message;
    }

    [[nodiscard]] YumeButton * friends() const
    {
        return _friends;
    }

private:
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = nullptr);

    ~ToolWidget() override;

    void update_icon_status();
    void on_button_clicked(YumeButton *on_clicked_button);

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(QColor(128, 128, 128, 32), 1));
        painter.drawLine(this->rect().topRight(), this->rect().bottomRight());
        // 获取需要重绘的区域
        QRegion region = event->region();
        if (region.isEmpty()) return;

        for (YumeButton *button: _buttons)
        {
            if (button->is_selected())
            {
                QRect buttonRect = button->geometry();
                if (region.intersects(buttonRect))
                {
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(220, 220, 220));
                    painter.drawRoundedRect(buttonRect, 10, 10);
                }
            }
        }
    }

private:
    QVBoxLayout *_main_layout;
    YumeButton *_message;
    YumeButton *_friends;
    std::vector<YumeButton *> _buttons;

private slots:

};


#endif //TOOLWIDGET_H
