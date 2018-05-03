#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QMainWindow>
#include <mainwindow.h>
#include <QBluetoothSocket>

#define PORTNUMBER 1357
#define IPADDRESS "192.168.204.1"

class QLabel;
class QTcpServer;
class QNetworkSession;

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr,MainWindow *mWindow = nullptr);

private:
    QBluetoothSocket *socket,*socket2;
    MainWindow *mainWindow;
    int playerNumber;
    int thread_id=0;
};

#endif
