#include "headers/block.h"
#include "QPainter"

Block::Block(std::string __name, std::string _action, std::string _type, int _color, int _price0, int _price1, int _price2, int _sizeType ,int _direction) {
    name = __name;
    action = _action;
    type = _type;
    color = _color;
    price[0] = _price0;
    price[1] = _price1;
    price[2] = _price2;
    owner = -1;
    mortgaged = false;
    united = false;
    house = 0;
    sizeType=_sizeType;
    if(sizeType){
        if(_direction%2){
            this->setFixedSize(106,72);
        }
        else this->setFixedSize(72,106);
    }
    else this->setFixedSize(106,106);
    direction=_direction;
}

void Block::Buy(int __player) {
    owner = __player;
}

void Block::Mortgage() {
    mortgaged = true;
}

void Block::Redeem() {
    mortgaged = false;
}

void Block::Build() {
    ++house;
}

void Block::Sell() {
    --house;
}

void Block::ChangeUnited(bool __united) {
    united = __united;
}

std::string Block::Type() const {
    return type;
}

int Block::Color() const{
    if(color==-1)return RGBColor[0];
    return RGBColor[color];
}

int Block::Price0() const{
    return price[0];
}

int Block::Price1() const {
    return price[1];
}

int Block::Price2() const {
    if(house == 0) return price[2] * (united ? 2 : 1);
    if(house == 1) return price[2] * 4;
    if(house == 2) return price[2] * 12;
    if(house == 3) return price[2] * 28;
    if(house == 4) return price[2] * 34;
    return price[2] * 40;
}

int Block::Owner() const {
    return owner;
}

int Block::House() const{
    return house;
}

void Block::paintEvent(QPaintEvent *) {
    //sizeType 0->四角 106*106 1->四边 106*72
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(QPen(QColor(0,0,0,0)));//设置画笔形式
    painter.setBrush(QBrush(QColor(Color()),Qt::SolidPattern));//设置画刷形式
    painter.drawRoundedRect(0,0,QWidget::width(),QWidget::height(),10,10);
}