//
// Created by 残梦 on 2025/8/1.
//

#ifndef YUMEBUTTON_H
#define YUMEBUTTON_H
#include <qabstractbutton.h>
#include <QGraphicsColorizeEffect>
#include <QLabel>

#include <QWidget>
#include<QPalette>
#include<QPainter>
#include <QVBoxLayout>
#include<QMouseEvent>

#include "YumeLabel.h"

class YumeButton:public QAbstractButton
{
public:
    [[nodiscard]] QHBoxLayout * main_layout() const
    {
        return _main_layout;
    }

    [[nodiscard]] YumeLabel * label() const
    {
        return _label;
    }

    void set_effect_rate(float effect_rate)
    {
        this->effect_rate = effect_rate;
    }

    [[nodiscard]] bool is_selected() const
    {
        return isSelected;
    }

    void set_is_selected(bool is_selected)
    {
        isSelected = is_selected;
    }

    [[nodiscard]] bool is_hovered() const
    {
        return isHovered;
    }

    void set_is_hovered(bool is_hovered)
    {
        isHovered = is_hovered;
    }

    [[nodiscard]] QString is_selected_icon() const
    {
        return _is_selected_icon;
    }

    void set_is_selected_icon(const QString &is_selected_icon)
    {
        _is_selected_icon = is_selected_icon;
    }

    [[nodiscard]] QString no_selected_icon() const
    {
        return _no_selected_icon;
    }

    void set_no_selected_icon(const QString &no_selected_icon)
    {
        _no_selected_icon = no_selected_icon;
    }

private:
    Q_OBJECT

public:
    YumeButton(QWidget* parent=nullptr);
    ~YumeButton();
    void setText(const QString& text);
    void setIcon(const QString& file);
    void setHoverColor(const QColor& color);
    void setNormalColor(const QColor& color);
protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    QColor hoverColor=QColor::fromString("#008DEB");
    QColor normalColor=QColor::fromString("#0099FF");
    QString _is_selected_icon;
    QString _no_selected_icon;
    float effect_rate=0.0;
    bool isHovered=false;
    bool isSelected=false;

    QTimer* _timer;
    unsigned int _is_clicked=0;
private:
    QHBoxLayout* _main_layout=nullptr;
    YumeLabel* _label=nullptr;
    QGraphicsColorizeEffect *effect;


private slots:
    void double_clicked_timer();

    signals:
    void double_click();
};



#endif //YUMEBUTTON_H
