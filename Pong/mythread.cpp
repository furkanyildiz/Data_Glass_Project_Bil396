// mythread.cpp

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <iostream>
#include "mythread.h"
#include "gameplay.h"



shared_values MyThread::shared = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

MyThread::MyThread(int ID, int thread_id, QObject *parent,QTcpServer *server) : QThread(parent),tcpServer(server)
{
    this->socketDescriptor = ID;
    this->thread_id = thread_id;
    this->send_string = "";
    shared.connected_glasses_count++;
    qDebug()<< "Connected glasses: "<<shared.connected_glasses_count;
    qDebug()<< "thread id : "<<thread_id;

}

void MyThread::run()
{
    qDebug() << socketDescriptor << " Starting thread";

    socket= tcpServer->nextPendingConnection();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readWrite()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);
//    connect(socket, SIGNAL(connected()), this, SLOT(readWrite()),Qt::DirectConnection);

    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop
    exec();


}

void MyThread::readWrite()
{


    if (shared.game_mode == 1)
        Pong_mode();

/*
    qDebug()<<"READY READ AND WRITE";


    QByteArray recData = socket->readAll();

    qDebug() << socketDescriptor << " This message receiving from data glass : " << recData;

    QString sendMessage = "1234;56;789;0;12";
    QByteArray sendByte = sendMessage.toUtf8() ;
    socket->write(sendByte);

*/

   // while (socket->canReadLine()) {





    //}


}

void MyThread::Pong_mode(){

    QByteArray line =  socket->readAll();

    qDebug() << " This message receiving from data glass : " << this->thread_id << line;
    QByteArray q_b;

    std::string data = "";
    data = "";
    send_string.clear();

        if (thread_id == 1){

            shared.gyro1 = line.toInt();
            infos.gyro = shared.gyro2;


        }
        if (thread_id == 2){
            shared.gyro2 = line.toInt();
            infos.gyro = shared.gyro1;

        }
        infos.topx = shared.mainBallX / SCREEN_RATIO;
        infos.topy = shared.mainBallY / SCREEN_RATIO;

        if(socket->bytesToWrite()==0 && socket->isWritable()){

            q_b.clear();

            std::string tempp = std::to_string(infos.gyro);
            send_string+=tempp;
            send_string+=";";

            //topx
            tempp = std::to_string(infos.topx);
            send_string+=tempp;
            send_string+=";";

            //topy
            tempp = std::to_string(infos.topy);
            send_string+=tempp;
            send_string+=";";


            //flag top 2
            tempp = std::to_string(shared.flag_top2);
            send_string+=tempp;
            send_string+=";";

            //top2 address
            tempp = std::to_string(shared.second_ballX);
            send_string+=tempp;
            send_string+=";";

            //top2y
            tempp = std::to_string(shared.second_ballY);
            send_string+=tempp;
            send_string+=";";

            //flag of token
            tempp = std::to_string(shared.flag_token);
            send_string+=tempp;
            send_string+=";";

            //token address
            //tokenx
            tempp = std::to_string(shared.item_X);
            send_string+=tempp;
            send_string+=";";

            //tokeny
            tempp = std::to_string(shared.item_Y);
            send_string+=tempp;
            send_string+=";";


            //flag of block
            tempp = std::to_string(shared.flag_block);
            send_string+=tempp;
            send_string+=";";

            //blocks coordinates
            //blockX
            tempp = std::to_string(shared.square_X);
            send_string+=tempp;
            send_string+=";";

            //BlockY
            tempp = std::to_string(shared.square_Y);
            send_string+=tempp;
            send_string+=";";

            //yollama formatına cevir ve yolla

            std::cout << "yollanan string: " <<send_string <<std::endl;
            QString data_to_write = QString::fromStdString(send_string);
            q_b = data_to_write.toUtf8();
            socket->write(q_b);
            //qDebug() << "string:" << data_to_write ;
            //qDebug() << "Sent string as bytes:" << q_b ;

            //qDebug() <<"Sent top x: "<<infos.topx << " top y: " << infos.topy;


        }

}

void MyThread::disconnected()
{
/*    qDebug() << socketDescriptor << " Disconnected";
    qDebug() << "Waiting player Connection";

    QTime dieTime = QTime::currentTime().addSecs(10);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    if(QTime::currentTime() < dieTime){
        qDebug() << "Connection is established again";
    }else{
        qDebug() << "Connection is lost";
        socket->deleteLater();
        exit(0);

    }*/
    qDebug() << "Connection is lost" << thread_id << " ++++";
}
