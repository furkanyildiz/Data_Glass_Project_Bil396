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
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_10);

    out << "This message sending from data glass.";


    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);

    block.clear();

    while((clientConnection->state() == QTcpSocket::ConnectedState)){
        clientConnection->waitForReadyRead();
        block.clear();
        block = clientConnection->readAll();
        qDebug() << " Client message is : " << block.data();

    }
    clientConnection->disconnectFromHost();

    qDebug() << "Client disconnected";

    // make this thread a loop
    //exec();
}

void MyThread::readyRead()
{
    qDebug()<<"READY READ";
    QByteArray Data = socket->readAll();

    qDebug() << socketDescriptor << " Data in: " << Data;

    socket->write(Data);
}

void MyThread::disconnected()
{

    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
