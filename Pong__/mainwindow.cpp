#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "gameplay.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>
#include <QTimer>
#include <server.h>

MainWindow::MainWindow(QWidget *parent,int game_mode) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    P1iScore ( 0 ),
    P2iScore ( 0 )
{
    g_mode=game_mode;
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsRectItem *p1 = new QGraphicsRectItem(0, 0, 30, 5);
    p1->setBrush(QBrush(Qt::blue));

    QGraphicsRectItem *p2 = new QGraphicsRectItem(0, 0, 60, 5);
    p2->setBrush(QBrush(Qt::green));

    QGraphicsEllipseItem *ball = new QGraphicsEllipseItem(0, 0, 4, 4);
    ball->setBrush(QBrush(Qt::magenta));

    QGraphicsRectItem *token= new QGraphicsRectItem(0, 0, 5, 5);
    token->setBrush(QBrush(Qt::black));

    QGraphicsRectItem *innerPanel= new QGraphicsRectItem(0,0,128,256);//oyunun sınırlarını gösteren panel
    innerPanel->setBrush(QBrush(Qt::yellow));
    scene->addItem(innerPanel);
    ui->boardView->setScene(scene);


    if(g_mode==1)
    iLoop = new Gameplay(*scene, p1, p2, ball,g_mode, token, this); // GamePlay objesi oluşturuldu. Oyunu bu yönetir.
    else{
       iLoop = new Gameplay(*scene, p1, p2, ball,g_mode, token, this);
    }
    QSize m(scene->sceneRect().size().width()+5, scene->sceneRect().size().height()+5);

    ui->boardView->setMinimumSize(m);

    resize(m);
    ui->boardView->installEventFilter(iLoop);

    QObject::connect(iLoop, SIGNAL(goal(int)), this, SLOT(addScore(int)));
    qDebug() << "denug3";
    server = new Server(parent,this);
    qDebug() << "denug";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addScore(int count)
{
    if(count == 1){
        P1iScore++;
        ui->playerScore->display(P1iScore);
        ui->playerScore->setPalette(Qt::blue);
        ui->showGoal->setText("                 GOAL! Player1 Scored");
        ui->showGoal->setVisible(true);
    }
    else{
        P2iScore++;
        ui->aiScore->display(P2iScore);
        ui->aiScore->setPalette(Qt::green);
        ui->showGoal->setText("                  GOAL! Player2 Scored");
        ui->showGoal->setVisible(true);
    }

    if(P1iScore > P2iScore){
        ui->status->setText("P1 leads the game");
    }else if(P1iScore == P2iScore){
        ui->status->setText("Draw");
    }else{
        ui->status->setText("P2 leads the game");
    }
    QTimer::singleShot(500, ui->showGoal, &QLabel::hide);
}


void MainWindow::addPlayer(int count){
    std::string s = " The player who participated in the game : Player"  + std::to_string(count);
    ui->labelPlayers->setText(s.c_str());
}
