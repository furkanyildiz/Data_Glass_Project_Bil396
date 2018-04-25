// mythread.cpp

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include "mythread.h"

QByteArray data1;
QByteArray data2;


MyThread::MyThread(int ID, QObject *parent,QTcpServer *server, int id) :
    QThread(parent),
    tcpServer(server)
{
    this->thread_id = id;
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    qDebug() << socketDescriptor << " Starting thread " << thread_id ;

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




    if(thread_id == 1){
        data1 = recData;
        qDebug() << socketDescriptor << " This message receiving from data glass : " << this->thread_id << data2;
    }else{
        data2 = recData;
        qDebug() << socketDescriptor << " This message receiving from data glass : " << this->thread_id << data1;
    }
    if (thread_id == 2){
        QByteArray sendData;
        sendData.fill(0, 160);
        QString str = "\nThis message sending from server : ";
        sendData.insert(0, str.toLocal8Bit());
        sendData.insert(80,data1);
        sendData.resize(160);

        socket->write(sendData);
    }else{
        QByteArray sendData;
        sendData.fill(0, 160);
        QString str = "\nThis message sending from server : ";
        sendData.insert(0, str.toLocal8Bit());
        sendData.insert(80,data2);
        sendData.resize(160);

        socket->write(sendData);
    }

}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
