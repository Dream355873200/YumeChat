//
// Created by 残梦 on 2025/8/2.
//

#ifndef YUMETITLEBAR_H
#define YUMETITLEBAR_H
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QGuiApplication>
#include <QWindow>
#include <QMouseEvent>
#include <QGraphicsColorizeEffect>
#include "YumeLabel.h"

class YumeTitleBar:public QWidget
{
public:
    [[nodiscard]] YumeLabel * x() const
    {
        return _x;
    }

    [[nodiscard]] QHBoxLayout * main_layout() const
    {
        return _main_layout;
    }

private:
    Q_OBJECT
    friend class MainWindow;
    friend class YumeWindow;
public:
    YumeTitleBar(QWidget* parent=nullptr);
    ~YumeTitleBar();
    QHBoxLayout* GetMainLayout();
    void setIconEffect(const float normal_rate,const float hover_rate,const QColor& effect_color);


protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    QGraphicsColorizeEffect *effect;
    QHBoxLayout *_main_layout;
    QPoint m_windowPosition;
    QPoint m_dragStartPosition;
    YumeLabel* _x;
    float _normal_rate=0.8;
    float _hover_rate=1.0;
    QColor _effect_color=Qt::white;

};



#endif //YUMETITLEBAR_H
