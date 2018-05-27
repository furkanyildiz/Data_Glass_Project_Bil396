#include "gerisayimekrani.h"
#include "ui_gerisayimekrani.h"
#include <QMovie>
#include <QDebug>
#include <QThread>

GeriSayimEkrani::GeriSayimEkrani(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeriSayimEkrani)
{
    ui->setupUi(this);
    qDebug() << "geri sayim olusturuldu";
    // baslangic ekrani
    QMovie *movie = new QMovie(":/Images/3seconds.gif");
    movie->setScaledSize(QSize(430,300));
    ui->gerisayim->setMovie(movie);
    movie->start();

    qDebug() << "movie olusturuldu";
    ui->gerisayim->setGeometry(10, 10, 380, 250);
    ui->gerisayim->setAlignment(Qt::AlignCenter);
    qDebug() << "yer olusturuldu";

}
void GeriSayimEkrani::stopscreen(){
    qDebug() << "stop screene girdi";
    this->close();
}

GeriSayimEkrani::~GeriSayimEkrani()
{
    delete ui;
}
