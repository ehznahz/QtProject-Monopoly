#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "QWidget"
#include "headers/map.h"
#include "headers/dice.h"
#include "headers/playerview.h"
#include "headers/eventview.h"
class mainloop : public QWidget
{
    Q_OBJECT
    int roundLimit = 0;
    bool pointEnabled = false;
    Map map;
    Dice* dice;
    playerView* pView;
    eventView* eView;
public:
    explicit mainloop(QWidget* parent = nullptr);
    void reset(QList<Player *> _player, int playerCount, int roundLimit, bool pointEnabled);
    void paintEvent(QPaintEvent*) override;
    void gameStart();
    void TradingSelect(int currentPlayer);
    void TradingWith(int currentPlayer,int targetPlayer);
    void blockOp(int current,int _block);

signals:
    void Quit();

public slots:
    void Buy(int currentPlayer,int loc);
};


#endif //MAINLOOP_H
