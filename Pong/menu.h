#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QListWidgetItem>
#include <server.h>
#include "gerisayimekrani.h"
class Server;
namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    void updateGame(int playerNumber);

private slots:
    void arkanoid_stop_screen();
    void pong_stop_screen();
    void on_arkanoid_button_clicked();


    void on_pong_button_clicked();

private:
    QTimer *timer;
    GeriSayimEkrani *countdown;
    Ui::Menu *ui;
    Server *server;
};

#endif // MENU_H
