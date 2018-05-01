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

Gameplay::Gameplay(QGraphicsScene & scene, QGraphicsRectItem *p1, QGraphicsRectItem *p2, QGraphicsItem *ball,int gameMode, QGraphicsItem *token, QObject *parent) :
    QObject(parent),
    iScene ( scene ),
    iP1 ( p1 ),
    iP2 ( p2 ),
    iBall ( ball ),
    iToken ( token ),
    iTokenDirection(+1, -1),
    iBallDirection ( -3, -3 ), //ilk anda topun hareket yönü
    iP1Direction( 0 ),
    iP2Direction( 0 )
{
   g_mode=gameMode;
    iScene.setSceneRect(0, 0,  128,256);
    if(g_mode==1){//pong ıcın
        iScene.addItem(iP1);
        iScene.addItem(iToken);
        iP2->setRect(0,0,30,5);
    }
    iScene.addItem(iP2);
    iScene.addItem(iBall);


    iP1->setPos(49, 12);
    iP2->setPos(49, 244);
    iBall->setPos(64, 128);
    iToken->setPos(120,90);

    iTimer = new QTimer(this);
    iTimer->setInterval(20);
    iTimer->start();

   if(g_mode==2){
    setBlocks();
    for(int i=0;i<8;i++){
        block_state[i]=true;
    }

   }
    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(tick()));

}

void Gameplay::tick()
{

    qreal newX = iBall->pos().x() + iBallDirection.x();
    qreal newY = iBall->pos().y() + iBallDirection.y();

    qreal newTokenX= iToken->pos().x()+iTokenDirection.x();
    qreal newTokenY = iToken->pos().y()+iTokenDirection.y();
//    iP1->pos().setX(100);
  //  iP2->pos().setX(18);
    qreal pnewx = iP1->pos().x();
    qreal p2newx = iP2->pos().x();

    //int gy = MyThread::gyro1;

     gyro1 =   MyThread::getGyro1()* 2;
     gyro2 =   MyThread::getGyro2()* 2;

    iP1->setPos(gyro1,iP1->pos().y());
    iP2->setPos(gyro2,iP2->pos().y());



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

    if ( ( p2newx < 0 ) || ( p2newx + iP2->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iP2Direction = 0;
    }

    if ( ( iP2->collidesWithItem(iBall) ) && ( iBallDirection.y() > 0 ))
    {
        iBallDirection.ry() *= -1;


    }
    if(g_mode==1){
        ////////Son eklenen token
         if ( ( newTokenX < 0 ) || ( newTokenX + iToken->boundingRect().right() > iScene.sceneRect().right() ) )
         {
             iTokenDirection.rx() *= -1;
         }

         if ( newTokenY < 0 )
         {
            // -1 for hitting the top wall
            orgin1=orgin1-5;
            iP1->setRect(0,0,orgin1,5);
            iTokenDirection.ry() *= -1;
         }
         if( newTokenY + iToken->boundingRect().bottom() > iScene.sceneRect().bottom()){
             //hitting bottom
             orgin2=orgin2-5;
             iP2->setRect(0,0,orgin2,5);
             iTokenDirection.ry() *= -1;
         }


        if ( ( iP1->collidesWithItem(iBall) ) && ( iBallDirection.y() < 0 ) )
    {
        iBallDirection.ry() *= -1;

    }
        if ( ( iP1->collidesWithItem(iToken) ) && ( iTokenDirection.y() < 0 ) )
    {
        iTokenDirection.ry() *= -1;
        orgin1=orgin1+5;
        iP1->setRect(0,0,orgin1,5);
    }

        if ( ( iP2->collidesWithItem(iToken) ) && ( iTokenDirection.y() > 0 ) )
    {
        iTokenDirection.ry() *= -1;
        orgin2=orgin2+5;
        iP2->setRect(0,0,orgin2,5);
    }
        if ( ( iBall->collidesWithItem(iToken) ) )
    {
        iTokenDirection.ry() *= -1;
        iTokenDirection.rx() *= -1;
        iBallDirection.ry() *= -1;
    }
    }
    if(g_mode==2){
        detectCollusion();
    }

    if ( qrand() % 10 == 0 )
    {
        iP2Direction = calculateP2Direction(gyro2);
    }else if(qrand() % 7 == 0){
        iP1Direction = calculateP1Direction(gyro1);
    }

    iBall->moveBy(iBallDirection.x(), iBallDirection.y());
    iToken->moveBy(iTokenDirection.x(), iTokenDirection.y());

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


    MyThread::setBallX(iBall->pos().x());
    MyThread::setBallY(iBall->pos().y());

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
    if((iP2->pos().x()>=98)&&client_data%2!=0){//EGER RAKET EN SAGDAYSA SADECE RAKETI SOLA HAREKET ETTIRECEK KOMUT BEKLEYECEK
        dir=0;//AKSI HALDE RAKET HAREKET ETMEYECEK
    }
    else if(iP2->pos().x()<=0&&client_data%2==0){dir=0;}

    return dir;

}
qreal Gameplay::calculateP1Direction(int client_data){
    qreal dir = 0;

    dir=client_data;
    if((iP1->pos().x()>=98)&&client_data%2!=0){
        //EGER RAKET EN SAGDAYSA SADECE RAKETI SOLA HAREKET ETTIRECEK KOMUT BEKLEYECEK
        dir=0;//AKSI HALDE RAKET HAREKET ETMEYECEK
    }
    else if(iP1->pos().x()<=0&&client_data%2==0){dir=0;}


    return dir;
}
void Gameplay::setBlocks(){
    for(int i=0;i<8;i++){
        blocks[i]=new QGraphicsRectItem(0,0,16,10);

        iScene.addItem(blocks[i]);
        blocks[i]->setBrush(QBrush(Qt::red));

        if(i<5)
            blocks[i]->setPos(i*20+10,10);
        else{
            blocks[i]->setPos((i%5)*20+30,30);
        }
    }
}
void Gameplay::detectCollusion(){
    for(int i=0;i<8;i++){
        if((blocks[i]->collidesWithItem(iBall))&&block_state[i]==true){
            iBallDirection.ry()*=-1;
            iScene.removeItem(blocks[i]);
            block_state[i]=false;
            defaultP2Size=defaultP2Size-5;
            iP2->setRect(0,0,defaultP2Size,5);
        }
    }
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
