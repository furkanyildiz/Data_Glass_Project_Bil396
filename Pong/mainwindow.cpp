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
#include "resultwindow.h"
#include <iostream>
#include <QMovie>
#include <QThread>
#include <QTime>

MainWindow::MainWindow(QWidget *parent,int game_mode) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    P1iScore ( 0 ),
    P2iScore ( 0 )
{
    g_mode=game_mode;

    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsRectItem *p1 = new QGraphicsRectItem(0, 0, Constant::PLAYER1_WIDTH*2, Constant::PLAYER1_HEIGHT);
    p1->setBrush(QBrush(Qt::blue));

    QGraphicsRectItem *p2 = new QGraphicsRectItem(0, 0, Constant::PLAYER2_WIDTH*2, Constant::PLAYER2_HEIGHT);
    p2->setBrush(QBrush(Qt::green));

    QGraphicsEllipseItem *ball = new QGraphicsEllipseItem(0, 0, Constant::BALL_RAD*2, Constant::BALL_RAD*2);
    ball->setBrush(QBrush(Qt::magenta));

    QGraphicsEllipseItem *ball2 = new QGraphicsEllipseItem(0, 0, Constant::BALL_RAD, Constant::BALL_RAD);
    ball2->setBrush(QBrush(Qt::cyan));

    QGraphicsRectItem *token = new QGraphicsRectItem(0, 0, 5, 5);
    token->setBrush(QBrush(Qt::black));

    /*QGraphicsRectItem *innerPanel= new QGraphicsRectItem(0,0,128,256);//oyunun sınırlarını gösteren panel
    innerPanel->setBrush(QBrush(Qt::yellow));
    scene->addItem(innerPanel);
    */
    QPixmap* gameBackGround;
    QPixmap* goalBackGround;

    if(g_mode == 1)
        gameBackGround = new QPixmap(":/Images/soccerField.png");
    else
        gameBackGround = new QPixmap(":/Images/darkSpace.jpg");

    goalBackGround = new QPixmap(":/Images/goalscreen.jpg");
    QPixmap scaledGameBG = gameBackGround->scaled(QSize(Constant::GAME_AREA_WIDTH, Constant::GAME_AREA_HEIGHT));
    area = new QGraphicsPixmapItem();
    area->setPixmap(scaledGameBG);


    QPixmap goalscaledGameBG = goalBackGround->scaled(QSize(Constant::GAME_AREA_WIDTH, Constant::GAME_AREA_HEIGHT));
    goalarea = new QGraphicsPixmapItem();
    goalarea->setPixmap(goalscaledGameBG);

    scene->addItem(goalarea);
    scene->addItem(area);

    ui->boardView->setScene(scene);

    if(g_mode == 1){
        set_pong();
    }else{
        set_arkanoid();
    }

    if(g_mode==1)
        iLoop = new Gameplay(*scene, p1, p2, ball,g_mode, token, this, ball2); // GamePlay objesi oluşturuldu. Oyunu bu yönetir.
    else{
        iLoop = new Gameplay(*scene, p1, p2, ball,g_mode, token, this, ball2);
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

void MainWindow::set_pong(){
   // empty :d 80 iq function
}

void MainWindow::set_arkanoid(){
    ui->aiScore->setVisible(false);
    ui->scoreboard->setVisible(false);
    ui->ai->setVisible(false);
}

void MainWindow::addScore(int count)
{
//    if(g_mode == 1 && count == 10){

//        QTime dieTime= QTime::currentTime().addSecs(2);
//        while (QTime::currentTime() < dieTime);

//        std::cout << "normal ekrani geri getiriyor" << std::endl;
//        goalarea->setVisible(false);
//        area->setVisible(true);
//    }
    if(g_mode == 2 && count == 1){ // arkanoid loses
        ++P1iScore;
        ui->playerScore->display(P1iScore);
        if(P1iScore == 10){
            ResultWindow *who_won = new ResultWindow(NULL, 1, 2);
            who_won->setWindowTitle("Result");
            who_won->show();
            this->close();
        }
    }else if(g_mode == 2 && count == 5){ // arkanoid wins
        std::cout << "arkanoid you won :" << count << std::endl;
        ResultWindow *who_won = new ResultWindow(NULL, 2, 2);
        who_won->setWindowTitle("Result");
        who_won->show();
        this->close();
    }
    if(g_mode == 1){
        if(count == 1){
            P1iScore++;
            ui->playerScore->display(P1iScore);
            ui->playerScore->setPalette(Qt::blue);
            ui->showGoal->setText("GOAL! Player1 Scored");
            ui->showGoal->setVisible(true);
        }
        else{
            P2iScore++;
            ui->aiScore->display(P2iScore);
            ui->aiScore->setPalette(Qt::green);
            ui->showGoal->setText("GOAL! Player2 Scored");
            ui->showGoal->setVisible(true);
        }

        if(P1iScore > P2iScore){
            ui->status->setText("P1 leads the game");
        }else if(P1iScore == P2iScore){
            ui->status->setText("Draw");
        }else{
            ui->status->setText("P2 leads the game");
        }

        if(P1iScore == 3){
            ResultWindow *who_won = new ResultWindow(NULL, 1, 1);
            who_won->show();
            this->close();
        }else if(P2iScore == 3){
            ResultWindow *who_won = new ResultWindow(NULL, 2, 1);
            who_won->show();
            this->close();
        }
        //gol ekranini aciyor
//        if(count != 10){
//            std::cout << "gol ekrani geldi" << std::endl;
//            area->setVisible(false);
//            goalarea->setVisible(true);
//        }

        QTimer::singleShot(500, ui->showGoal, &QLabel::hide);
        QMovie *movie = new QMovie(":/Images/meksika.gif");

        // boyutu burada ayarlanacak
        movie->setScaledSize(QSize(200,25));
        ui->goalScreen->setGeometry(10, 10, 200, 25);
        ui->goalScreen->setAlignment(Qt::AlignCenter);

        ui->goalScreen->setMovie(movie);
        movie->start();
        QTimer::singleShot(1500, ui->goalScreen, &QLabel::hide);
        ui->goalScreen->setVisible(true);
    }

}


void MainWindow::addPlayer(int count){
    std::string s = " The player who participated in the game : Player"  + std::to_string(count);
    ui->labelPlayers->setText(s.c_str());
}
