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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    P1iScore ( 0 ),
    P2iScore ( 0 )
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    QGraphicsRectItem *p1 = new QGraphicsRectItem(0, 0, 80, 20);
    p1->setBrush(QBrush(Qt::blue));
    QGraphicsRectItem *p2 = new QGraphicsRectItem(0, 0, 80, 20);
    p2->setBrush(QBrush(Qt::green));

    QGraphicsEllipseItem *ball = new QGraphicsEllipseItem(0, 0, 15, 15);
    ball->setBrush(QBrush(Qt::magenta));

    ui->boardView->setScene(scene);

    iLoop = new Gameplay(*scene, p1, p2, ball, this); // GamePlay objesi oluşturuldu. Oyunu bu yönetir.

    QSize m(scene->sceneRect().size().width() + 15, scene->sceneRect().size().height() + 15);

    ui->boardView->setMinimumSize(m);

    resize(minimumSize());
    ui->boardView->installEventFilter(iLoop);

    QObject::connect(iLoop, SIGNAL(goal(int)), this, SLOT(addScore(int)));
    server = new Server(parent,this);

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
        ui->showGoal->setText("                 GOAL! Player Scored");
        ui->showGoal->setVisible(true);
    }
    else{
        P2iScore++;
        ui->aiScore->display(P2iScore);
        ui->aiScore->setPalette(Qt::green);
        ui->showGoal->setText("                  GOAL! Ai Scored");
        ui->showGoal->setVisible(true);
    }

    if(P1iScore > P2iScore){
        ui->status->setText("P1 leads the game");
    }else if(P1iScore == P2iScore){
        ui->status->setText("Draw");
    }else{
        ui->status->setText("AI leads the game");
    }
    QTimer::singleShot(500, ui->showGoal, &QLabel::hide);
}


void MainWindow::addPlayer(int count){
    std::string s = " The player who participated in the game : Player"  + std::to_string(count);
    ui->labelPlayers->setText(s.c_str());
}
