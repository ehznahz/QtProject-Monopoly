#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "QPushButton"
#include "headers/player.h"

class Block : public QAbstractButton
{
    Q_OBJECT
    QString name;

public:
    const QString &getName() const;

private:
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
const int RGBColor[9]={0xDC143C,0x800080,0x0000CD,0x228B22,0x808000,0xEEE8AA,0x8B4513,0xFF4500,0x696969};

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
