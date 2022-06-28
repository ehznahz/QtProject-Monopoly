#include "headers/mainloop.h"

#include <utility>
#include "QPainter"
#include "headers/dice.h"
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
    /*
    stylizedButton* diceBtn = new stylizedButton("roll",30,30);
    dice->show();
    diceBtn->setParent(this);
    diceBtn->move(500,280);
    connect(diceBtn,&stylizedButton::pressed,this,[=]{
        qDebug()<<dice->roll();
    });
    */
    stylizedButton* quitBtn = new stylizedButton("quit",30,30);
    dice->show();
    quitBtn->setParent(this);
    quitBtn->move(300,280);
    connect(quitBtn,&stylizedButton::pressed,this,[=]{
        emit Quit();
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
                int key;

                QEventLoop* el = new QEventLoop;
                stylizedButton* Btn = new stylizedButton("掷骰子", 100, 30);
                Btn->setParent(this);
                Btn->move(500, 280);
                Btn->show();
                connect(Btn, &stylizedButton::pressed, this, [=, &key]() {
                    dice->show();
                    key = dice->roll();
                    el->exit();
                });
                el->exec();

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
    for(bool quittag = false; !quittag; current = (current + 1) % map.playerNumber) {
        if(!map.player[current]->Alive()) continue;
        int key, px, py;
        QEventLoop* el = new QEventLoop;

        stylizedButton* BtnA = new stylizedButton("掷骰子", 100, 30);
        BtnA->setParent(this);
        BtnA->move(500, 280);
        connect(BtnA, &stylizedButton::pressed, this, [=, &key]() {
            dice->show();
            key = dice->roll();
            el->exit();
        });
        el->exec();


        px = key / 10, py = key % 10;
        map.Move(current, px + py);


        stylizedButton* BtnB = new stylizedButton("结束回合", 100, 30);
        BtnB->setParent(this);
        BtnB->move(500, 280);
        connect(BtnB, &stylizedButton::pressed, this, [=]() {
            el->exit();
        });
        el->exec();
        connect(this, &mainloop::Quit, this, [=, &quittag]() {
           quittag = true;
        });
    }
}
