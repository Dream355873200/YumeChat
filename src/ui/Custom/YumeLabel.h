//
// Created by 残梦 on 2025/8/1.
//

#ifndef YUMELABEL_H
#define YUMELABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>


class YumeLabel:public QLabel
{
public:

private:
    Q_OBJECT

public:
    YumeLabel(QWidget *parent=nullptr);
    void set_text(const QString& text);
    void set_font_size(int size);
    void set_icon(const QString& path);

protected:


private:
    QPixmap _icon;
protected:

    bool eventFilter(QObject *watched, QEvent *event) override;
    signals:
    void clicked();
};



#endif //YUMELABEL_H
