#include "mainwindow.h"

#include <QApplication>

#include "yumewindow.h"
#include "ui/Custom/YumeButton.h"
#include "ui/Custom/YumeLabel.h"
#include "ui/Custom/YumeLineEdit.h"

#include "src/ui/login/login_dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setFixedSize(320,445);
    w.show();

    YumeWindow c;
    c.resize(1200,800);
    c.show();

    return a.exec();
}
