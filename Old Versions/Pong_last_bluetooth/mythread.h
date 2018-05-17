#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QDebug>
#include <QBluetoothSocket>
#include "gameplay.h"
#include <QBluetoothServer>

#define SCREEN_RATIO 4

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
    explicit MyThread(QString bluetoothmac,int id);
    void run();
    int thread_id = 0;
    static int getGyro1() {return gyro1;}
    static int getGyro2() {return gyro2;}
    informations infos;
    static int getBallX();
    static void setBallX(int value);

    static int getBallY();
    static void setBallY(int value);

public slots:
    void readWrite();
    void disconnected();
    void clientConnected();

signals:
    void clientConnected(const QString &name);

private:
    QBluetoothSocket *socket;
    QBluetoothServer *rfcommServer;
    QString bluetoothmac;
};

#endif // MYTHREAD_H
