#include "stylizedbutton.h"
#include "QGraphicsDropShadowEffect"
stylizedButton::stylizedButton(QString text,int _width,int _height):QPushButton(text){
    //设置样式
    this->setStyleSheet("border:none;"
                        "color:white;"
                        "border-radius: 10px;"
                        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #e77ec6, stop: 0.50 #e854ba, stop: 0.87 #e742b5, stop: 1 #e742b5);"
                        );
    this->setFixedSize(_width,_height);
    //阴影
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setColor(QColor("#130f1d"));
    effect->setBlurRadius(20);
    effect->setOffset(3,3);
    this->setGraphicsEffect(effect);
}

stylizedButton::stylizedButton(QString origImg, QString pressedImg){

}
