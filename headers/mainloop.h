#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "QWidget"
#include "headers/map.h"
#include "headers/dice.h"

class mainloop : public QWidget
{
    Q_OBJECT
    int roundLimit = 0;
    bool pointEnabled = false;
    Map map;
    Dice* dice;

public:
    explicit mainloop(QWidget* parent = nullptr);
    void reset(QList<Player *> _player, int playerCount, int roundLimit, bool pointEnabled);
    void paintEvent(QPaintEvent*) override;
    void gamestart();

signals:
    void Continue();
};


#endif //MAINLOOP_H
