#include "headers/mainloop.h"

#include <ctime>
#include <cstdlib>
#include <utility>
#include "QPainter"
#include "headers/dice.h"
#include "headers/stylizedbutton.h"
#include "QEventLoop"
#include "QVBoxLayout"
#include "headers/cardview.h"

mainloop::mainloop(QWidget *parent): QWidget(parent) {
    this->setFixedSize(1600,900);
    this->move(0,0);
    map.setParent(this);
    map.move(200,20);
    map.show();
    dice = new Dice();
    dice->setParent(this);
    dice->move(520,280);
    dice->show();
    stylizedButton* quitBtn = new stylizedButton("quit",60,30);
    quitBtn->setParent(this);
    quitBtn->move(300,250);
    quitBtn->show();
    connect(quitBtn,&stylizedButton::pressed,this,[=]{
        emit Quit();
    });
}
void mainloop::reset(QList<Player *> _player, int playerCount, int _roundLimit, bool _pointEnabled) {
    for(int i=0;i<playerCount;++i){
        map.player[i]=_player[i];
        map.player[i]->symbol.setParent(&map);
        map.player[i]->symbol.hide();
        map.player[i]->symbol.setDirection(1);
        ((CardLayout*)(map.block[0]->layout()))->addWidget(&(map.player[i]->symbol));
        map.player[i]->symbol.show();
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
    int current = -2;

    //初始化地块按钮
    //测试用

    for(int i = 0; i < 40; ++i) map.block[i]->Buy(0), map.player[0]->Buy(i);
    for (int i = 0; i < 40; ++i) {
        connect(map.block[i], &Block::clicked, this, [=, &current]() {
            qDebug() << "why?" << current;
            QWidget* pop = new QWidget();
            pop->setObjectName("quitWidget");
            pop->setStyleSheet("QWidget#quitWidget{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}");
            pop->setParent(this->parentWidget());
            pop->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
            pop->setFixedSize(1600, 900);
            pop->move(0, 0);
            pop->show();

            stylizedButton* close = new stylizedButton("返回", 200, 50);
            close->setParent(pop);
            close->move(0, 0);
            close->show();
            connect(close, &stylizedButton::clicked, this, [=]() {
                pop->close();
            });

            stylizedButton* mortgage = new stylizedButton("抵押", 200, 50);
            mortgage->setParent(pop);
            mortgage->move(900, 650);
            mortgage->show();
            if(map.block[i]->Owner() != current) mortgage->setDisabled(true);
            else if(map.block[i]->Mortgaged()) mortgage->setDisabled(true);
            else if(map.block[i]->House() > 0) mortgage->setDisabled(true);
            else mortgage->setEnabled(true);
            connect(mortgage, &stylizedButton::clicked, this, [=]() {
                qDebug() << "111";
                map.Mortgage(current, i);
                pop->close();
            });

            stylizedButton* redeem = new stylizedButton("赎回", 200, 50);
            redeem->setParent(pop);
            redeem->move(500, 650);
            redeem->show();
            if(map.block[i]->Owner() != current) redeem->setDisabled(true);
            else if(!map.block[i]->Mortgaged()) redeem->setDisabled(true);
            else redeem->setEnabled(true);
            connect(redeem, &stylizedButton::clicked, this, [=]() {
                map.Redeem(current, i);
                pop->close();
            });

            stylizedButton* buy = new stylizedButton("买房", 200, 50);
            buy->setParent(pop);
            buy->move(500, 750);
            buy->show();
            if(map.block[i]->Type() != "Property") buy->setDisabled(true);
            else if(map.block[i]->Owner() != current) buy->setDisabled(true);
            else if(!map.block[i]->United()) buy->setDisabled(true);
            else if(map.block[i]->Mortgaged()) buy->setDisabled(true);
            else if(map.block[i]->House() == 5) buy->setDisabled(true);
            else buy->setEnabled(true);
            connect(buy, &stylizedButton::clicked, this, [=]() {
                map.Build(current, i);
                pop->close();
            });

            stylizedButton* sell = new stylizedButton("卖房", 200, 50);
            sell->setParent(pop);
            sell->move(900, 750);
            sell->show();
            if(map.block[i]->Type() != "Property") sell->setDisabled(true);
            else if(map.block[i]->Owner() != current) sell->setDisabled(true);
            else if(!map.block[i]->United()) sell->setDisabled(true);
            else if(map.block[i]->Mortgaged()) sell->setDisabled(true);
            else if(map.block[i]->House() == 0) sell->setDisabled(true);
            else sell->setEnabled(true);
            connect(sell, &stylizedButton::clicked, this, [=]() {
                map.Sell(current, i);
                pop->close();
            });

            QLabel *text = new QLabel();
            text->setParent(pop);
            if(map.block[i]->Type() == "Property") {
                text->setText(  QString("基本信息\n")
                                + "地块名称：" + map.block[i]->Name() + "\n"
                                + map.block[i]->Action() + "\n"
                                + "地租\n"
                                + "拥有该地块：￥" + QString::number(map.block[i]->Price2()) + "\n"
                                + "拥有整片同色地块：￥" + QString::number(map.block[i]->Price2() * 2) + "\n"
                                + "拥有 1 座房：￥" + QString::number(map.block[i]->Price2() * 4) + "\n"
                                + "拥有 2 座房：￥" + QString::number(map.block[i]->Price2() * 12) + "\n"
                                + "拥有 3 座房：￥" + QString::number(map.block[i]->Price2() * 28) + "\n"
                                + "拥有 4 座房：￥" + QString::number(map.block[i]->Price2() * 34) + "\n"
                                + "拥有 5 座房：￥" + QString::number(map.block[i]->Price2() * 40) + "\n"
                                + "买房：￥" + QString::number(map.block[i]->Price1()) + "    卖房：￥" + QString::number(map.block[i]->Price1() / 2) + "\n"
                                + "抵押：￥" + QString::number(int(map.block[i]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[i]->Price0() * 0.55)) + "\n"
                              );
            }
            else if(map.block[i]->Type() == "Railroad") {
                text->setText(  QString("基本信息\n")
                                + "地块名称：" + map.block[i]->Name() + "\n"
                                + map.block[i]->Action() + "\n"
                                + "地租\n"
                                + "拥有 1 个地铁站：￥25\n"
                                + "拥有 2 个地铁站：￥50\n"
                                + "拥有 3 个地铁站：￥100\n"
                                + "拥有 4 个地铁站：￥200\n"
                                + "抵押：￥" + QString::number(int(map.block[i]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[i]->Price0() * 0.55)) + "\n"
                              );
            }
            else if(map.block[i]->Type() == "Utility") {
                text->setText(  QString("基本信息\n")
                                + "地块名称：" + map.block[i]->Name() + "\n"
                                + map.block[i]->Action() + "\n"
                                + "地租\n"
                                + "拥有 1 个公共设施：￥骰子点数 * 4\n"
                                + "拥有 2 个公共设施：￥骰子点数 * 10\n"
                                + "抵押：￥" + QString::number(int(map.block[i]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[i]->Price0() * 0.55)) + "\n"
                              );
            }
            else {
                text->setText(  QString("基本信息\n")
                                + "地块名称：" + map.block[i]->Name() + "\n"
                                + map.block[i]->Action() + "\n"
                                );
            }
            text->setFont(QFont("Noto Sans SC", 25, 700));
            text->setGeometry(500, 25, 600, 675);
            text->setAlignment(Qt::AlignCenter);
            text->setStyleSheet("QLabel{color:white;}");
            text->show();
        });
    }
    srand(time(0) + clock());
    //决定起家
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
                Btn->move(500, 250);
                Btn->show();
                connect(Btn, &stylizedButton::pressed, this, [=, &key]() {
                    Btn->setDisabled(true);
                    dice->show();
                    key = dice->roll();
                    el->exit();
                });
                el->exec();
                delete Btn;

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
        QEventLoop* el = new QEventLoop;
        if(map.player[current]->Active() < 0) {
            stylizedButton* BtnA = new stylizedButton("支付 $50 直接出小黑屋", 250, 30);
            BtnA->setParent(this);
            BtnA->move(300, 200);
            BtnA->show();
            stylizedButton* BtnB = new stylizedButton("继续待着", 250, 30);
            BtnB->setParent(this);
            BtnB->move(700, 200);
            BtnB->show();
            connect(BtnA, &stylizedButton::pressed, this, [=]() {
                for(; map.player[current]->Active() < 0; map.player[current]->Wait());
                el->exit();
            });
            connect(BtnB, &stylizedButton::pressed, this, [=]() {
                map.player[current]->Wait();
                el->exit();
            });
            el->exec();
            delete BtnA;
            delete BtnB;
            continue;
        }
        int key, px, py;

        stylizedButton* BtnA = new stylizedButton("掷骰子", 100, 30);
        BtnA->setParent(this);
        BtnA->move(500, 250);
        BtnA->show();
        connect(BtnA, &stylizedButton::pressed, this, [=, &key]() {
            BtnA->setDisabled(true);
            dice->show();
            key = dice->roll();
            el->exit();
        });
        el->exec();
        delete BtnA;

        px = key / 10, py = key % 10;
        map.Move(current, px + py);


        stylizedButton* BtnB = new stylizedButton("结束回合", 100, 30);
        BtnB->setParent(this);
        BtnB->move(500, 250);
        BtnB->show();
        connect(BtnB, &stylizedButton::pressed, this, [=]() {
            BtnB->setDisabled(true);
            el->exit();
        });
        el->exec();
        connect(this, &mainloop::Quit, this, [=, &quittag]() {
           quittag = true;
        });
        delete BtnB;
    }
}
