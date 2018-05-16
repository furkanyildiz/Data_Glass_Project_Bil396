// mythread.cpp

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include "mythread.h"

MyThread::MyThread(int ID, QObject *parent,QTcpServer *server) :
    QThread(parent),
    tcpServer(server)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    qDebug() << socketDescriptor << " Starting thread";

    socket= tcpServer->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readWrite()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop
    exec();


}

void MyThread::readWrite()
{
    qDebug()<<"READY READ AND WRITE";
    QByteArray recData = socket->readAll();

    qDebug() << socketDescriptor << " This message receiving from data glass : " << recData;

    QByteArray sendData;
    sendData.fill(0, 160);
    QString str = "This message sending from server : ";
    sendData.insert(0, str.toLocal8Bit());
    sendData.insert(80,recData);
    sendData.resize(160);

    socket->write(sendData);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
