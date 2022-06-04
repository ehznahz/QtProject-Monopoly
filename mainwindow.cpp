#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QApplication"
#include "QPainter"
#include "stylizedbutton.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1600,900);
    stylizedButton* btn = new stylizedButton("开始游戏",500,80);
    btn->setParent(this);
    btn->move(this->width()*0.5-btn->width()*0.5,this->height()*0.62);
    btn->setFont(QFont("Noto Sans SC",20,700));
}

void MainWindow::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap bk("://resources/image/background.png");
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //更好的缩放
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0,0,this->width(),this->height(),bk);
}

MainWindow::~MainWindow()
{
    delete ui;
}

