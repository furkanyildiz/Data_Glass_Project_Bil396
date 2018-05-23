#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QListWidgetItem>
#include <server.h>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    //void on_listWidget_2_itemPressed(QListWidgetItem *item);

private:
    Ui::Menu *ui;
    Server *server;
};

#endif // MENU_H
