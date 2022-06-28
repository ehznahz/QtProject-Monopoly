#include "headers/mainwindow.h"

#include <utility>
#include "headers/gameinitial.h"
#include "headers/startmenu.h"
#include "headers/mainloop.h"
#include "QApplication"
#include "QPainter"
#include "QPalette"
#include "QGraphicsBlurEffect"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    setFixedSize(1600,900);
    this->setWindowTitle("Monopoly");
    this->setWindowIcon(QIcon(":/resources/image/icons/dice.png"));

    startMenu* newMenu = new startMenu(this);
    newMenu->move(0,0);
    newMenu->show();
    gameInitial* initMenu = new gameInitial(this);
    initMenu->move(0,0);
    initMenu->hide();

    connect(newMenu,&startMenu::beginClicked,this,[=](){
        newMenu->hide();
        initMenu->show();
        //游戏mainloop
    });

    mainloop* mainLoop = new mainloop(this);
    mainLoop->hide();

    connect(initMenu,&gameInitial::gameStarted,this,[=](QList<Player *> _player, int playerCount, int roundLimit, bool pointEnabled){
        initMenu->hide();
        mainLoop->reset(std::move(_player),playerCount,roundLimit,pointEnabled);
        mainLoop->show();
        //mainLoop->gamestart();
    });

}

void MainWindow::initPainter(QPainter* painter)const{
        QMainWindow::initPainter(painter);
        //抗锯齿
        //painter->setRenderHint(QPainter::Antialiasing);
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
}


