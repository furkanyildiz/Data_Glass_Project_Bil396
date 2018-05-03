#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QDebug>
#include <QBluetoothSocket>
#include "gameplay.h"

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




public:
    friend Gameplay;
    explicit MyThread(QBluetoothSocket *socket,int id,QBluetoothSocket* secondSocket);
    void run();
    int thread_id = 0;
    static int getGyro1() {return gyro1;}
    static int getGyro2() {return gyro2;}
    informations infos;
public slots:
    void readWrite();
    void disconnected();

private:
    QBluetoothSocket *socket;
    QBluetoothSocket* secondSocket;
};

#endif // MYTHREAD_H
