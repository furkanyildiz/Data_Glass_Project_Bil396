#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "gameplay.h"

#define SCREEN_RATIO 4

//These struct between raspberry and server.
typedef struct informations
{
    uint16_t gyro;
    uint16_t topx;
    uint16_t topy;
}informations;

//server ile gameplay arasındaki struct.
struct shared_values{
    int game_mode; //oyun pongsa 1, arkonoid ise 0
    int connected_glasses_count;
    int gyro1;
    int gyro2;
    int mainBallX; //Oyundaki topun koordinatı
    int mainBallY; //Oyundaki topun koordinatı
    int second_ballX; //Oyuna ikinci top dahil olduğunda onun koordinatı
    int second_ballY; //Oyuna ikinci top dahil olduğunda onun koordinatı
    int square_X; //Oyunda gezen karenin koordinatı
    int square_Y; //Oyunda gezen karenin koordinatı
    int item_X;  //İkinci topun oyuna dahil olması için köşelerde çıkan çizginin koordinatı
    int item_Y;  //İkinci topun oyuna dahil olması için köşelerde çıkan çizginin koordinatı
    int flag_top2; //top2 varsa 1 yoksa 0
    int flag_token;
    int flag_block;
    int arkanoid_block_x[8]; // arkanoidde 8 block var her birinin x koordinati
    int arkanoid_block_y[8]; // arkanoidde 8 block var her birinin y koordinati
};

class MyThread : public QThread
{
    Q_OBJECT

    static struct shared_values shared;

public:
    friend Gameplay;


    explicit MyThread(int iID, int thread_id, QObject *parent = 0,QTcpServer *server=0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void discError();

public slots:
    void readWrite();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    int socketDescriptor;
    QTcpServer *tcpServer = nullptr;
    informations infos;
    int thread_id;
    std::string send_string;
    void Pong_mode();

};

#endif // MYTHREAD_H
