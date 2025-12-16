#include "mainwindow.h"

#include <QApplication>
#include <windows.h>

#include "yumewindow.h"
#include "ui/Add/SelectWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(320,445);
    w.show();


    YumeWindow c;
    c.show();

    QObject::connect(&w,&MainWindow::open_yumewindow,&c,&YumeWindow::SlotOpen);

    return a.exec();
}
