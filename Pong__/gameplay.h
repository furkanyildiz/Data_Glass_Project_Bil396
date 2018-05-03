#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>
#include <QLabel>
#include <QGraphicsScene>
#include "constants.h"
class QGraphicsItem;
class QTimer;

extern int x_pos_of_ball;
extern int y_pos_of_ball;
#define BLOCK_SIZE 8

class Gameplay : public QObject
{
    Q_OBJECT // bu macro meta-obje içeren tüm classlarda bulunmalı,q

public:
    explicit Gameplay(QGraphicsScene & scene, QGraphicsRectItem *p1, QGraphicsRectItem *p2, QGraphicsItem *ball,int gameMode, QGraphicsItem *token,QObject *parent);
protected:
    virtual bool eventFilter(QObject *, QEvent *);

signals:
    void goal(int player);

private slots:
    void tick();

private:
    qreal calculateP2Direction(int client_data);
    qreal calculateP1Direction(int client_data);
      int data=5;
private:
    QGraphicsScene & iScene;
    QGraphicsItem  *iBall, *iToken;
    QGraphicsRectItem *blocks[8],*iP1 , *iP2;
    bool block_state[8];
    void setBlocks();
    void detectCollusion();
    int defaultP2Size=60;
    QTimer *iTimer;
    qreal orgin1=30;
    qreal orgin2=30;
    QPointF iBallDirection;
    QPointF iTokenDirection;
    qreal iP1Direction;
    qreal iP2Direction;
    int g_mode;
    int gyro1;
    int gyro2;
};

#endif // GAMEPLAY_H
