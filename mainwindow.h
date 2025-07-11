#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/ui/login/login_dialog.h"
#include "src/ui/Register/registerdialog.h"
#include <QStackedWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginDialog *login_dialog;
    RegisterDialog *reg_dialog;
    QStackedWidget *stack_widget;
public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();
};
#endif // MAINWINDOW_H
