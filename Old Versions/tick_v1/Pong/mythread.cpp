// mythread.cpp

#include <QtWidgets>

#include <QtCore>
#include <iostream>
#include<QtBluetooth>
#include "mythread.h"


QByteArray data1;
QByteArray data2;
int MyThread::gyro1 = 100;
int MyThread::gyro2 = 100;


MyThread::MyThread(QBluetoothSocket *socket,int id,QBluetoothSocket* secondSocket)
{
    this->thread_id = id;
    this->socket = socket;
    this->secondSocket = secondSocket;
}

void MyThread::run()
{
    qDebug() << "THREAD RUNNING";/*
    int a= rand()%89+10;
    int b= rand()%89+10;
    int c= rand()%890+100;
    int d= rand()%89+10;
    std::string f = std::to_string(a);*/
    sleep(5);
    //while(1){

        connect(socket, SIGNAL(readyRead()), this, SLOT(readWrite()),Qt::DirectConnection);
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

        //std::cout << f.c_str() << std::endl;
        //socket->write(f.c_str());
        //socket->write(std::to_string(a)+","+std::to_string(b)+","+std::to_string(c)+","+std::to_string(d));
        //sleep(1);

        /*
        if(socket->isReadable()){
            rec = socket->read(2);
            qDebug() <<  rec;
            rec.clear();
            socket->write("1");
        }*/

    //}
    // make this thread a loop
    exec();
}
void MyThread::readWrite()
{

    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender()); //silincede calısıyor.
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine().trimmed();
        qDebug() << " This message receiving from data glass : " << this->thread_id << line;
        //secondSocket->write(line);
        if (thread_id == 1){
            gyro1 = line.toInt();
            infos.gyro = gyro2;

        }
        if (thread_id == 2){
            gyro2 = line.toInt();
            infos.gyro = gyro1;
        }
        infos.topx = 32;
        infos.topy = 64;

        socket->write(infos);

    }


    // QByteArray text = message.toUtf8() + '\n';  // string to Qbyte array

}

void MyThread::disconnected()
{

}
