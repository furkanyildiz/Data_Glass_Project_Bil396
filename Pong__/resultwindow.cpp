#include "resultwindow.h"
#include "ui_resultwindow.h"
#include <QGraphicsScene>
#include "constants.h"
#include <QGraphicsPixmapItem>
#include <iostream>

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
    if(player_no == 1 && game_mode == 1)
        player_win_photo = new QPixmap(":/Images/player1wins.png");
    else if(player_no == 1 && game_mode == 1)
        player_win_photo = new QPixmap(":/Images/player2wins.png");
    else if(player_no == 1 && game_mode == 2)
        player_win_photo = new QPixmap(":/Images/lose.png");
    else if(player_no == 2 && game_mode == 2)
        player_win_photo = new QPixmap(":/Images/win.png");

    QPixmap scaledGameBG = player_win_photo->scaled(QSize(Constant::GAME_AREA_WIDTH/4, Constant::GAME_AREA_HEIGHT/4));
    QGraphicsPixmapItem *area = new QGraphicsPixmapItem();
    area->setPixmap(scaledGameBG);
    scene->addItem(area);

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
