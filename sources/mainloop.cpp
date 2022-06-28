#include "headers/mainloop.h"

#include <utility>
#include "QPainter"
#include "headers/Dice.h"
#include "headers/stylizedbutton.h"
#include "QEventLoop"

mainloop::mainloop(QWidget *parent): QWidget(parent) {
    this->setFixedSize(1600,900);
    this->move(0,0);
    map.setParent(this);
    map.move(200,20);
    map.show();
    //map.setAutoFillBackground(true);
    dice = new Dice();
    dice->setParent(this);
    dice->move(520,280);
    dice->show();
    stylizedButton* diceBtn= new stylizedButton("roll",30,30);
    dice->show();
    diceBtn->setParent(this);
    diceBtn->move(500,280);
    connect(diceBtn,&stylizedButton::pressed,[=]{
        qDebug()<<dice->roll();
    });
}
void mainloop::reset(QList<Player *> _player, int playerCount, int _roundLimit, bool _pointEnabled) {
    for(int i=0;i<playerCount;++i){
        map.player[i]=_player[i];
        map.player[i]->symbol.setParent(&map);
        map.player[i]->symbol.hide();
    }
    map.playerNumber=playerCount;
    roundLimit = _roundLimit;
    pointEnabled = _pointEnabled;
    //TODO display
}

void mainloop::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap bk("://resources/image/background-noIcon.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), bk);
}

void mainloop::gamestart() {
    //决定起家
    int current = 0;
    {
        bool winner[6] = {1, 1, 1, 1, 1, 1};
        int weight[6] = {0, 0, 0, 0, 0, 0};
        for(int existplayer = map.playerNumber; existplayer > 1; ) {
            int maxnum = 0;
            for(int i = 0; i < map.playerNumber; ++i) if(winner[i]) {
                int key = map.player[i]->Roll();
                weight[i] = key / 10 + key % 10;
                if(weight[i] > maxnum) maxnum = weight[i];
            }
            for(int i = 0; i < map.playerNumber; ++i) if(winner[i] && weight[i] < maxnum) {
                winner[i] = 0;
                --existplayer;
            }
        }
        for(int i = 0; i < map.playerNumber; ++i) if(winner[i]) current = i;
    }
    for(; ; current = (current + 1) % map.playerNumber) {
        QEventLoop* el = new QEventLoop;
        if(!map.player[current]->Alive()) continue;
        connect(this, &mainloop::Continue, this, [=]() {
            el->exit();
        });
        el->exec();
        int key = map.player[current]->Roll();
        int px = key / 10, py = key % 10;
        map.Move(current, px + py);
        connect(this, &mainloop::Continue, this, [=]() {
            el->exit();
        });
        el->exec();
    }
}
