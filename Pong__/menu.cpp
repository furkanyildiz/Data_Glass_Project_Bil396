#include "menu.h"
#include "ui_menu.h"
#include <QListWidgetItem>
#include "mainwindow.h"
#include <iostream>
using namespace std;

int btn1 = 0;
int btn2 = 0;
Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*, int)),
                this, SLOT(on_listWidget_2_itemClicked(QListWidgetItem*, int)));
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    ui->listWidget_2->hide();
    //ui->listWidget_2->disconnect();
        if (btn1 == 1)
            ui->listWidget->show();
        else {
            ui->listWidget->addItem("Gozluk 1");
            ui->listWidget->addItem("Gozluk 2");
            ui->listWidget->addItem("Gozluk 3");
            ui->listWidget->addItem("Gozluk 4");
            ui->listWidget->addItem("Gozluk 5");
            ui->listWidget->addItem("Gozluk 6");

            btn1 = 1;
        }
}

void Menu::on_pushButton_2_clicked()
{
    ui->listWidget->hide();
        if (btn2 == 1)
            ui->listWidget_2->show();
        else {
            ui->listWidget_2->addItem("PONG");
            ui->listWidget_2->addItem("ARCONOID");
            btn2 = 1;
        }
}

void Menu::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    if(ui->listWidget_2->item(0) == item) {
        cout << "PONG" << endl;
        MainWindow *w = new MainWindow;

        w->show();

        this->close();
    }else if(ui->listWidget_2->item(1) == item){
       cout << "ARCONOID" << endl;
       QWidget *p1;
       MainWindow *w = new MainWindow(p1,2);

        w->show();

        this->close();
    }
}

/*
void Menu::on_listWidget_2_itemPressed(QListWidgetItem *item)
{

}*/
