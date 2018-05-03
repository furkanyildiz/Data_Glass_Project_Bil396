#include <QApplication>
#include "mainwindow.h"
#include "menu.h"
int main_data;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    Menu menu;
    //w.setWindowState(Qt::WindowMaximized);
    //w.setWindowTitle("Pong");
    //w.show();
    menu.show();

    return a.exec();
}
