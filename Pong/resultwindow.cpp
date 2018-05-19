#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <QGraphicsScene>
#include "constants.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QLabel>
#include <QMovie>

ResultWindow::ResultWindow(QWidget *parent, int player_no, int game_mode) :
    QDialog(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    std::cout << "result window olusturldu" << std::endl;
    //player 1 kazandiysa

    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap* player_win_photo;

    // kazanan oyuncuya gore fotoyu aliyor
    if(player_no == 1 && game_mode == 1){                                   // player1 kazandi
        player_win_photo = new QPixmap(":/Images/p1w.png");
        QPixmap scaledGameBG = player_win_photo->scaled(QSize(375, 245));
        QGraphicsPixmapItem *area = new QGraphicsPixmapItem();
        area->setPixmap(scaledGameBG);
        scene->addItem(area);
    }else if(player_no == 2 && game_mode == 1){                             // player2 kazandi
        player_win_photo = new QPixmap(":/Images/p2w.jpg");
        QPixmap scaledGameBG = player_win_photo->scaled(QSize(375, 245));
        QGraphicsPixmapItem *area = new QGraphicsPixmapItem();
        area->setPixmap(scaledGameBG);
        scene->addItem(area);
    }else if(player_no == 1 && game_mode == 2){                             // arkanoidi kaybetti
        QMovie *movie = new QMovie(":/Images/aglayanyildiz.gif");
        movie->setScaledSize(QSize(430,300));
        QLabel *processLabel = new QLabel(this);
        processLabel->setMovie(movie);
        movie->start();
        processLabel->setGeometry(10, 10, 380, 250);
        processLabel->setAlignment(Qt::AlignCenter);
        scene->addWidget(processLabel);
    }else if(player_no == 2 && game_mode == 2){                             // arkanoidi kazandi
        QMovie *movie = new QMovie(":/Images/gulenyildiz.gif");
        movie->setScaledSize(QSize(430,320));
        QLabel *processLabel = new QLabel(this);
        processLabel->setMovie(movie);
        movie->start();
        processLabel->setGeometry(10, 10, 380, 250);
        processLabel->setAlignment(Qt::AlignCenter);
        scene->addWidget(processLabel);
    }
    ui->winner_view->setScene(scene);
}


ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::on_cancel_clicked()
{
    this->close();
}
