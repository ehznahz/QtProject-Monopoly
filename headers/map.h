#ifndef MAP_H
#define MAP_H

#include "headers/block.h"
class Map : public QWidget
{
    Q_OBJECT
    Block* block[40];
    Player* player[6];
    int playerNumber;

public:
    friend class mainloop;
    Map();
    void Move(int, int);
    void Update();
    void Bankrupt(int, int);
    void Buy(int, int);
    void Mortgage(int, int);
    void Redeem(int, int);
    void Build(int, int);
    void Sell(int, int);

signals:
    void BuyOrNot(int, int);
    void BankruptOrNot(int, int);
};

#endif
