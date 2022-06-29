#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "QPushButton"
#include "headers/player.h"

class Block : public QAbstractButton
{
    Q_OBJECT
    QString name;
    QString action;
    QString type;
    int color;
    int price[3]; //地面、房子、租金底价
    int owner;
    bool mortgaged;
    bool united;
    int house;

    int direction;
    int sizeType;
    void paintEvent(QPaintEvent*)override;
    const int RGBColor[9]={0x2C1F36,0xf94144,0xF3722C,0xF8961E,0xF9C74F,0x90BE6D,0x43AA8B,0x4D908E,0x577590};

public:
    Block(QString, QString, QString, int, int, int, int, int, int);
    void Buy(int);
    void Mortgage();
    void Redeem();
    void Build();
    void Sell();
    void ChangeUnited();
    QString Name() const;
    QString Action() const;
    QString Type() const;
    int Color() const;
    int Price0() const;
    int Price1() const;
    int Price2() const;
    int Rent() const;
    int Owner() const;
    bool Mortgaged() const;
    bool United() const;
    int House() const;
};
#endif
