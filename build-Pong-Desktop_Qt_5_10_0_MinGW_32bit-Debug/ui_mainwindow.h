/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLCDNumber *playerScore;
    QLabel *ai;
    QLabel *player;
    QLCDNumber *aiScore;
    QLabel *scoreboard;
    QGraphicsView *boardView;
    QLabel *showGoal;
    QLabel *status;
    QLabel *labelPlayers;
    QLabel *goalScreen;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(527, 517);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        playerScore = new QLCDNumber(centralWidget);
        playerScore->setObjectName(QStringLiteral("playerScore"));

        gridLayout->addWidget(playerScore, 2, 3, 1, 1);

        ai = new QLabel(centralWidget);
        ai->setObjectName(QStringLiteral("ai"));

        gridLayout->addWidget(ai, 3, 4, 1, 1);

        player = new QLabel(centralWidget);
        player->setObjectName(QStringLiteral("player"));

        gridLayout->addWidget(player, 2, 4, 1, 1);

        aiScore = new QLCDNumber(centralWidget);
        aiScore->setObjectName(QStringLiteral("aiScore"));

        gridLayout->addWidget(aiScore, 3, 3, 1, 1);

        scoreboard = new QLabel(centralWidget);
        scoreboard->setObjectName(QStringLiteral("scoreboard"));

        gridLayout->addWidget(scoreboard, 2, 2, 1, 1);

        boardView = new QGraphicsView(centralWidget);
        boardView->setObjectName(QStringLiteral("boardView"));

        gridLayout->addWidget(boardView, 5, 0, 1, 5);

        showGoal = new QLabel(centralWidget);
        showGoal->setObjectName(QStringLiteral("showGoal"));

        gridLayout->addWidget(showGoal, 2, 1, 1, 1);

        status = new QLabel(centralWidget);
        status->setObjectName(QStringLiteral("status"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(status->sizePolicy().hasHeightForWidth());
        status->setSizePolicy(sizePolicy);

        gridLayout->addWidget(status, 3, 1, 1, 1);

        labelPlayers = new QLabel(centralWidget);
        labelPlayers->setObjectName(QStringLiteral("labelPlayers"));

        gridLayout->addWidget(labelPlayers, 4, 1, 1, 1);

        goalScreen = new QLabel(centralWidget);
        goalScreen->setObjectName(QStringLiteral("goalScreen"));
        goalScreen->setEnabled(true);

        gridLayout->addWidget(goalScreen, 6, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 527, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        ai->setText(QApplication::translate("MainWindow", "AI", nullptr));
        player->setText(QApplication::translate("MainWindow", "Player", nullptr));
        scoreboard->setText(QApplication::translate("MainWindow", "Scoreboard", nullptr));
        showGoal->setText(QString());
        status->setText(QString());
        labelPlayers->setText(QApplication::translate("MainWindow", "Wait for connecting...", nullptr));
        goalScreen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
