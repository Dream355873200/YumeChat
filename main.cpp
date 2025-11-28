#include "mainwindow.h"

#include <QApplication>
#include <windows.h>

#include "yumewindow.h"
#include "ui/Custom/YumeButton.h"
#include "ui/Custom/YumeLabel.h"
#include "ui/Custom/YumeLineEdit.h"

#include "src/ui/login/login_dialog.h"
#include "ui/Custom/YumeBubble.h"
#include "ui/Widgets/ChatArea.h"
#include "ui/Widgets/ChatInput.h"
#include "ui/Widgets/FriendWidget.h"
#include "ui/Widgets/MessageItem.h"
#include "ui/Widgets/SearchWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(320,445);
    w.show();


    YumeWindow c;
    c.show();
    QObject::connect(&w,&MainWindow::open_yumewindow,&c,&YumeWindow::SlotOpen);


    MessageItem aaaa;
    aaaa.set_text("bbbbbbbbbbbbbbbbbbbbbbbbb \n123333333333333333333333333333333333333333333333\n12333333333333333333333333");
    aaaa.set_mode(ItemMode::Self);
    aaaa.show();

    YumeBubble bubble;
    bubble.set_text("bbbbbbbbbbbbbbbbbbbbbbbbb \n123333333333333333333333333333333333333333333333\n12333333333333333333333333");
    bubble.show();

    return a.exec();
}
