#include "headers/player.h"

Player::Player(int __color,QString __name, int __money, double __lucky_rate, double __escape_rate, double __rent_rate, double __build_rate): symbol(__color,0,45,45){
    name = __name;
    lucky_rate = __lucky_rate;
    escape_rate = __escape_rate;
    rent_rate = __rent_rate;
    build_rate = __build_rate;
    money = __money;
    location = 0;
    for(int i = 0; i < 40; i++) get[i] = false;
    alive = true;
}

void Player::Move(int __step) {
    location = (location + __step) % 40;
}

void Player::Buy(int __block) {
    get[__block] = true;
}

void Player::Earn(int __money) {
    money += __money;
}

void Player::Imprison() {
    active = -2;
}

void Player::Bankrupt() {
    money = 0;
    for(int i = 0; i < 40; ++i) get[i] = false;
    alive = false;
}

double Player::LuckyRate() const {
    return lucky_rate;
}

double Player::EscapeRate() const {
    return escape_rate;
}

double Player::RentRate() const {
    return rent_rate;
}

double Player::BuildRate() const {
    return build_rate;
}

int Player::Money() const {
    return money;
}

int Player::Location() const {
    return location;
}

bool Player::Active() const {
    return active >= 0;
}

bool Player::Alive() const {
    return alive;
}
