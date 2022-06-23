#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
    std::string name;
    double lucky_rate;
    double escape_rate;
    double rent_rate;
    double build_rate;
    int money;
    int location;
    bool get[40];
    int active;
    bool alive;
public:
    Player(std::string = "\0", int = 0, double = 0, double = 0, double = 0, double = 0);
    void Move(int);
    void Buy(int);
    void Earn(int);
    void Imprison();
    void Bankrupt();
    double LuckyRate() const;
    double EscapeRate() const;
    double RentRate() const;
    double BuildRate() const;
    int Money() const;
    int Location() const;
    bool Active() const;
    bool Alive() const;
};
#endif
