#include "gameplay.h"
#include<iostream>
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <QGlobal.h>
#include <QTime>
#include <QEvent>
#include <QKeyEvent>
#include <math.h>
#include"mythread.h"
#include "resultwindow.h"
#include <QtMath>

int x_pos_of_ball;
int y_pos_of_ball;

Gameplay::Gameplay(QGraphicsScene & scene, QGraphicsRectItem *p1, QGraphicsRectItem *p2, QGraphicsItem *ball,int gameMode, QGraphicsItem *token, QObject *parent, QGraphicsItem *ball2) :
    QObject(parent),
    iScene ( scene ),
    iP1 ( p1 ),
    iP2 ( p2 ),
    iBall ( ball ),
    iToken ( token ),
    iBall_2 (ball2),
    iTokenDirection(+1, -1),
    iBallDirection ( -3,-3), //ilk anda topun hareket yönü
    iBall2Direction(0, 0),
    iP1Direction( 0 ),
    iP2Direction( 0 )
{
    g_mode = gameMode;

    if(g_mode == 1){
        set_pong();
        QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(pong_tick()));
    }
    else{
        set_arkanoid();
        QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(arkanoid_tick()));
    }

}
void Gameplay::set_arkanoid(){

    iScene.setSceneRect(0, 0, Constant::GAME_AREA_WIDTH, Constant::GAME_AREA_HEIGHT);

    //iP2->setRect(0,0,Constant::PLAYER2_WIDTH, Constant::PLAYER2_HEIGHT);

    iScene.addItem(iP2);
    iScene.addItem(iBall);


    iP2->setPos(Constant::PLAYER2_POS_X/2, Constant::PLAYER2_POS_Y-8);
    iBall->setPos(Constant::GAME_AREA_WIDTH/2, Constant::GAME_AREA_HEIGHT/2);

    iTimer = new QTimer(this);
    iTimer->setInterval(15);
    iTimer->start();


    setBlocks();
    for(int i=0;i<BLOCK_SIZE;i++){
        block_state[i]=true;
    }
//    std::cout << "arkanoids blocks and boolean array are set" << std::endl;
    MyThread::shared.game_mode = 0; // arkanoid oyunu set edildi
}

void Gameplay::set_pong(){
    iScene.setSceneRect(0, 0, Constant::GAME_AREA_WIDTH, Constant::GAME_AREA_HEIGHT);

    iScene.addItem(iP1);
    iScene.addItem(iToken);

    // iP2->setRect(0,0,Constant::PLAYER2_WIDTH, Constant::PLAYER2_HEIGHT);
    iScene.addItem(iP2);
    iScene.addItem(iBall);
    left_side =new QGraphicsRectItem(0, 0, Constant::BLOCK_HEIGHT - 10, Constant::BLOCK_WIDTH + 100);

    iScene.addItem(left_side);
    left_side->setBrush(QBrush(Qt::red));
    left_side->setPos(Constant::GAME_AREA_WIDTH - 6, Constant::GAME_AREA_HEIGHT/2 - 20);


    iP2->setPos(Constant::PLAYER2_POS_X, Constant::PLAYER2_POS_Y-8);
    iBall->setPos(Constant::GAME_AREA_WIDTH/2, Constant::GAME_AREA_HEIGHT/2);
    iToken->setPos(Constant::GAME_AREA_WIDTH/3 + 5, Constant::GAME_AREA_HEIGHT/2 - 5);
    iP1->setPos(Constant::PLAYER1_POS_X, Constant::PLAYER1_POS_Y+8);
//    std::cout << "the position of token and p1 are set" << std::endl;


    iTimer = new QTimer(this);
    iTimer->setInterval(20);
    iTimer->start();
    MyThread::shared.flag_token = 1;
    MyThread::shared.flag_block = 1;
    MyThread::shared.game_mode = 1; // pong oyunu set edildi
}

void Gameplay::check_pong_winner(int player){
//    std::cout << "player" << player << " kazandi" << std::endl;
    game_over = true;
}

void Gameplay::check_arkanoid_winner(){
    game_over = true;
}

void Gameplay::check_blocks(){
    for(int i = 0; i < 8; ++i){
        if(block_state[i] == false)
            ++block_count;
    }
    if(block_count != 8){
        block_count = 0;
    }else if (block_count == 8){
//        std::cout << "block count : " << block_count << std::endl;
        game_over = true;
    }
}

void Gameplay::arkanoid_tick(){

    if(game_over == true){
        return;
    }

    check_blocks();

    qreal newX = iBall->pos().x() + iBallDirection.x();
    qreal newY = iBall->pos().y() + iBallDirection.y();


    qreal pnewx = iP1->pos().x();

    //int gy = MyThread::gyro1;

    gyro1 =   MyThread::shared.gyro1* 2;
    gyro2 =   MyThread::shared.gyro2* 2;

    iP1->setPos(gyro1,iP1->pos().y());

    if ( ( newX < 0 ) || ( newX + iBall->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iBallDirection.rx() *= -1;
    }

    if (game_over == true || ( newY < 0 ) || ( newY + iBall->boundingRect().bottom() > iScene.sceneRect().bottom() ) )
    {
        // 1 for hitting the bottom wall, -1 for hitting the top wall
        if(newY > 0){
            p1Score++;
            if(p1Score > 10)
                check_arkanoid_winner();
        }

        if(game_over == true && control == 0){
//            std::cout << "8 block yok edildi" << std::endl;
            emit goal(5);
            control++;
            return;
        }
        else if(control == 0)
            emit goal(newY / fabs(newY));

        iBallDirection.ry() *= -1;
    }

    // P2 TOP ILE CARPIYOR
    if ( ( iP2->collidesWithItem(iBall) ) && ( iBallDirection.y() > 0 ))
    {
        iBallDirection.ry() *= -1;

        // BURADA TOPUN ACISI DEGISECEK
        int ball_x = iBall->x();
        int p2_x = iP2->pos().rx();

        std::cout << "iball = " << ball_x << std::endl;
        std::cout << "p2 = " << p2_x << std::endl;

        qreal randomNumber = 1 + (rand()%10) * 0.1;

        qreal pos = qFabs(iBall->pos().rx() - iP2->pos().rx());

        if (pos < 2*Constant::PLAYER2_WIDTH*1/5){
            std::cout << "left most " << std::endl;
            iBallDirection.rx() = -1* 2 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*2/5 && pos > 2*Constant::PLAYER2_WIDTH*1/5) {
            std::cout << "left " << std::endl;
            iBallDirection.rx() = -1 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*4/5 && pos > 2*Constant::PLAYER2_WIDTH*3/5) {
            std::cout << "right " << std::endl;
            iBallDirection.rx() = randomNumber;
        }else if (pos > 2*Constant::PLAYER2_WIDTH*4/5) {
            std::cout << "right most" << std::endl;
            iBallDirection.rx() = 2*randomNumber;
        }else {
            std::cout << "middle" << std::endl;
            if(randomNumber > 1.5)
                iBallDirection.rx() = -0.1;
            else
                iBallDirection.rx() = 0.1;
        }
    }

    detectCollusion();

    iBall->moveBy(iBallDirection.x(), iBallDirection.y());

    // iP2->setPos(Constant::PLAYER2_POS_X, Constant::PLAYER2_POS_Y);

    // 0 orta, 1 en sag, -1 en sola gider
//    if(iP2Direction == 0){
//        iP2->setPos(Constant::PLAYER2_POS_X, Constant::PLAYER2_POS_Y-8);
//    }else if(iP2Direction == 1){
//        iP2->setPos(Constant::GAME_AREA_WIDTH-Constant::PLAYER2_WIDTH, Constant::PLAYER2_POS_Y-8);
//    }
//    else if(iP2Direction == -1){
//        iP2->setPos(0, Constant::PLAYER2_POS_Y-8);
//    }

    iP2->moveBy(iP2Direction, 0);
    //qDebug()<<"Ball position:"<<iBall->pos();
    x_pos_of_ball=iBall->pos().rx();
    y_pos_of_ball=iBall->pos().ry();


//    MyThread::setBallX(iBall->pos().x());
//    MyThread::setBallY(iBall->pos().y());

    MyThread::shared.mainBallX = iBall->pos().x();
    MyThread::shared.mainBallY = iBall->pos().y();
}

void Gameplay::pong_tick(){

    if(game_over == true){
        return;
    }

    qreal newX = iBall->pos().x() + iBallDirection.x();
    qreal newY = iBall->pos().y() + iBallDirection.y();

    qreal newX2 = iBall_2->pos().x() + iBall2Direction.x();
    qreal newY2 = iBall_2->pos().y() + iBall2Direction.y();

    qreal newTokenX= iToken->pos().x()+iTokenDirection.x();
    qreal newTokenY = iToken->pos().y()+iTokenDirection.y();

    qreal pnewx = iP1->pos().x();
    qreal p2newx = iP2->pos().x();

    //int gy = MyThread::gyro1;

    gyro1 =   MyThread::shared.gyro1 * 2;
    //gyro1 =   MyThread::getGyro1()* 2;

    iP1->setPos(gyro1,iP1->pos().y());
    //iP2->setPos(gyro2,iP2->pos().y());


    if ( ( newX < 0 ) || ( newX + iBall->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iBallDirection.rx() *= -1;
    }

    if ( ( newX2 < 0 ) || ( newX2 + iBall_2->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iBall2Direction.rx() *= -1;
    }

    if ( ( newY < 0 ) || ( newY + iBall->boundingRect().bottom() > iScene.sceneRect().bottom() ) )
    {
        // 1 for hitting the bottom wall, -1 for hitting the top wall
        if(newY < 0){
            p2Score++;
//            std::cout << "player2" << " : " << p2Score << std::endl;
            if(p2Score == 10){
                check_pong_winner(2); // player 2 kazandi
            }
        }else{
            p1Score++;
//            std::cout << "player1" << " : " << p1Score << std::endl;
            if(p1Score == 10){
                check_pong_winner(1); // player 1 kazandi
            }
        }

        emit goal(newY / fabs(newY));

        iBall->setPos(Constant::GAME_AREA_WIDTH/2, Constant::GAME_AREA_HEIGHT/2);
        iToken->setVisible(true);
        MyThread::shared.flag_token = 1;
        iToken->setPos(Constant::GAME_AREA_WIDTH/3, Constant::GAME_AREA_HEIGHT/2);
        iTokenDirection.rx() = 2;
        iTokenDirection.ry() = -2;
        iTokenDirection *= -1;

        iP2->setRect(0,0,Constant::PLAYER2_WIDTH*2, Constant::PLAYER2_HEIGHT); //2yebol
        iP1->setRect(0,0,Constant::PLAYER2_WIDTH*2, Constant::PLAYER2_HEIGHT); //2yebol

        iBall_2->setPos(0, 0);
        MyThread::shared.flag_top2 = 0;
        iBall_2->setVisible(false);
        iBall2Direction.ry() = 0;
        iBall2Direction.rx() = 0;
        iBallDirection.ry() *= -1;



        // ekrani eski haline getirmke icin
       // emit goal(10);

        iScene.addItem(left_side);
        side_state = true;

    }

    if ( ( newY2 < 0 ) || ( newY2 + iBall_2->boundingRect().bottom() > iScene.sceneRect().bottom() ) )
    {
        // 1 for hitting the bottom wall, -1 for hitting the top wall
        if(newY2 < 0){
            p2Score++;
//            std::cout << "player2" << " : " << p2Score << std::endl;
            if(p2Score == 10){
                check_pong_winner(2); // player 2 kazandi
            }
        }else{
            p1Score++;
//            std::cout << "player1" << " : " << p1Score << std::endl;
            if(p1Score == 10){
                check_pong_winner(1); // player 1 kazandi
            }
        }

        emit goal(newY2 / fabs(newY2));
        iBall->setPos(Constant::GAME_AREA_WIDTH/2, Constant::GAME_AREA_HEIGHT/2);
        iToken->setVisible(true);
        MyThread::shared.flag_token = 1;

        iToken->setPos(Constant::GAME_AREA_WIDTH/3, Constant::GAME_AREA_HEIGHT/2);
        iTokenDirection.rx() = 2;
        iTokenDirection.ry() = -2;
        iTokenDirection *= -1;

        iP2->setRect(0,0,Constant::PLAYER2_WIDTH, Constant::PLAYER2_HEIGHT);
        iP1->setRect(0,0,Constant::PLAYER2_WIDTH, Constant::PLAYER2_HEIGHT);

        iBall_2->setPos(0, 0);
        MyThread::shared.flag_top2 = 0;
        iBall_2->setVisible(false);
        iBall2Direction.ry() = 0;
        iBall2Direction.rx() = 0;

        iBallDirection.ry() *= -1;

        iScene.addItem(left_side);
        side_state = true;
    }

    detectSideCollusion();
    if ( ( pnewx < 0 ) || ( pnewx + iP1->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iP1Direction = 0;

    }

    if ( ( p2newx < 0 ) || ( p2newx + iP2->boundingRect().right() > iScene.sceneRect().right() ) )
    {
        iP2Direction = 0;
    }

    // P2 ILE TOP CARPISIYOR
    if ( ( iP2->collidesWithItem(iBall) ) && ( iBallDirection.y() > 0 ))
    {
        iBallDirection.ry() *= -1;

        // topun sekmesini degistiren yer

        int ball_x = iBall->x();
        int p2_x = iP2->pos().rx();

        qreal randomNumber = 1 + (rand()%10) * 0.1;

        qreal pos = qFabs(iBall->pos().rx() - iP2->pos().rx());

        if (pos < 2*Constant::PLAYER2_WIDTH*1/5){
            std::cout << "left most " << std::endl;
            iBallDirection.rx() = -1* 2 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*2/5 && pos > 2*Constant::PLAYER2_WIDTH*1/5) {
            std::cout << "left " << std::endl;
            iBallDirection.rx() = -1 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*4/5 && pos > 2*Constant::PLAYER2_WIDTH*3/5) {
            std::cout << "right " << std::endl;
            iBallDirection.rx() = randomNumber;
        }else if (pos > 2*Constant::PLAYER2_WIDTH*4/5) {
            std::cout << "right most" << std::endl;
            iBallDirection.rx() = 2*randomNumber;
        }else {
            std::cout << "middle" << std::endl;
            if(randomNumber > 1.5)
                iBallDirection.rx() = -0.1;
            else
                iBallDirection.rx() = 0.1;
        }



    }

    // P2 ILE TOP2 CARPISIYOR
    if ( ( iP2->collidesWithItem(iBall_2) ) && ( iBall2Direction.y() > 0 ))
    {
        iBall2Direction.ry() *= -1;
        qreal randomNumber = 1 + (rand()%10) * 0.1;

        qreal pos = qFabs(iBall->pos().rx() - iP2->pos().rx());

        if (pos < 2*Constant::PLAYER2_WIDTH*1/5){
            std::cout << "left most " << std::endl;
            iBallDirection.rx() = -1* 2 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*2/5 && pos > 2*Constant::PLAYER2_WIDTH*1/5) {
            std::cout << "left " << std::endl;
            iBallDirection.rx() = -1 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*4/5 && pos > 2*Constant::PLAYER2_WIDTH*3/5) {
            std::cout << "right " << std::endl;
            iBallDirection.rx() = randomNumber;
        }else if (pos > 2*Constant::PLAYER2_WIDTH*4/5) {
            std::cout << "right most" << std::endl;
            iBallDirection.rx() = 2*randomNumber;
        }else {
            std::cout << "middle" << std::endl;
            if(randomNumber > 1.5)
                iBallDirection.rx() = -0.1;
            else
                iBallDirection.rx() = 0.1;
        }
    }

    ////////Son eklenen token
    if ( ( newTokenX < 0 ) || ( newTokenX + iToken->boundingRect().right() > iScene.sceneRect().right() ) )
     {
         iTokenDirection.rx() *= -1;
     }

    if ( newTokenY < 0 )
     {
        // -1 for hitting the top wall
        iP2->setRect(0,0,Constant::PLAYER2_WIDTH*2,5);
        iTokenDirection.rx() = 0;
        iTokenDirection.ry() = 0;
        iToken->setPos(100, 100);
        MyThread::shared.flag_token = 0;
        iToken->setVisible(false);
     }
    if( newTokenY + iToken->boundingRect().bottom() > iScene.sceneRect().bottom()){
         //hitting bottom
         iP1->setRect(0,0,Constant::PLAYER1_WIDTH*2,5);
         iTokenDirection.rx() = 0;
         iTokenDirection.ry() = 0;
         iToken->setPos(100, 100);
         MyThread::shared.flag_token = 0;
         iToken->setVisible(false);
     }

    // P1 TOP ILE CARPISIYOR
    if ( ( iP1->collidesWithItem(iBall) ) && ( iBallDirection.y() < 0 ) ){
        iBallDirection.ry() *= -1;

        // topun sekmesini degistiren yer

        qreal randomNumber = 1 + (rand()%10) * 0.1;

        qreal pos = qFabs(iBall->pos().rx() - iP1->pos().rx());



        if (pos < 2*Constant::PLAYER2_WIDTH*1/5){
            std::cout << "left most " << std::endl;
            iBallDirection.rx() = -2 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*2/5 && pos > 2*Constant::PLAYER2_WIDTH*1/5) {
            std::cout << "left " << std::endl;
            iBallDirection.rx() = randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*4/5 && pos > 2*Constant::PLAYER2_WIDTH*3/5) {
            std::cout << "right " << std::endl;
            iBallDirection.rx() = randomNumber;
        }else if (pos > 2*Constant::PLAYER2_WIDTH*4/5) {
            std::cout << "right most" << std::endl;
            iBallDirection.rx() = 2*randomNumber;
        }else {
            std::cout << "middle" << std::endl;
            if(randomNumber > 1.5)
                iBallDirection.rx() = -0.1;
            else
                iBallDirection.rx() = 0.1;
        }

    }
    // P1 BALL2 ILE CARPISIYOR
    if ( ( iP1->collidesWithItem(iBall_2) ) && ( iBall2Direction.y() < 0 ) ){
        iBall2Direction.ry() *= -1;
        qreal randomNumber = 1 + (rand()%10) * 0.1;

        qreal pos = qFabs(iBall->pos().rx() - iP1->pos().rx());

        if (pos < 2*Constant::PLAYER2_WIDTH*1/5){
            std::cout << "left most " << std::endl;
            iBallDirection.rx() = 2 * randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*2/5 && pos > 2*Constant::PLAYER2_WIDTH*1/5) {
            std::cout << "left " << std::endl;
            iBallDirection.rx() = randomNumber;
        }else if (pos < 2*Constant::PLAYER2_WIDTH*4/5 && pos > 2*Constant::PLAYER2_WIDTH*3/5) {
            std::cout << "right " << std::endl;
            iBallDirection.rx() = -randomNumber;
        }else if (pos > 2*Constant::PLAYER2_WIDTH*4/5) {
            std::cout << "right most" << std::endl;
            iBallDirection.rx() = -2*randomNumber;
        }else {
            std::cout << "middle" << std::endl;
            if(randomNumber > 1.5)
                iBallDirection.rx() = -0.1;
            else
                iBallDirection.rx() = 0.1;
        }
    }

    if ( ( iP1->collidesWithItem(iToken) ) && ( iTokenDirection.y() < 0 ) ){
        iTokenDirection.ry() *= -1;
        //orgin1=orgin1+5;
        //iP1->setRect(0,0,orgin1,5);
    }

    if ( ( iP2->collidesWithItem(iToken) ) && ( iTokenDirection.y() > 0 ) ){
        iTokenDirection.ry() *= -1;
        //orgin2=orgin2+5;
        //iP2->setRect(0,0,orgin2,5);
    }
    if ( ( iBall->collidesWithItem(iToken) ) ){
        iTokenDirection.ry() *= -1;
        iTokenDirection.rx() *= -1;
        iBallDirection.ry() *= -1;
    }

    if ( ( iBall_2->collidesWithItem(iToken) ) ){
        iTokenDirection.ry() *= -1;
        iTokenDirection.rx() *= -1;
        iBall2Direction.ry() *= -1;
    }


    if ( qrand() % 10 == 0 ){
        //iP2Direction = calculateP2Direction(gyro2);
    }else if(qrand() % 7 == 0){
        iP1Direction = calculateP1Direction(gyro1);
    }

    iBall->moveBy(iBallDirection.x(), iBallDirection.y());
    iToken->moveBy(iTokenDirection.x(), iTokenDirection.y());
    iBall_2->moveBy(iBall2Direction.x(), iBall2Direction.y());

//    if(iP1Direction==0){
//        iP1->setPos(1,5);
//    }else if(iP1Direction==1){
//        iP1->setPos(80,5);
//    }
//    else if(iP1Direction==-2){
//        iP1->setPos(160,5);
//    }
//    else if(iP1Direction==3){
//        iP1->setPos(240,5);
//    }
//    else{ //iP1->moveBy(iP1Direction, 0);
//    }

    iP2->moveBy(iP2Direction, 0);
    //qDebug()<<"Ball position:"<<iBall->pos();
    x_pos_of_ball=iBall->pos().rx();
    y_pos_of_ball=iBall->pos().ry();

//    MyThread::setBallX(iBall->pos().x());
//    MyThread::setBallY(iBall->pos().y());

    MyThread::shared.mainBallX = iBall->pos().x();
    MyThread::shared.mainBallY = iBall->pos().y();

    MyThread::shared.second_ballX = iBall_2->pos().x();
    MyThread::shared.second_ballY = iBall_2->pos().y();

    MyThread::shared.square_X = iToken->pos().x();
    MyThread::shared.square_Y = iToken->pos().y();

    MyThread::shared.item_X = left_side->pos().x();
    MyThread::shared.item_Y = left_side->pos().y();

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
        blocks[i]=new QGraphicsRectItem(0,0,Constant::BLOCK_WIDTH,Constant::BLOCK_HEIGHT);

        iScene.addItem(blocks[i]);
        blocks[i]->setBrush(QBrush(Qt::red));

        // ekrana yerlestirilip threaddeki shared valuesa kaydediliyor x ve y koordinatlari
        if(i<5){
            blocks[i]->setPos(i*(Constant::BLOCK_WIDTH + 8)+12,10);
            // arkanoiddeki blocklarin koordinatlari
            //MyThread::shared.arkanoid_block_x[i] = i*(Constant::BLOCK_WIDTH + 8)+12;
            //MyThread::shared.arkanoid_block_y[i] = 10;
            /*qDebug() << "Arkanoid block" << i << "(" <<  MyThread::shared.arkanoid_block_x[i]
                        << "," <<  MyThread::shared.arkanoid_block_y[i] << ")";*/
        }else{
            blocks[i]->setPos((i%5)*(Constant::BLOCK_WIDTH + 8)+12+Constant::BLOCK_WIDTH,30);
            // arkanoiddeki blocklarin koordinatlari
            //MyThread::shared.arkanoid_block_x[i] = (i%5)*(Constant::BLOCK_WIDTH + 8)+12+Constant::BLOCK_WIDTH;
            //MyThread::shared.arkanoid_block_y[i] = 30;
            /*qDebug() << "Arkanoid block" << i << "(" <<  MyThread::shared.arkanoid_block_x[i]
                        << "," <<  MyThread::shared.arkanoid_block_y[i] << ")";*/
        }


    }
}
void Gameplay::detectCollusion(){
    for(int i=0;i<8;i++){
        if((blocks[i]->collidesWithItem(iBall)) && block_state[i]==true){
            iBallDirection.ry()*=-1;
            iScene.removeItem(blocks[i]);
            block_state[i]=false;
            MyThread::shared.block_destroyed[i] = 1;
            //defaultP2Size=defaultP2Size-5;
            //qDebug() << i << ". block yok edildi -> blockdestroyed=" << MyThread::shared.block_destroyed[i];
            //iP2->setRect(0,0,defaultP2Size,5);
            //std::cout << "bir block yok edildi" << std::endl;
        }
    }
}

void Gameplay::detectSideCollusion() {
    if((left_side->collidesWithItem(iBall)) && side_state == true){
        iBallDirection.ry()*=-1;
        iScene.removeItem(left_side);
        side_state = false;
        iScene.addItem(iBall_2);
        iBall_2->setVisible(true);
        MyThread::shared.flag_top2 = 1;
        iBall_2->setPos(Constant::GAME_AREA_WIDTH/2, Constant::GAME_AREA_HEIGHT/2);
        iBall2Direction.rx() = -3;
        iBall2Direction.ry() = 3;
        MyThread::shared.flag_block = 0;

//        std::cout << "top sayisi ikiye cikti" << std::endl;
    }
}

