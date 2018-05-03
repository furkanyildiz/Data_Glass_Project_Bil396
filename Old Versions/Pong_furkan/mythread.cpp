// mythread.cpp

#include <QtWidgets>

#include <QtCore>
#include <iostream>
#include<QtBluetooth>
#include "mythread.h"


QByteArray data1;
QByteArray data2;
int MyThread::gyro1 = 30;
int MyThread::gyro2 = 30;


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
    QByteArray q_b;/*
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender()); //silincede calısıyor.
    if (!socket)
        return;
*/
    while (socket->canReadLine()) {
        QByteArray line = socket->readLine().trimmed();
        qDebug() << " This message receiving from data glass : " << this->thread_id << line;
        //secondSocket->write(line);
        if (thread_id == 1){
            gyro1 = line.toInt();
            infos.gyro = gyro2;
            qDebug() <<"Sent: "<<infos.gyro;

        }
        if (thread_id == 2){
            gyro2 = line.toInt();
            infos.gyro = gyro1;
        }
        infos.topx = 32;
        infos.topy = 102;
        //line.
        //QByteArray zero;
        //zero.setNum(0);
        //qDebug() <<"Sent: "<<infos.gyro;
        //socket->write(q)

        q_b.setNum(15);

        qDebug() << q_b.at(0) << " " << q_b.at(1);

        if(socket->bytesToWrite()==0 && socket->isWritable()){
            socket->write(q_b);
        }
        //msleep(300);
        /*
        if(socket->bytesToWrite()==0 && socket->isWritable()){
            socket->write("5");
        }*/
        /*
        if(infos.gyro<10){
            socket->write(zero);
        }

        qDebug() <<"Sent: "<<infos.gyro;

        char dens[1024];
        sprintf(dens,"%d",infos.gyro);
        qDebug() <<"dens: "<<dens;

        //socket->write(q_b);
        q_b.setNum(infos.topx);
        if(infos.topx<10){
            socket->write(zero);
        }
        socket->write(dens);
        //socket->write(q_b);
        q_b.setNum(infos.topy);
        if(infos.topy<10){
            socket->write(zero);
        }
        socket->write(q_b);
*/

    }


    // QByteArray text = message.toUtf8() + '\n';  // string to Qbyte array

}

void MyThread::disconnected()
{

}
