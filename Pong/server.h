#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QMainWindow>
#include <mainwindow.h>

#define PORTNUMBER 8081
#define IPADDRESS "192.168.91.1"

class QLabel;
class QTcpServer;
class QNetworkSession;

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr,MainWindow *mWindow = nullptr);

private slots:
    void sessionOpened();
    void readWrite();

private:
    QTcpServer *tcpServer = nullptr;
    QNetworkSession *networkSession = nullptr;
    MainWindow *mainWindow;
    int playerNumber;
    int thread_id = 0;
    QString revData;
};

#endif
