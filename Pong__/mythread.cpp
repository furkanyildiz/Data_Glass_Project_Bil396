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

MyThread::MyThread(QString bluetoothmac,int id)
{
    this->thread_id = id;
    this->bluetoothmac = bluetoothmac;


}
/*
    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    static const QString serviceUuid2(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));

    socket2 = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket2->connectToService(QBluetoothAddress("98:D3:32:10:7D:B0"), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);



  */
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
/*
    rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(rfcommServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
*/

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(QBluetoothAddress(bluetoothmac), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);



    connect(socket, SIGNAL(readyRead()), this, SLOT(readWrite()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);


    exec();


    /*
   const QBluetoothAddress &localAdapter = QBluetoothAddress();
   bool result = rfcommServer->listen(localAdapter);
   while (!result) {
       connect(rfcommServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
   }
  */
}

void MyThread::clientConnected()
{
    socket = rfcommServer->nextPendingConnection();
    if (!socket)
        return;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readWrite()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

//    clientSockets.append(socket);
    emit clientConnected(socket->peerName());
}


void MyThread::readWrite()
{
    QByteArray q_b;/*
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender()); //silincede calısıyor.
    if (!socket)
        return;
*/
    int i = 0;
    while (socket->canReadLine()) {
        QByteArray line = socket->readLine().trimmed();

        if(i<50)
            qDebug() << " This message receiving from data glass : " << this->thread_id << line;
        i+=1;
        //secondSocket->write(line);
        if (thread_id == 1){
            gyro1 = line.toInt();
            infos.gyro = gyro2;

        }
        if (thread_id == 2){
            gyro2 = line.toInt();
            infos.gyro = gyro1;
        }
        infos.topx = ballX / SCREEN_RATIO;
        infos.topy = ballY / SCREEN_RATIO;
        //line.
        QByteArray zero;
        zero.setNum(0);


        //qDebug() <<"Sent top x: "<<infos.topx << " top y: " << infos.topy;

        if(socket->bytesToWrite()==0 && socket->isWritable()){

            //gyro
            if (infos.gyro <10 )
                socket->write(zero);

            q_b.setNum(infos.gyro);
            socket->write(q_b);

            qDebug() <<"Sent top x: "<<infos.topx << " top y: " << infos.topy;
/*
            //topx
            if(infos.topx <10)
                socket->write(zero);

            q_b.setNum(infos.topx);
            socket->write(q_b);

             //topy
            if(infos.topy <10){
                socket->write(zero);
                socket->write(zero);

            }
            else if(infos.topy <100){
                socket->write(zero);

            }
            q_b.setNum(infos.topy);
            socket->write(q_b);
*/
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
