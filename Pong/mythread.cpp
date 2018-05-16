// mythread.cpp

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include "mythread.h"


QByteArray data1;
QByteArray data2;
int MyThread::gyro1 = 30;
int MyThread::gyro2 = 30;
int MyThread::ballX = 30;
int MyThread::ballY = 60;


int MyThread::getBallX()
{
    return ballX;
}

void MyThread::setBallX(int value)
{
    ballX = value;
}

int MyThread::getBallY()
{
    return ballY;
}

void MyThread::setBallY(int value)
{
    ballY = value;
}

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
//    std::printf(" This message receiving from data glass : %d \n" , std::atoi(recData.data()));
    gyro1 = std::atoi(recData.data());

    QByteArray sendData;
    sendData.fill(0, 160);
    QString str = "This message sending from server : " + recData;
    /*
    sendData.insert(0, str.toLocal8Bit());
    sendData.insert(80,recData);
    sendData.resize(160);
    */
    sendData.insert(0,str.toLocal8Bit());

//    socket->write(sendData);

    QString sendMessage = "1234;56;789;0;12";
    QByteArray sendByte = sendMessage.toUtf8() ;
    socket->write(sendByte);


}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
