#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "src/ui/login/login_dialog.h"
#include "src/ui/Register/registerdialog.h"
#include <QStackedWidget>
#include"framelessmainwindow.h"
#include "yumewindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public FramelessMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent,std::shared_ptr<YumeWindow> yume_window);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);

        // 垂直渐变背景
        QLinearGradient liner(0, 0, 0, height());
        liner.setColorAt(0.0, QColor("#62A5FA"));
        liner.setColorAt(0.5, QColor("#ffffff"));

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(liner);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(this->rect(), 6, 6);
    }
private:
    Ui::MainWindow *ui;
    LoginDialog *login_dialog;
    RegisterDialog *reg_dialog;
    QStackedWidget *stack_widget;
    std::shared_ptr<YumeWindow> _yume_window;
public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();
    void SlotClose();
    void SlotToYumeWindow();

};
#endif // MAINWINDOW_H
