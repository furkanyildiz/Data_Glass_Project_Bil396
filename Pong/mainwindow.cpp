#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "gameplay.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    iScore ( 0 )
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

    QSize m(scene->sceneRect().size().width(), scene->sceneRect().size().height());

    ui->boardView->setMinimumSize(m);

    resize(maximumSize());
    ui->boardView->installEventFilter(iLoop);

    QObject::connect(iLoop, SIGNAL(goal(int)), this, SLOT(addScore(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addScore(int count)
{
    iScore += count;
    ui->lcdNumber->display(iScore);
}

