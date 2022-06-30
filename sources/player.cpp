#include "headers/player.h"

Player::Player(int __color, QString __name, int __money, double __lucky_rate, double __escape_rate, double __rent_rate, double __build_rate) : symbol(__color, 0, 35, 35){
	name = __name;
	lucky_rate = __lucky_rate;
	escape_rate = __escape_rate;
	rent_rate = __rent_rate;
	build_rate = __build_rate;
	money = __money;
	location = 0;
	for(int i = 0; i < 40; i++) get[i] = false;
	active = 0;
	alive = true;
}

void Player::Move(int __step){
	location = (location + __step) % 40;
}

void Player::Buy(int __block){
	get[__block] = true;
}

void Player::Abandon(int __block){
	get[__block] = false;
}

void Player::Earn(int __money){
	money += __money;
	emit moneyChanged();
}

void Player::Imprison(){
	active = -2;
}

void Player::Wait(){
	++active;
}

void Player::Bankrupt(){
	money = 0;
	for(int i = 0; i < 40; ++i) get[i] = false;
	active = 0;
	alive = false;
}

double Player::LuckyRate() const{
	return lucky_rate - 1;
}

double Player::EscapeRate() const{
	return escape_rate - 1;
}

double Player::RentRate() const{
	return rent_rate;
}

double Player::BuildRate() const{
	return build_rate;
}

int Player::Money() const{
	return money;
}

int Player::Location() const{
	return location;
}

int Player::Active() const{
	return active;
}

bool Player::Alive() const{
	return alive;
}

const QString &Player::getName() const{
	return name;
}

void Player::setLuckyRate(double luckyRate){
	lucky_rate = luckyRate;
}

void Player::setEscapeRate(double escapeRate){
	escape_rate = escapeRate;
}

void Player::setRentRate(double rentRate){
	rent_rate = rentRate;
}

void Player::setBuildRate(double buildRate){
	build_rate = buildRate;
}
