#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "QObject"
#include "headers/playersymbol.h"
class Player : public QObject
{
    Q_OBJECT
    QString name;
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
    Player(int, QString, int, double, double, double, double);
    void Move(int);
    void Buy(int);
    void Abandon(int);
    void Earn(int);
    void Imprison();
    void Wait();
    void Bankrupt();
    double LuckyRate() const;
    double EscapeRate() const;
    double RentRate() const;
    double BuildRate() const;
    int Money() const;
    int Location() const;
    int Active() const;
    bool Alive() const;
    void setLuckyRate(double luckyRate);
    void setEscapeRate(double escapeRate);
    void setRentRate(double rentRate);
    void setBuildRate(double buildRate);
    playerSymbol symbol;
    const QString &getName() const;

signals:
    void moneyChanged();
};
#endif
