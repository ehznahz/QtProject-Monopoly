#include "startmenu.h"
#include "stylizedbutton.h"
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
        qDebug()<<"点击了info";
    });

    //退出游戏
    stylizedButton* exitBtn = new stylizedButton(40,40,":/resources/image/icons/exit.png");
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.985-exitBtn->width(),this->height()*0.08-exitBtn->height());
    // TODO 通知确定模块化
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

    //设置游戏
    stylizedButton* settingBtn = new stylizedButton(40,40,":/resources/image/icons/setting.png");
    settingBtn->setParent(this);
    settingBtn->move(this->width()*0.95-settingBtn->width(),this->height()*0.08-exitBtn->height());
    connect(settingBtn,&stylizedButton::clicked,[=](){
        qDebug()<<"点击了setting";
    });
}

void startMenu::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap bk("://resources/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),bk);
}
