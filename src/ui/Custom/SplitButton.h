//
// Created by 残梦 on 2025/12/23.
//

#ifndef SPLITBUTTON_H
#define SPLITBUTTON_H
#include <QToolButton>
#include <QMenu>
#include <qgraphicseffect.h>
#include <QEvent>
#include <QMouseEvent>
#include "YumeLabel.h"
#include <QHBoxLayout>
#include<QPainterPath>

#include "YumeMenu.h"

class SplitButton:public QAbstractButton
{
public:
    [[nodiscard]] YumeMenu * menu() const
    {
        return _menu;
    }

    SplitButton(QWidget* parent=nullptr);
    ~SplitButton();
    void setText(const QString& text);
    void setHoverColor(const QColor& color);
    void setNormalColor(const QColor& color);
    void addMenuButton(const QString& text,const std::function<void()>& function);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void drawArrow(QPainter *painter);

    bool eventFilter(QObject *watched, QEvent *event) override;

private:

    void showMenu();

    QColor hoverColor=QColor::fromString("#008DEB");
    QColor normalColor=QColor::fromString("#0099FF");
    bool isHovered=false;
    bool isPressed=false;
    QHBoxLayout* _main_layout=nullptr;
    YumeLabel* _label=nullptr;


    int _menuWidth = 30;
    bool inMenu;
    YumeMenu* _menu;
};



#endif //SPLITBUTTON_H
