#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "QWidget"
#include "headers/player.h"
#include "headers/map.h"
class mainloop: public QWidget{
    Q_OBJECT
    int roundLimit=0;
    bool pointEnabled= false;
    Map map;
public:
    explicit mainloop(QWidget* parent= nullptr);
    void reset(QList<Player *> _player, int playerCount, int roundLimit, bool pointEnabled);
    void paintEvent(QPaintEvent*) override;
};


#endif //MAINLOOP_H
