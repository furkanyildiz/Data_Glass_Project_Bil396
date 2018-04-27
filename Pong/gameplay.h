#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>
#include <QLabel>
#include <QGraphicsScene>
class QGraphicsItem;
class QTimer;

extern int x_pos_of_ball;
extern int y_pos_of_ball;

class Gameplay : public QObject
{
    Q_OBJECT // bu macro meta-obje içeren tüm classlarda bulunmalı,q

public:
    explicit Gameplay(QGraphicsScene & scene, QGraphicsItem *p1, QGraphicsItem *p2, QGraphicsItem *ball, QObject *parent);
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
    QGraphicsItem *iP1, *iP2, *iBall;
    QTimer *iTimer;

    QPointF iBallDirection;
    qreal iP1Direction;
    qreal iP2Direction;
};

#endif // GAMEPLAY_H
