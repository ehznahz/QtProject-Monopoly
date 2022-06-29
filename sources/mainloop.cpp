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
#include "QSlider"
#include "set"

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
    Block::players = &map.player[0];
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
    //
    //map.player[0]->Earn(-1600);
    //初始化地块按钮
    for (int i = 0; i < 40; ++i) {
        connect(map.block[i], &Block::clicked, this, [=, &current]() {
            QWidget* pop = new QWidget();
            pop->setObjectName("informWidget");
            pop->setStyleSheet("QWidget#informWidget{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}");
            pop->setParent(this->parentWidget());
            pop->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
            pop->setFixedSize(1600, 900);
            pop->move(0, 0);
            pop->show();
            QGridLayout* qLayout = new QGridLayout;
            qLayout->setContentsMargins(300,100,300,100);
            qLayout->setAlignment(Qt::AlignCenter);
            pop->setLayout(qLayout);
            QWidget* textView=new QWidget;
            textView->setLayout(new QVBoxLayout);
            QLabel *text = new QLabel();
            QLabel *title = new QLabel("基本信息");
            title->setFont(QFont("Noto Sans SC", 22, 700));
            title->setAlignment(Qt::AlignCenter);
            title->setStyleSheet("QLabel{color:white;}");
            textView->layout()->addWidget(title);
            text->setParent(pop);
            if(map.block[i]->Type() == "Property") {
                text->setText( "地块名称：" + map.block[i]->Name() + "\n"
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
                              + "抵押：￥" + QString::number(int(map.block[i]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[i]->Price0() * 0.55))
                );
            }
            else if(map.block[i]->Type() == "Railroad") {
                text->setText(  "地块名称：" + map.block[i]->Name() + "\n"
                              + map.block[i]->Action() + "\n"
                              + "地租\n"
                              + "拥有 1 个地铁站：￥25\n"
                              + "拥有 2 个地铁站：￥50\n"
                              + "拥有 3 个地铁站：￥100\n"
                              + "拥有 4 个地铁站：￥200\n"
                              + "抵押：￥" + QString::number(int(map.block[i]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[i]->Price0() * 0.55))
                );
            }
            else if(map.block[i]->Type() == "Utility") {
                text->setText(  "地块名称：" + map.block[i]->Name() + "\n"
                              + map.block[i]->Action() + "\n"
                              + "地租\n"
                              + "拥有 1 个公共设施：￥骰子点数 * 4\n"
                              + "拥有 2 个公共设施：￥骰子点数 * 10\n"
                              + "抵押：￥" + QString::number(int(map.block[i]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[i]->Price0() * 0.55))
                );
            }
            else {
                text->setText( "地块名称：" + map.block[i]->Name() + "\n"
                              + map.block[i]->Action()
                );
            }
            text->setFont(QFont("Noto Sans SC", 16, 500));
            text->setMargin(10);
            text->setAlignment(Qt::AlignCenter);
            text->setStyleSheet("QLabel{color:white;}");
            textView->layout()->addWidget(text);
            qLayout->addWidget(textView,0,0,1,2);
            textView->setStyleSheet("border:2px solid white");

            stylizedButton* close = new stylizedButton("返回", 200, 50);
            close->setParent(pop);
            close->move(0, 0);
            close->show();
            connect(close, &stylizedButton::clicked, this, [=]() {
                pop->close();
            });

            stylizedButton* mortgage = new stylizedButton("抵押", 200, 50);
            qLayout->addWidget(mortgage,2,1,1,1);
            mortgage->show();
            if(map.block[i]->Owner() != current) mortgage->setDisabled(true);
            else if(map.block[i]->Mortgaged()) mortgage->setDisabled(true);
            else if(map.block[i]->House() > 0) mortgage->setDisabled(true);
            else mortgage->setEnabled(true);
            connect(mortgage, &stylizedButton::clicked, this, [=]() {
                map.Mortgage(current, i);
                pop->close();
            });

            stylizedButton* redeem = new stylizedButton("赎回", 200, 50);
            qLayout->addWidget(redeem,2,0,1,1);
            redeem->show();
            if(map.block[i]->Owner() != current) redeem->setDisabled(true);
            else if(!map.block[i]->Mortgaged()) redeem->setDisabled(true);
            else redeem->setEnabled(true);
            connect(redeem, &stylizedButton::clicked, this, [=]() {
                map.Redeem(current, i);
                pop->close();
            });

            stylizedButton* buy = new stylizedButton("买房", 200, 50);
            qLayout->addWidget(buy,3,0,1,1);
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
            qLayout->addWidget(sell,3,1,1,1);
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
        });
    }
    srand(time(0) + clock());
    stylizedButton* BtnBankrupt = new stylizedButton("破产", 100, 40);
    BtnBankrupt->setParent(this);
    BtnBankrupt->move(1200, 180);
    BtnBankrupt->show();
    stylizedButton* BtnTrading = new stylizedButton("进行交易", 100, 40);
    BtnTrading->setParent(this);
    BtnTrading->move(1200, 280);
    BtnTrading->show();

    connect(BtnBankrupt, &stylizedButton::pressed, this, [=, &current]() {
        QWidget* pop = new QWidget();
        pop->setObjectName("bankruptWidget");
        pop->setStyleSheet("QWidget#bankruptWidget{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}");
        pop->setParent(this->parentWidget());
        pop->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
        pop->setFixedSize(1600,900);
        pop->move(0,0);
        //按钮
        stylizedButton* confirm = new stylizedButton("确定",230,50);
        confirm->setParent(pop);
        confirm->move(pop->width()*0.5+20,550);
        connect(confirm,&stylizedButton::clicked,this,[=]() {
            int loc = map.player[current]->Location();
            if(map.player[current]->Money() >= 0) map.Bankrupt(current, -1);
            else map.Bankrupt(current, map.block[loc]->Owner());
            pop->close();
        });
        stylizedButton* cancel = new stylizedButton("取消",230,50);
        cancel->setParent(pop);
        cancel->move(this->width()*0.5-250,550);
        connect(cancel,&stylizedButton::clicked,pop,[=]() {
            pop->close();
        });
        //文字
        QLabel *text = new QLabel();
        text->setParent(pop);
        text->setText("确定要破产吗?");
        text->setFont(QFont("Noto Sans SC",25,700));
        text->setGeometry(this->width()*0.5-250,this->height()*0.4-25,500,50);
        text->setAlignment(Qt::AlignCenter);
        text->setStyleSheet("QLabel{color:white;}");
        text->show();
        pop->show();

    });
    connect(BtnTrading,&stylizedButton::pressed,this,[&current, this](){
        TradingSelect(current);
    });
    connect(&map, &Map::BuyOrNot, this, &mainloop::Buy);

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
    for(; ; current = (current + 1) % map.playerNumber) {
        if(!map.player[current]->Alive()) continue;
        QEventLoop* el = new QEventLoop;
        if(map.player[current]->Active() < 0) {
            stylizedButton* BtnA = new stylizedButton("支付 ￥50 直接出小黑屋", 250, 30);
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
            delete el;
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

        connect(map.player[current], &Player::moneyChanged, this, [=]() {
            if(map.player[current]->Money() < 0) BtnB->setDisabled(true);
            else BtnB->setEnabled(true);
        });

        if(map.player[current]->Money() < 0) BtnB->setDisabled(true);
        else BtnB->setEnabled(true);

        el->exec();
        delete BtnB;
        delete el;
    }
}
void mainloop::TradingSelect(int currentPlayer) {
    QWidget* tradingView = new QWidget;
    tradingView->setParent(this->parentWidget());
    tradingView->setGeometry(0,0,1600,900);
    tradingView->show();
    tradingView->setObjectName("tradingView");
    tradingView->setStyleSheet("QWidget#tradingView{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}"
                               "QLabel{color:white}");
    QGridLayout* layout = new QGridLayout();
    tradingView->setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(10);
    layout->setContentsMargins(500,200,500,200);
    auto titleT=new QLabel("进行交易");
    titleT->setFont(QFont("Noto Sans SC",20,700));
    layout->addWidget(titleT,0,0,1,2);
    layout->addWidget(new QLabel("请选择一玩家开始交易"),1,0,1,2);
    int cnt=0;
    for (int i = 0; i < map.playerNumber; ++i) {
        if(i==currentPlayer||!map.player[i]->Alive())continue;
        layout->addWidget(new playerSymbol(map.player[i]->symbol.getColor(),0,30,30),(++cnt)+1,0,1,1);
        stylizedButton* btn=new stylizedButton(map.player[i]->getName(),200,35);
        layout->addWidget(btn,cnt+1,1,1,1);
        connect(btn,&stylizedButton::pressed,this,[=](){
            delete tradingView;
            TradingWith(currentPlayer,i);
        });
    }
}

void mainloop::TradingWith(int currentPlayer,int targetPlayer) {
    this->hide();
    QWidget* tradingView = new QWidget;
    tradingView->setParent(this->parentWidget());
    tradingView->setGeometry(0,0,1600,900);
    tradingView->show();
    tradingView->setObjectName("tradingView");
    tradingView->setStyleSheet("QWidget#tradingView{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}"
                               "QLabel{color:white}");
    QGridLayout* layout = new QGridLayout();
    tradingView->setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(10);
    layout->setContentsMargins(500,200,500,200);
    auto titleT=new QLabel("进行交易");
    titleT->setFont(QFont("Noto Sans SC",20,700));
    layout->addWidget(titleT,0,0,1,5);
    layout->addWidget(new playerSymbol(map.player[currentPlayer]->symbol.getColor(),0,30,30),1,0,1,1);
    layout->addWidget(new QLabel(map.player[currentPlayer]->getName()),1,1,1,1);
    layout->addWidget(new playerSymbol(map.player[targetPlayer]->symbol.getColor(),0,30,30),1,3,1,1);
    layout->addWidget(new QLabel(map.player[targetPlayer]->getName()),1,4,1,1);
    auto sliderA=new QSlider(Qt::Orientation::Horizontal);
    sliderA->setRange(0,map.player[currentPlayer]->Money());
    sliderA->setFixedSize(300,15);
    layout->addWidget(sliderA,2,0,1,2);
    auto sliderB=new QSlider(Qt::Orientation::Horizontal);
    sliderB->setRange(0,map.player[targetPlayer]->Money());
    sliderB->setFixedSize(300,15);
    layout->addWidget(sliderB,2,3,1,2);
    layout->addWidget(new QLabel("金钱"),3,0,1,1,Qt::AlignLeft);
    layout->addWidget(new QLabel("金钱"),3,3,1,1,Qt::AlignLeft);
    auto labelV1 = new QLabel(QString::number(sliderA->value()));
    connect(sliderA,&QSlider::valueChanged,this,[=](int v){
        labelV1->setNum(v);
    });
    layout->addWidget(labelV1,3,1,1,1,Qt::AlignRight);
    auto labelV2 = new QLabel(QString::number(sliderB->value()));
    connect(sliderB,&QSlider::valueChanged,this,[=](int v){
        labelV2->setNum(v);
    });
    layout->addWidget(labelV2,3,4,1,1,Qt::AlignRight);
    std::set<int>* cityA=new std::set<int>;
    std::set<int>* cityB=new std::set<int>;
    auto qWidgetA = new QWidget();
    qWidgetA->setFixedWidth(300);
    layout->addWidget(qWidgetA,4,0,1,2);
    qWidgetA->setLayout(new QVBoxLayout);
    for (int i = 0; i < 40; ++i) {
        if(map.block[i]->Owner()==currentPlayer&&!map.block[i]->Mortgaged()&&map.block[i]->House()==0){
            if(map.block[i]->United()){
                bool fail= false;
                for (int j = 0; j < 40; ++j) {
                    if(map.block[j]->House()!=0&&map.block[i]->Color()==map.block[j]->Color()){
                        fail= true;
                        break;
                    }
                }
                if(fail)continue;
            }
            auto btnN = new stylizedButton(map.block[i]->getName(),280,40);
            qWidgetA->layout()->addWidget(btnN);
            btnN->setCheckable(true);
            connect(btnN,&stylizedButton::toggled,this,[=](bool checked){
                if(checked)cityA->insert(i);
                else cityA->erase(i);
            });
        }
    }
    auto qWidgetB = new QWidget();
    qWidgetB->setFixedWidth(300);
    layout->addWidget(qWidgetB,4,3,1,2);
    qWidgetB->setLayout(new QVBoxLayout);
    for (int i = 0; i < 40; ++i) {
        if(map.block[i]->Owner()==targetPlayer&&!map.block[i]->Mortgaged()&&map.block[i]->House()==0){
            if(map.block[i]->United()){
                bool fail= false;
                for (int j = 0; j < 40; ++j) {
                    if(map.block[j]->House()!=0&&map.block[i]->Color()==map.block[j]->Color()){
                        fail= true;
                        break;
                    }
                }
                if(fail)continue;
            }
            auto btnN = new stylizedButton(map.block[i]->getName(),280,40);
            qWidgetB->layout()->addWidget(btnN);
            btnN->setCheckable(true);
            connect(btnN,&stylizedButton::toggled,this,[=](bool checked){
                if(checked)cityB->insert(i);
                else cityB->erase(i);
            });
        }
    }
    this->repaint();
    tradingView->update();
    stylizedButton* confirm = new stylizedButton("发起交易",300,50);
    layout->addWidget(confirm,5,3,1,2);
    stylizedButton* cancel = new stylizedButton("取消交易",300,50);
    layout->addWidget(cancel,5,0,1,2);
    connect(cancel,&stylizedButton::pressed,this,[=](){
        delete tradingView;
        this->show();
    });
    connect(confirm,&stylizedButton::pressed,this,[=](){
        sliderA->setDisabled(true);
        sliderB->setDisabled(true);
        qWidgetA->setDisabled(true);
        qWidgetB->setDisabled(true);
        delete confirm;
        cancel->setText("拒绝交易");
        stylizedButton* accept = new stylizedButton("接受交易",300,50);
        layout->addWidget(accept,5,3,1,2);
        connect(accept,&stylizedButton::pressed,this,[=](){
            map.player[currentPlayer]->Earn(-sliderA->value()+sliderB->value());
            map.player[targetPlayer]->Earn(-sliderB->value()+sliderA->value());
            for(auto i:*cityA){
                map.player[currentPlayer]->Abandon(i);
                map.player[targetPlayer]->Buy(i);
                map.block[i]->Buy(targetPlayer);
            }
            for(auto i:*cityB){
                map.player[targetPlayer]->Abandon(i);
                map.player[currentPlayer]->Buy(i);
                map.block[i]->Buy(currentPlayer);
            }
            map.Update();
            delete tradingView;
            this->show();
        });
    });
}

void mainloop::Buy(int currentPlayer,int loc) {
    QEventLoop* waitHere = new QEventLoop();
    QTimer* timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, waitHere,&QEventLoop::quit);
    timer->start(500);
    waitHere->exec();
    timer->stop();
    QWidget *pop = new QWidget();
    pop->setObjectName("buyWidget");
    pop->setStyleSheet("QWidget#buyWidget{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}");
    pop->setParent(this->parentWidget());
    pop->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    pop->setFixedSize(1600, 900);
    pop->move(0, 0);
    pop->show();
    QGridLayout *qLayout = new QGridLayout;
    qLayout->setContentsMargins(300, 100, 300, 100);
    qLayout->setAlignment(Qt::AlignCenter);
    pop->setLayout(qLayout);
    QWidget *textView = new QWidget;
    textView->setLayout(new QVBoxLayout);
    QLabel *text = new QLabel();
    QLabel *title = new QLabel("基本信息");
    title->setFont(QFont("Noto Sans SC", 22, 700));
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel{color:white;}");
    textView->layout()->addWidget(title);
    text->setParent(pop);
    if (map.block[loc]->Type() == "Property") {
        text->setText("地块名称：" + map.block[loc]->Name() + "\n" + map.block[loc]->Action() + "\n" + "地租\n" + "拥有该地块：￥" + QString::number(map.block[loc]->Price2()) + "\n" + "拥有整片同色地块：￥" + QString::number(map.block[loc]->Price2() * 2) + "\n" + "拥有 1 座房：￥" + QString::number(map.block[loc]->Price2() * 4) + "\n" + "拥有 2 座房：￥" + QString::number(map.block[loc]->Price2() * 12) + "\n" + "拥有 3 座房：￥" + QString::number(map.block[loc]->Price2() * 28) + "\n" + "拥有 4 座房：￥" + QString::number(map.block[loc]->Price2() * 34) + "\n" + "拥有 5 座房：￥" + QString::number(map.block[loc]->Price2() * 40) + "\n" + "买房：￥" + QString::number(map.block[loc]->Price1()) + "    卖房：￥" + QString::number(map.block[loc]->Price1() / 2) + "\n" + "抵押：￥" + QString::number(int(map.block[loc]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[loc]->Price0() * 0.55)) );
    } else if (map.block[loc]->Type() == "Railroad") {
        text->setText("地块名称：" + map.block[loc]->Name() + "\n" + map.block[loc]->Action() + "\n" + "地租\n" + "拥有 1 个地铁站：￥25\n" + "拥有 2 个地铁站：￥50\n" + "拥有 3 个地铁站：￥100\n" + "拥有 4 个地铁站：￥200\n" + "抵押：￥" + QString::number(int(map.block[loc]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[loc]->Price0() * 0.55)));
    } else if (map.block[loc]->Type() == "Utility") {
        text->setText("地块名称：" + map.block[loc]->Name() + "\n" + map.block[loc]->Action() + "\n" + "地租\n" + "拥有 1 个公共设施：￥骰子点数 * 4\n" + "拥有 2 个公共设施：￥骰子点数 * 10\n" + "抵押：￥" + QString::number(int(map.block[loc]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[loc]->Price0() * 0.55)));
    } else {
        text->setText("地块名称：" + map.block[loc]->Name() + "\n" + map.block[loc]->Action() );
    }
    text->setMargin(10);
    text->setFont(QFont("Noto Sans SC", 16, 500));
    text->setAlignment(Qt::AlignCenter);
    text->setStyleSheet("QLabel{color:white;}");
    textView->layout()->addWidget(text);
    qLayout->addWidget(textView, 0, 0, 1, 2);
    textView->setStyleSheet("border:2px solid white");

    stylizedButton *buy = new stylizedButton("购买", 200, 50);
    qLayout->addWidget(buy, 2, 1, 1, 1);
    buy->show();
    if (!map.block[loc]->Price0()) buy->setDisabled(true);
    else if (map.block[loc]->Owner() != -1)
        buy->setDisabled(true);
    else
        buy->setEnabled(true);
    connect(buy, &stylizedButton::clicked, this, [=]() {
        map.Buy(currentPlayer, loc);
        pop->close();
    });

    stylizedButton *back = new stylizedButton("返回", 200, 50);
    qLayout->addWidget(back, 2, 0, 1, 1);
    back->show();
    connect(back, &stylizedButton::clicked, this, [=]() {
        pop->close();
    });
}
