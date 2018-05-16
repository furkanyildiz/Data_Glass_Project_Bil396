#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

class Gameplay;
class Server;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT // bu macro meta-obje içeren tüm classlarda bulunmalı

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addPlayer(int count);

private slots:
    void addScore(int count);

private:
    Ui::MainWindow *ui;
    Gameplay *iLoop;
    int iScore;
    int P1iScore;
    int P2iScore;
    std::string str;
    Server *server;
};

#endif // MAINWINDOW_H
