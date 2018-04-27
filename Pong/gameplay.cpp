#include "gameplay.h"
#include<iostream>
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <math.h>
#include"mythread.h"
int x_pos_of_ball;
int y_pos_of_ball;

Gameplay::Gameplay(QGraphicsScene & scene, QGraphicsItem *p1, QGraphicsItem *p2, QGraphicsItem *ball, QObject *parent) :
    QObject(parent),
    iScene ( scene ),
    iP1 ( p1 ),
    iP2 ( p2 ),
    iBall ( ball ),
    iBallDirection ( -3, -3 ), //ilk anda topun hareket yönü
    iP1Direction( 0 ),
    iP2Direction( 0 )
{
    iScene.setSceneRect(0, 0,  350,320);
    iScene.addItem(iP1);
    iScene.addItem(iP2);
    iScene.addItem(iBall);

    iP1->setPos(135, 5);
    iP2->setPos(135, 300);
    iBall->setPos(150, 150);

    iTimer = new QTimer(this);
    iTimer->setInterval(20);
    iTimer->start();

    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(tick()));

}

void Gameplay::tick()
{

    qreal newX = iBall->pos().x() + iBallDirection.x();
    qreal newY = iBall->pos().y() + iBallDirection.y();


    qreal pnewx = iP1->pos().x() + iP1Direction;
    qreal p2newx = iP2->pos().x() + iP2Direction;

    if ( ( newX < 0 ) || ( newX + iBall->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iBallDirection.rx() *= -1;
    }

    if ( ( newY < 0 ) || ( newY + iBall->boundingRect().bottom() > iScene.sceneRect().bottom() ) )
    {
        // 1 for hitting the bottom wall, -1 for hitting the top wall
        emit goal(newY / fabs(newY));
        iBallDirection.ry() *= -1;
    }

    if ( ( pnewx < 0 ) || ( pnewx + iP1->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iP1Direction = 0;

    }

    if ( ( p2newx < 0 ) || ( p2newx + iP1->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iP2Direction = 0;
    }

    if ( ( iP1->collidesWithItem(iBall) ) && ( iBallDirection.y() < 0 ) )
    {
        iBallDirection.ry() *= -1;
    }

    if ( ( iP2->collidesWithItem(iBall) ) && ( iBallDirection.y() > 0 ) )
    {
        iBallDirection.ry() *= -1;
    }

    if ( qrand() % 10 == 0 )
    {
        iP2Direction = calculateP2Direction(cli_data);
    }else if(qrand() % 7 == 0){
        iP1Direction = calculateP1Direction(cli_data2);
    }


    iBall->moveBy(iBallDirection.x(), iBallDirection.y());

    if(iP1Direction==0){
        iP1->setPos(1,5);
    }else if(iP1Direction==1){
        iP1->setPos(80,5);
    }
    else if(iP1Direction==-2){
        iP1->setPos(160,5);
    }
    else if(iP1Direction==3){
        iP1->setPos(240,5);
    }
    else{ //iP1->moveBy(iP1Direction, 0);
    }

    iP2->moveBy(iP2Direction, 0);
    //qDebug()<<"Ball position:"<<iBall->pos();
    x_pos_of_ball=iBall->pos().rx();
    y_pos_of_ball=iBall->pos().ry();
}

bool Gameplay::eventFilter(QObject *target, QEvent *e)
{
    Q_UNUSED(target);

    bool handled = false;
//    if ( e->type() == QEvent::KeyPress )
//    {
//        QKeyEvent *keyEvent = (QKeyEvent *)e;

//        if ( keyEvent->key() == Qt::Key_Left )
//        {
//            iP1Direction = (iP1Direction == 0 ? -5 : 0);
//            handled = true;
//        }
//        else if ( keyEvent->key() == Qt::Key_Right )
//        {
//            iP1Direction  = (iP1Direction == 0 ? 5 : 0);
//            handled = true;
//        }
//    }

    return handled;
}

qreal Gameplay::calculateP2Direction(int client_data)
{
    qreal dir = 0;

    dir=client_data;
    if((iP2->pos().x()>=270)&&client_data%2!=0){//EGER RAKET EN SAGDAYSA SADECE RAKETI SOLA HAREKET ETTIRECEK KOMUT BEKLEYECEK
        dir=0;//AKSI HALDE RAKET HAREKET ETMEYECEK
    }
    else if(iP2->pos().x()<=0&&client_data%2==0){dir=0;}

    return dir;

}
qreal Gameplay::calculateP1Direction(int client_data){
    qreal dir = 0;

    dir=client_data;
    if((iP1->pos().x()>=270)&&client_data%2!=0){
        //EGER RAKET EN SAGDAYSA SADECE RAKETI SOLA HAREKET ETTIRECEK KOMUT BEKLEYECEK
        dir=0;//AKSI HALDE RAKET HAREKET ETMEYECEK
    }
    else if(iP1->pos().x()<=0&&client_data%2==0){dir=0;}


    return dir;
}
/*qreal Gameplay::calculateP2Direction()
{
    qreal dir = 0;

    if ( iBall->pos().x() + iBallDirection.x() > iP2->sceneBoundingRect().right() )
    {
        // move right
        dir = 5;
    }
    else if ( iBall->pos().x() + iBallDirection.x() < iP2->sceneBoundingRect().left() )
    {
        // move left
        dir = -5;
    }

    return dir;*/
