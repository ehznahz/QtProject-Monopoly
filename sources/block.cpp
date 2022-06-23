#include "headers/block.h"

Block::Block(std::string __name, std::string __action, std::string __type, int __color, int __price0, int __price1, int __price2) {
    name = __name;
    action = __action;
    type = __type;
    color = __color;
    price[0] = __price0;
    price[1] = __price1;
    price[2] = __price2;
    owner = -1;
    mortgaged = false;
    united = false;
    house = 0;
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
    return color;
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
