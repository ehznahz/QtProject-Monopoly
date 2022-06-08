#include "headers/stylizedbutton.h"
#include "QGraphicsDropShadowEffect"
#include "headers/eventwatcher.h"
#include "QPainter"
#include "QUrl"
#include "QApplication"
#include "QPaintEvent"
#include "QPropertyAnimation"
#include "QEasingCurve"

stylizedButton::stylizedButton(QString text,int _width,int _height):QPushButton(text){
    //设置样式
    origPix=nullptr;
    this->setStyleSheet("QPushButton{border:none;"
                        "color:white;"
                        "border-radius: 10px;"
                        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #e77ec6, stop: 0.50 #e854ba, stop: 0.87 #e742b5, stop: 1 #e742b5);}"
                        "QPushButton:hover:!pressed{background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #ef93d3, stop: 0.87 #ef66c4, stop: 1 #ef53c0);}"
                        "QPushButton:pressed{background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #aa5385, stop: 0.87 #aa2873, stop: 1 #aa2873);}"
                        "QPushButton:disabled{background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #979797, stop: 0.50 #6e6e6e, stop: 0.87 #5a5a5a, stop: 1 #5a5a5a);}"
                        );
    this->setFixedSize(_width,_height);
    //阴影
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setColor(QColor(0x130f1d));
    effect->setBlurRadius(20);
    effect->setOffset(2,2);
    this->setGraphicsEffect(effect);
    //checkable 特性
    connect(this,&stylizedButton::toggled,[=](bool){
        this->update();
    });
}

stylizedButton::stylizedButton(int _width,int _height, QString origImg, QString pressedImg, QString hoverImg,QString checkedImg){
// TODO 处理图片按钮的 disabled 状态
    QPixmap *pix= new QPixmap(origImg);
    if(_width==-1)_width=pix->width();
    if(_height==-1)_height=pix->height();
    this->setFixedSize(_width, _height);
    this->setStyleSheet("border:none;");

    origPix = new QIcon(*pix);
    this->setIconSize(QSize(_width, _height));
    QPainter painter(pix);
    origPix->paint(&painter,0,0,_width,_height);
    this->setIcon(*origPix);

    if(pressedImg==""){
        connect(this,&stylizedButton::pressed,[=](){
            auto effect = new QGraphicsOpacityEffect(this);
            effect->setOpacity(0.5);
            this->setGraphicsEffect(effect);
        });
    } else {
        QPixmap pressPixmap(pressedImg);
        pressedPix = new QIcon(pressPixmap);
        QPainter painter(&pressPixmap);
        pressedPix->paint(&painter,0,0,_width,_height);
        connect(this,&stylizedButton::pressed,[=](){
            this->setIcon(*pressedPix);
        });
    }

    if(hoverImg!=""){
        QPixmap hoverPixmap(hoverImg);
        hoverPix = new QIcon(hoverPixmap);
        QPainter painter(&hoverPixmap);
        hoverPix->paint(&painter,0,0,_width,_height);
    }

    if(checkedImg!=""){
        QPixmap checkedPixmap(checkedImg);
        checkedPix = new QIcon(checkedPixmap);
        QPainter painter(&checkedPixmap);
        checkedPix->paint(&painter,0,0,_width,_height);
        connect(this,&stylizedButton::toggled,[=](bool c){
            if(c) this->setIcon(*checkedPix);
            else this->setIcon(*origPix);
        });
    }
    else{
        QPropertyAnimation* ani=nullptr;
        connect(this,&stylizedButton::toggled,[=,&ani](bool c){// clazy:exclude=lambda-in-connect
            if(c) {
                auto nef = new QGraphicsOpacityEffect(this);
                this->setGraphicsEffect(nef);
                ani= new QPropertyAnimation(nef,"opacity");
                ani->setDuration(1000);
                ani->setStartValue(0.5);
                ani->setEndValue(1);
                ani->setEasingCurve(QEasingCurve::InOutQuad);
                connect(ani,&QPropertyAnimation::finished,[=](){

                    if(ani->direction()==QPropertyAnimation::Backward){
                        ani->setDirection(QPropertyAnimation::Forward);
                    }
                    else ani->setDirection(QPropertyAnimation::Backward);
                    ani->start();
                });
                ani->start();
            }else {
                if(ani!=nullptr)delete ani;
                delete this->graphicsEffect();
            };
        });
    }

    eventWatcher* w = new eventWatcher(this);
    this->installEventFilter(w);
}

void stylizedButton::initPainter(QPainter * painter) const{
    QPushButton::initPainter(painter);
    //抗锯齿
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
}

void stylizedButton::paintEvent(QPaintEvent * event){
    this->QPushButton::paintEvent(event);
    //文字类型按钮的选中
    if(origPix==nullptr&&this->isCheckable()){
        if(this->isChecked()){
            QPainter painter(this);
            QPixmap pix(":/resources/image/icons/checked.png");
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::SmoothPixmapTransform);
            painter.drawPixmap(this->width()-this->height(),this->height()*3/10,this->height()*2/5,this->height()*2/5,pix);
        }
    }
}
