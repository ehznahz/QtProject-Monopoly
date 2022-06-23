#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "headers/player.h"

class Block
{
    std::string name;
    std::string action;
    std::string type;
    int color;
    int price[3]; //地面、房子、租金底价
    int owner;
    bool mortgaged;
    bool united;
    int house;
public:
    Block(std::string = "\0", std::string = "\0", std::string = "\0", int = -1, int = 0, int = 0, int = 0);
    void Buy(int);
    void Mortgage();
    void Redeem();
    void Build();
    void Sell();
    void ChangeUnited(bool);
    std::string Type() const;
    int Color() const;
    int Price0() const;
    int Price1() const;
    int Price2() const;
    int Owner() const;
    int House() const;
};
#endif
