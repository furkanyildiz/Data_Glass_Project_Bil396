#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include <server.h>
#include <mainwindow.h>
#include <mythread.h>

Server::Server(QWidget *parent, MainWindow *mWindow)
    : QDialog(parent)
    , mainWindow(mWindow)
{
    QBluetoothSocket *socket,*socket2;

    //socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    static const QString serviceUuid2(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));


    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(QBluetoothAddress("00:15:83:35:94:CA"), QBluetoothUuid(serviceUuid2), QIODevice::ReadWrite);

    MyThread *thread = new MyThread(socket,++thread_id,socket2);
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();

    socket2 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket2->connectToService(QBluetoothAddress("98:D3:32:10:7D:B0"), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);

    MyThread *thread2 = new MyThread(socket2,++thread_id,socket);
    QObject::connect(thread2, SIGNAL(finished()), thread2, SLOT(deleteLater()));

    thread2->start();

}

void Server::sessionOpened()
{

}

void Server::readWrite()
{

}
