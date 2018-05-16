#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "gameplay.h"


#define SCREEN_RATIO 2

typedef struct informations
{
    u_int16_t gyro;
    u_int16_t topx;
    u_int16_t topy;
}informations;

class MyThread : public QThread
{
    Q_OBJECT

static int gyro1;
static int gyro2;
static int ballX;
static int ballY;

public:
    friend Gameplay;
    int thread_id = 0;
    informations infos;
    explicit MyThread(int iID, QObject *parent = 0,QTcpServer *server=0);
    void run();
    static int getGyro1() {return gyro1;}
    static int getGyro2() {return gyro2;}    
    static int getBallX();
    static void setBallX(int value);
    static int getBallY();
    static void setBallY(int value);

public slots:
    void readWrite();
    void disconnected();

signals:

private:
    QTcpSocket *socket;
    int socketDescriptor;
    QTcpServer *tcpServer = nullptr;
};

#endif // MYTHREAD_H
