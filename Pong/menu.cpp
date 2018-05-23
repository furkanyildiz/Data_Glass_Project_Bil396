#include "menu.h"
#include "ui_menu.h"
#include <QListWidgetItem>
#include "mainwindow.h"
#include <iostream>
#include "mythread.h"

using namespace std;

int btn1 = 0;
int btn2 = 0;
Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*, int)),
                this, SLOT(on_listWidget_2_itemClicked(QListWidgetItem*, int)));
    server = new Server(parent,nullptr,this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    ui->listWidget_2->hide();
    ui->listWidget->show();
}

void Menu::on_pushButton_2_clicked()
{
    ui->listWidget->hide();
    ui->listWidget_2->show();
}

void Menu::updateGame(int playerNumber){
    if(playerNumber == 1){
        ui->listWidget_2->addItem("ARKANOID");
        ui->listWidget->addItem("Glass 1");
    }else if(playerNumber == 2){
        ui->listWidget_2->addItem("PONG");
        ui->listWidget->addItem("Glass 2");
    }
}

void Menu::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    if(ui->listWidget_2->item(1) == item) {
        cout << "PONG" << endl;
        MainWindow *w = new MainWindow;
        w->setWindowTitle("Pong");
        server->mainWindow = w;
        w->show();
        this->close();

    }else if(ui->listWidget_2->item(0) == item){
        cout << "ARKANOID" << endl;
        QWidget *p1 = NULL;
        MainWindow *w = new MainWindow(p1,2);
        w->setWindowTitle("Arkanoid");
        server->mainWindow = w;
        w->show();
        this->close();
    }
}
