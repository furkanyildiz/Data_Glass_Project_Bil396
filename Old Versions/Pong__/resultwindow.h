#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>
#include <mainwindow.h>
namespace Ui {
class ResultWindow;
}

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = 0, int player_no = 0, int game_mode = 0);
    ~ResultWindow();

private slots:
    void on_cancel_clicked();

private:

    Ui::ResultWindow *ui;
};

#endif // RESULTWINDOW_H
