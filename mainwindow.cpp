#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QApplication"
#include "QPainter"
#include "startmenu.h"
#include "QPalette"
#include "QGraphicsBlurEffect"
#include "gameinitial.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    });

}

void MainWindow::initPainter(QPainter* painter)const{
        QMainWindow::initPainter(painter);
        //抗锯齿
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
}

MainWindow::~MainWindow()
{
    delete ui;
}

