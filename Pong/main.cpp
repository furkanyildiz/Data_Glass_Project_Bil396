#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("Pong");
    w.show();

    return a.exec();
}
