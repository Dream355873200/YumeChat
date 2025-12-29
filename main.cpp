#include "mainwindow.h"

#include <QApplication>
#include <windows.h>

#include "yumewindow.h"
#include "ui/Add/SelectWindow.h"
#include "ui/Add/VerifyMessageWidget.h"
#include "ui/Custom/SplitButton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    std::shared_ptr<YumeWindow> c=nullptr;

    MainWindow w(nullptr,c);
    w.setFixedSize(320,445);
    w.show();


    YumeWindow e;
    e.show();

    SplitButton sp;
    sp.show();




    return a.exec();
}
