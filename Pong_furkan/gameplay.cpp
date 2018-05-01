#include "gameplay.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <math.h>

Gameplay::Gameplay(QGraphicsScene & scene, QGraphicsItem *p1, QGraphicsItem *p2, QGraphicsItem *ball,
                   QObject *parent,MainWindow *mWindow) :
    QObject(parent),
    iScene ( scene ),
    iP1 ( p1 ),
    iP2 ( p2 ),
    iBall ( ball ),
    iBallDirection ( -3, -3 ), //ilk anda topun hareket yönü
    iP1Direction( 0 ),
    iP2Direction( 0 ),
    mainWindow(mWindow)
{
    iScene.setSceneRect(0, 0,  256,512);
    //iScene.setSceneRect(0, 0,  64,128);
    iScene.addItem(iP1);
    iScene.addItem(iP2);
    iScene.addItem(iBall);

    iP1->setPos(135, 5);
    iP2->setPos(135, 300);
    iBall->setPos(150, 150);

    iTimer = new QTimer(this);
    iTimer->setInterval(12);
    iTimer->start();

    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(tick()));

}

void Gameplay::tick()
{
    qreal newX = iBall->pos().x() + iBallDirection.x();
    qreal newY = iBall->pos().y() + iBallDirection.y();

//    iP1->pos().setX(100);
  //  iP2->pos().setX(18);
    qreal pnewx = iP1->pos().x();
    qreal p2newx = iP2->pos().x();

    //int gy = MyThread::gyro1;

     int gy =   MyThread::getGyro1()* 6;
     int gy2 =   MyThread::getGyro2()* 6;

    iP1->setPos(gy,iP1->pos().y());
    iP2->setPos(gy2,iP2->pos().y());

    /*
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
        iP2Direction = calculateP2Direction();
    }else if(qrand() % 7 == 0){
        iP1Direction = randomPlayerMovement();
    }

    mainWindow->updatePos(iBall->pos());
    iBall->moveBy(iBallDirection.x(), iBallDirection.y());
    iP1->moveBy(iP1Direction, 0);
    iP2->moveBy(iP2Direction, 0);*/
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

qreal Gameplay::calculateP2Direction()
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

    return dir;

}
qreal Gameplay::randomPlayerMovement(){
    qreal dir = 0;
    qreal rnd = 0;
    rnd = qrand() % 10;

    if ( iBall->pos().x() + iBallDirection.x() > iP1->sceneBoundingRect().right() )
    {
        // move right
        dir = rnd;
    }
    else if ( iBall->pos().x() + iBallDirection.x() < iP1->sceneBoundingRect().left() )
    {
        // move left
        dir = -rnd;
    }

    return dir;
}
