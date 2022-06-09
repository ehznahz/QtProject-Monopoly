#ifndef PLAYERSYMBOL_H
#define PLAYERSYMBOL_H

#include "QWidget"
#include "QAbstractButton"

//TODO onHoverInGame
//TODO activeStyle

class playerSymbol:public QAbstractButton{
    Q_OBJECT
private:
    int color;
    int direction;
public:
    playerSymbol(int _color, int _direction, int _width, int _height);
    void paintEvent(QPaintEvent*) override;
    void setFixedSize(int w,int h);
    void setDirection(int);
    void setColor(int _c);
    int getColor();
    int getDirection();
};


#endif//PLAYERSYMBOL_H
