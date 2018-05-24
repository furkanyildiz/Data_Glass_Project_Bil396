#ifndef GERISAYIMEKRANI_H
#define GERISAYIMEKRANI_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class GeriSayimEkrani;
}

class GeriSayimEkrani : public QDialog
{
    Q_OBJECT

public:
    explicit GeriSayimEkrani(QWidget *parent = 0);
    ~GeriSayimEkrani();
    void stopscreen();
private:
    int flag = 0;
    Ui::GeriSayimEkrani *ui;
};

#endif // GERISAYIMEKRANI_H
