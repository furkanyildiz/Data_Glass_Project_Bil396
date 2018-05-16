#include <QApplication>
#include "mainwindow.h"
#include "menu.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;
    Menu menu;
    //w.setWindowState(Qt::WindowMaximized);
    menu.setWindowTitle("Main menu");
    //w.show();
    menu.show();

    return a.exec();
}
