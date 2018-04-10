#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
