//
// Created by 残梦 on 2025/8/1.
//

#ifndef YUMELINEEDIT_H
#define YUMELINEEDIT_H
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include<QPainter>
#include "logic/Global/global.h"
#include <QRegularExpression>
#include<QRegularExpressionValidator>
class YumeLineEdit:public QWidget
{
public:
    [[nodiscard]] QHBoxLayout * main_layout() const
    {
        return _main_layout;
    }

    [[nodiscard]] QLineEdit * line_edit() const
    {
        return _lineEdit;
    }

private:
    Q_OBJECT

public:
    YumeLineEdit(QWidget* parent=nullptr);
    ~YumeLineEdit();

    void setText(const QString& text);
    void loadPixmap(const QString& path);
    void setMode(LineEditMode mode);
    QString currentText();

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QHBoxLayout *_main_layout=nullptr;
    QLineEdit *_lineEdit=nullptr;
    QLabel *_ico=nullptr;
    QPixmap _image;
    QRegularExpression regx;
    QValidator *validator=nullptr;
};



#endif //YUMELINEEDIT_H
