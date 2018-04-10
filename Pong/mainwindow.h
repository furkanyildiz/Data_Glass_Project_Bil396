#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
class Gameplay;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT // bu macro meta-obje içeren tüm classlarda bulunmalı

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addScore(int count);

private:
    Ui::MainWindow *ui;
    Gameplay *iLoop;
    int iScore;
    std::string str;
};

#endif // MAINWINDOW_H
