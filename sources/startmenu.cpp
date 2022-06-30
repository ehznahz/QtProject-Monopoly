#include "headers/startmenu.h"
#include "headers/stylizedbutton.h"
#include "QApplication"
#include "QGraphicsBlurEffect"
#include "QPainter"
#include "QLabel"

startMenu::startMenu(QWidget *parent): QWidget{parent}{
    this->setFixedSize(1600,900);
    //开始游戏按键
    stylizedButton* startBtn = new stylizedButton("开始游戏",500,80);
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.62);
    startBtn->setFont(QFont("Noto Sans SC",20,700));
    connect(startBtn,SIGNAL(clicked(bool)),this,SIGNAL(beginClicked(bool)));

    //游戏信息
    stylizedButton* infoBtn = new stylizedButton(44,44,":/resources/image/icons/info.png");
    infoBtn->setParent(this);
    infoBtn->move(this->width()*0.985-infoBtn->width(),this->height()*0.98-infoBtn->height());
    connect(infoBtn,&stylizedButton::clicked,[=](){
        QWidget* pop = new QWidget();
        pop->setObjectName("infoWidget");
        pop->setStyleSheet("QWidget#infoWidget{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}"
                           "QLabel{color:white;}");
        pop->setParent(this->parentWidget());
        pop->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
        pop->setFixedSize(1600,900);
        pop->move(0,0);
        stylizedButton* close = new stylizedButton( 40, 40,":/resources/image/icons/close.png");
        close->setParent(pop);
        close->move(1500, 50);
        close->show();
        connect(close, &stylizedButton::pressed, this, [=]{
            pop->close();
        });
        //文字
        QLabel *text = new QLabel();
        text->setParent(pop);
        text->setText("关于");
        text->setFont(QFont("Noto Sans SC",25,700));
        text->setGeometry(this->width()*0.3,this->height()*0.2+50,500,40);
        text->setAlignment(Qt::AlignLeft);

        QLabel *content = new QLabel();
        content->setParent(pop);
        content->setText("该程序是北京大学2022年程序设计实习的大作业。\n"
                         "贡献者:   @candidBoy @LeehWinCing @ehznahz\n\n"
                         "该项目的完成离不开众多的开源软件和开放版权或免费内容:\n"
                         "部分图标  来自  Icons 8;\n"
                         "部分图标  来自  Emoji 项目;\n"
                         "该程序由  Qt  驱动。\n\n"
                         "该程序以  GNU LGPL v2.1  协议开放源码。");
        content->setFont(QFont("Noto Sans SC",16,500));
        content->setGeometry(this->width()*0.3,305,800,500);
        content->setAlignment(Qt::AlignLeft);
        text->show();
        pop->show();
    });

    //退出游戏
    stylizedButton* exitBtn = new stylizedButton(40,40,":/resources/image/icons/exit.png");
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.985-exitBtn->width(),this->height()*0.08-exitBtn->height());
    connect(exitBtn,&stylizedButton::clicked,this,[=](){
        QWidget* pop = new QWidget();
        pop->setObjectName("quitWidget");
        pop->setStyleSheet("QWidget#quitWidget{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}");
        pop->setParent(this->parentWidget());
        pop->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
        pop->setFixedSize(1600,900);
        pop->move(0,0);
        //按钮
        stylizedButton* confirm = new stylizedButton("确定",230,50);
        confirm->setParent(pop);
        confirm->move(pop->width()*0.5+20,550);
        connect(confirm,&stylizedButton::clicked,this,[=](){
            this->parentWidget()->close();
        });
        stylizedButton* cancel = new stylizedButton("取消",230,50);
        cancel->setParent(pop);
        cancel->move(this->width()*0.5-250,550);
        connect(cancel,&stylizedButton::clicked,pop,[=](){
            pop->close();
        });
        //文字
        QLabel *text = new QLabel();
        text->setParent(pop);
        text->setText("确定要退出游戏吗?");
        text->setFont(QFont("Noto Sans SC",25,700));
        text->setGeometry(this->width()*0.5-250,this->height()*0.4-25,500,50);
        text->setAlignment(Qt::AlignCenter);
        text->setStyleSheet("QLabel{color:white;}");
        text->show();
        pop->show();
    });
}

void startMenu::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap bk("://resources/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),bk);
}
