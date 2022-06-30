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
#include "headers/playerview.h"
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
    dice->move(530,320);
    dice->show();
    pView = new playerView();
    pView->setParent(this);
    pView->move(1080,20);
    pView->show();
}
void mainloop::reset(QList<Player *> _player, int playerCount, int _roundLimit, bool _pointEnabled) {
    for(int i=0;i<playerCount;++i){
        map.player[i]=_player[i];
        map.player[i]->symbol.setParent(&map);
        map.player[i]->symbol.hide();
        map.player[i]->symbol.setDirection(1);
        ((CardLayout*)(map.block[0]->layout()))->addWidget(&(map.player[i]->symbol));
        map.player[i]->symbol.show();
        connect(map.player[i],&Player::moneyChanged,pView,[=](){
            pView->updateMoney(i);
        });
    }
    map.playerNumber=playerCount;
    roundLimit = _roundLimit;
    pointEnabled = _pointEnabled;
    //TODO display
    Block::players = &map.player[0];
    pView->init(map.player,playerCount);
    pView->setFocus(0);
}

void mainloop::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap bk("://resources/image/background-noIcon.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), bk);
}

void mainloop::gameStart() {
    int current = 0, existplayer = map.playerNumber;
    //初始化地块按钮
    for (int i = 0; i < 40; ++i) {
        connect(map.block[i], &Block::clicked, this, [=, &current]() {
            blockOp(current,i);
        });
    }
    srand(time(0) + clock());
    stylizedButton* BtnBankrupt = new stylizedButton("破产", 155, 40);
    BtnBankrupt->setParent(this);
    BtnBankrupt->move(1080, 350);
    BtnBankrupt->show();
    stylizedButton* BtnTrading = new stylizedButton("进行交易", 155, 40);
    BtnTrading->setParent(this);
    BtnTrading->move(1245, 350);
    BtnTrading->show();

    connect(BtnBankrupt, &stylizedButton::pressed, this, [=, &current, &existplayer]() {
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
        connect(confirm,&stylizedButton::clicked,this,[=,&existplayer]() {
            int loc = map.player[current]->Location();
            map.Bankrupt(current);
            --existplayer;
            map.block[loc]->layout()->removeWidget(&map.player[current]->symbol);
            map.player[current]->symbol.setParent(nullptr);
            pView->setBankrupt(current);
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

    for(; existplayer > 1; current = (current + 1) % map.playerNumber) {
        if(!map.player[current]->Alive()) continue;
        pView->setFocus(current);
        QEventLoop* el = new QEventLoop;
        if(map.player[current]->Active() < 0) {
            stylizedButton* BtnA = new stylizedButton("支付 ￥50 直接出小黑屋", 250, 40);
            BtnA->setParent(this);
            BtnA->move(505, 450);
            BtnA->show();
            stylizedButton* BtnB = new stylizedButton("继续待着", 250, 40);
            BtnB->setParent(this);
            BtnB->move(505, 500);
            BtnB->show();
            connect(BtnA, &stylizedButton::pressed, this, [=]() {
                for(; map.player[current]->Active() < 0; map.player[current]->Wait());
                pView->setPrison(current, false);
                el->exit();
            });
            connect(BtnB, &stylizedButton::pressed, this, [=]() {
                map.player[current]->Wait();
                if(map.player[current]->Active()>=0)pView->setPrison(current, false);
                el->exit();
            });
            el->exec();
            delete BtnA;
            delete BtnB;
            delete el;
            continue;
        }
        int key, px, py;

        stylizedButton* BtnA = new stylizedButton("掷骰子", 200, 40);
        BtnA->setParent(this);
        BtnA->move(530, 500);
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
        if(map.player[current]->Active()<0){
            pView->setPrison(current, true);
        }

        stylizedButton* BtnB = new stylizedButton("结束回合", 200, 40);
        BtnB->setParent(this);
        BtnB->move(530, 500);
        BtnB->show();
        connect(BtnB, &stylizedButton::pressed, this, [=]() {
            if(map.player[current]->Money() < 0) return;
            BtnB->setDisabled(true);
            el->exit();
        });

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
    layout->setContentsMargins(500,100,500,100);
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
            if(!cityA->empty())
                for(auto i:*cityA){
                    map.player[currentPlayer]->Abandon(i);
                    map.player[targetPlayer]->Buy(i);
                    map.block[i]->Buy(targetPlayer);
                }
            if(!cityB->empty())
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

void mainloop::blockOp(int current, int _block) {
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
    if(map.block[_block]->Type() == "Property") {
        text->setText( "地块名称：" + map.block[_block]->Name() + "\n"
                      + map.block[_block]->Action() + "\n"
                      + "地租\n"
                      + "拥有该地块：￥" + QString::number(map.block[_block]->Price2()) + "\n"
                      + "拥有整片同色地块：￥" + QString::number(map.block[_block]->Price2() * 2) + "\n"
                      + "拥有 1 座房：￥" + QString::number(map.block[_block]->Price2() * 4) + "\n"
                      + "拥有 2 座房：￥" + QString::number(map.block[_block]->Price2() * 12) + "\n"
                      + "拥有 3 座房：￥" + QString::number(map.block[_block]->Price2() * 28) + "\n"
                      + "拥有 4 座房：￥" + QString::number(map.block[_block]->Price2() * 34) + "\n"
                      + "拥有 5 座房：￥" + QString::number(map.block[_block]->Price2() * 40) + "\n"
                      + "买房：￥" + QString::number(map.block[_block]->Price1()) + "    卖房：￥" + QString::number(map.block[_block]->Price1() / 2) + "\n"
                      + "抵押：￥" + QString::number(int(map.block[_block]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[_block]->Price0() * 0.55))
        );
    }
    else if(map.block[_block]->Type() == "Railroad") {
        text->setText(  "地块名称：" + map.block[_block]->Name() + "\n"
                      + map.block[_block]->Action() + "\n"
                      + "地租\n"
                      + "拥有 1 个地铁站：￥25\n"
                      + "拥有 2 个地铁站：￥50\n"
                      + "拥有 3 个地铁站：￥100\n"
                      + "拥有 4 个地铁站：￥200\n"
                      + "抵押：￥" + QString::number(int(map.block[_block]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[_block]->Price0() * 0.55))
        );
    }
    else if(map.block[_block]->Type() == "Utility") {
        text->setText(  "地块名称：" + map.block[_block]->Name() + "\n"
                      + map.block[_block]->Action() + "\n"
                      + "地租\n"
                      + "拥有 1 个公共设施：￥骰子点数 * 4\n"
                      + "拥有 2 个公共设施：￥骰子点数 * 10\n"
                      + "抵押：￥" + QString::number(int(map.block[_block]->Price0() * 0.5)) + "    赎回：￥" + QString::number(int(map.block[_block]->Price0() * 0.55))
        );
    }
    else {
        text->setText( "地块名称：" + map.block[_block]->Name() + "\n"
                      + map.block[_block]->Action()
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
    close->move(1300, 800);
    close->show();
    connect(close, &stylizedButton::clicked, this, [=]() {
        pop->close();
    });

    stylizedButton* mortgage = new stylizedButton("抵押", 200, 50);
    qLayout->addWidget(mortgage,2,1,1,1);
    mortgage->show();
    if(map.block[_block]->Owner() != current) mortgage->setDisabled(true);
    else if(map.block[_block]->Mortgaged()) mortgage->setDisabled(true);
    else if(map.block[_block]->House() > 0) mortgage->setDisabled(true);
    else mortgage->setEnabled(true);
    connect(mortgage, &stylizedButton::clicked, this, [=]() {
        map.Mortgage(current, _block);
        pop->close();
    });

    stylizedButton* redeem = new stylizedButton("赎回", 200, 50);
    qLayout->addWidget(redeem,2,0,1,1);
    redeem->show();
    if(map.block[_block]->Owner() != current) redeem->setDisabled(true);
    else if(!map.block[_block]->Mortgaged()) redeem->setDisabled(true);
    else redeem->setEnabled(true);
    connect(redeem, &stylizedButton::clicked, this, [=]() {
        map.Redeem(current, _block);
        pop->close();
    });

    stylizedButton* buy = new stylizedButton("买房", 200, 50);
    qLayout->addWidget(buy,3,0,1,1);
    buy->show();
    if(map.block[_block]->Type() != "Property") buy->setDisabled(true), qDebug() << "000";
    else if(map.block[_block]->Owner() != current) buy->setDisabled(true), qDebug() << "111";
    else if(!map.block[_block]->United()) buy->setDisabled(true), qDebug() << "222";
    else if(map.block[_block]->Mortgaged()) buy->setDisabled(true), qDebug() << "333";
    else if(map.block[_block]->House() == 5) buy->setDisabled(true), qDebug() << "444";
    else buy->setEnabled(true), qDebug() << "555";
    connect(buy, &stylizedButton::clicked, this, [=]() {
        map.Build(current, _block);
        pop->close();
    });

    stylizedButton* sell = new stylizedButton("卖房", 200, 50);
    qLayout->addWidget(sell,3,1,1,1);
    sell->show();
    if(map.block[_block]->Type() != "Property") sell->setDisabled(true);
    else if(map.block[_block]->Owner() != current) sell->setDisabled(true);
    else if(!map.block[_block]->United()) sell->setDisabled(true);
    else if(map.block[_block]->Mortgaged()) sell->setDisabled(true);
    else if(map.block[_block]->House() == 0) sell->setDisabled(true);
    else sell->setEnabled(true);
    connect(sell, &stylizedButton::clicked, this, [=]() {
        map.Sell(current, _block);
        pop->close();
    });
}
