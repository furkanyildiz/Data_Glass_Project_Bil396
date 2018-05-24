#include "menu.h"
#include "ui_menu.h"
#include <QListWidgetItem>
#include "mainwindow.h"
#include <iostream>
#include <QMovie>
#include <QPalette>
#include "mythread.h"
#include "gerisayimekrani.h"

using namespace std;

int btn1 = 0;
int btn2 = 0;
Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
//    connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*, int)),
//                this, SLOT(on_listWidget_2_itemClicked(QListWidgetItem*, int)));
    server = new Server(parent,nullptr,this);

    // ilk basta visibilityler false
    ui->arkanoid_button->setVisible(false);
    ui->pong_button->setVisible(false);

    QPalette pal = ui->arkanoid_button->palette();
    pal.setColor(QPalette::Button, QColor(Qt::cyan));
    ui->arkanoid_button->setAutoFillBackground(true);
    ui->arkanoid_button->setPalette(pal);
    ui->arkanoid_button->update();

    QPalette pal2 = ui->pong_button->palette();
    pal2.setColor(QPalette::Button, QColor(Qt::red));
    ui->pong_button->setAutoFillBackground(true);
    ui->pong_button->setPalette(pal2);
    ui->pong_button->update();

    // baslangic ekrani
    QMovie *movie = new QMovie(":/Images/pongbaslangic.gif");
    movie->setScaledSize(QSize(430,300));
    ui->pongbaslangic->setMovie(movie);
    movie->start();

    ui->pongbaslangic->setGeometry(10, 10, 380, 250);
    ui->pongbaslangic->setAlignment(Qt::AlignCenter);

}

Menu::~Menu()
{
    delete ui;
}


void Menu::updateGame(int playerNumber){
    if(playerNumber == 1){
//        ui->listWidget_2->addItem("ARKANOID");
//        ui->listWidget->addItem("Glass 1");
        ui->gozluk_no_label->setText("1 gozluk baglandi");
        ui->arkanoid_button->setVisible(true);
    }else if(playerNumber == 2){
//        ui->listWidget_2->addItem("PONG");
//        ui->listWidget->addItem("Glass 2");
        ui->gozluk_no_label->setText("2 gozluk baglandi");
        ui->pong_button->setVisible(true);
    }
}



void Menu::on_arkanoid_button_clicked()
{
    countdown = new GeriSayimEkrani(NULL);
    countdown->show();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(arkanoid_stop_screen()));
    timer->start(3000);

}

void Menu::arkanoid_stop_screen(){
    countdown->stopscreen();
    timer->stop();
    this->setVisible(false);
    cout << "ARKANOID" << endl;
    QWidget *p1 = NULL;
    MainWindow *w = new MainWindow(p1,2);
    w->setWindowTitle("Arkanoid");
    server->mainWindow = w;
    w->show();
    this->close();
}

void Menu::on_pong_button_clicked()
{
    countdown = new GeriSayimEkrani(NULL);
    countdown->show();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(pong_stop_screen()));
    timer->start(3000);
}

void Menu::pong_stop_screen(){
    countdown->stopscreen();
    timer->stop();
    this->setVisible(false);

    cout << "PONG" << endl;
    MainWindow *w = new MainWindow;
    w->setWindowTitle("Pong");
    server->mainWindow = w;
    w->show();
    this->close();
}
