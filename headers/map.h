#ifndef MAP_H
#define MAP_H

#include "headers/block.h"

class Map
{
    Block block[40];
    Player player[6];
    int playernumber;
public:
    Map();
    void Move(int, int);
    void Roll(int);
    void Update();
    void BuyOrNot(int, int);
    void BankruptOrNot(int);
    void SellOrNot(int);
    void Trade(int, int);
    void Bankrupt(int, int);
    void Buy(int, int);
    void Mortgage(int, int);
    void Redeem(int, int);
    void Build(int, int);
    void Sell(int, int);
    void Game();
};

#endif
