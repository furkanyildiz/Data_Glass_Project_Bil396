#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QDebug>
#include <QBluetoothSocket>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QBluetoothSocket *socket,int id,QBluetoothSocket* secondSocket);
    void run();
    int thread_id = 0;

public slots:
    void readWrite();
    void disconnected();

public slots:

private:
    QBluetoothSocket *socket;
    QBluetoothSocket* secondSocket;
};

#endif // MYTHREAD_H
