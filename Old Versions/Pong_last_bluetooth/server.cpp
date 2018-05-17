#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include <server.h>
#include <mainwindow.h>
#include <mythread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QThread>
Server::Server(QWidget *parent, MainWindow *mWindow)
    : QDialog(parent)
    , mainWindow(mWindow)
{
    thread_id++;
    MyThread *thread2 = new MyThread("98:D3:32:10:7D:B0",thread_id);
    thread_id++;
    thread2->start();
    QThread::sleep(5);
    MyThread *thread = new MyThread("00:15:83:35:94:CA",thread_id);
    thread->start();

}

void Server::sessionOpened()
{

}

void Server::readWrite()
{

}
