#include "headers/gameinitial.h"
#include "QFrame"
#include "QLabel"
#include "QLayout"
#include "QLineEdit"
#include "QPainter"
#include "QWidget"
#include "headers/playersymbol.h"
#include "headers/stylizedbutton.h"
#include "map"
#include "headers/stylizedspinbox.h"
#include "headers/player.h"

std::map<int, bool> availableColor = {
        {0x9a2b2e, false},
        {0xfbc85f, false},
        {0xf96815, false},
        {0xc0428a, false},
        {0x207349, false},
        {0x96d8de, false},
        {0x325b74, false},
        {0x726a4e, false},
        {0x788f74, false},
        {0x76c1b2, false},
        {0xf3774d, false},
        {0xf8de8d, false},
        {0xc5aecf, false}
};
QString defaultName[6] = {"Alice", "Bob", "Carol", "Dave", "Eve", "Francis"};

gameInitial::gameInitial(QWidget *parent) : QWidget{parent} {
    setFixedSize(1600, 900);
    playerSymbol* pSymbol[6];
    QLineEdit *nameInput[6];
    stylizedspinbox *playerCount = new stylizedspinbox();
    stylizedspinbox *initMoney = new stylizedspinbox();
    stylizedspinbox *roundLimit = new stylizedspinbox();
    stylizedButton *pointButton = new stylizedButton(28,28,":/resources/image/icons/unchecked.png","","",":/resources/image/icons/checked.png");
    {
        offlineView = new QFrame(this);
        offlineView->setGeometry(540, 80, 900, 760);
        offlineView->setObjectName("offlineView");
        offlineView->setStyleSheet("QFrame#offlineView{background-color:rgba(255,255,255,30);"
                                   "border-radius:10}");
        QHBoxLayout *pTopHBox = new QHBoxLayout();
        offlineView->setLayout(pTopHBox);
        QFrame *leftFrame = new QFrame();
        QFrame *rightFrame = new QFrame();
        QFrame *qLine = new QFrame();
        qLine->setFrameShape(QFrame::VLine);
        qLine->setObjectName("vLine");
        qLine->setStyleSheet("QFrame#vLine{background-color:rgba(255,255,255,30);"
                             "border-radius:3;"
                             "margin-top:10px;"
                             "margin-bottom:10px}");
        pTopHBox->addWidget(leftFrame);
        pTopHBox->addWidget(qLine);
        pTopHBox->addWidget(rightFrame);
        pTopHBox->setStretch(0, 5);
        pTopHBox->setStretch(2, 3);
        QFrame *playerView[6];
        //左侧
        {
            QLabel *leftText = new QLabel("角色设置");
            leftText->setAlignment(Qt::AlignCenter);
            leftText->setFont(QFont("Noto Sans SC", 18, 700));
            leftText->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");
            leftText->setFixedHeight(32);
            QGridLayout *leftLayout = new QGridLayout();
            leftFrame->setLayout(leftLayout);
            leftLayout->setSpacing(18);
            leftLayout->addWidget(leftText, 0, 0, 1, 2);
            stylizedButton *playerSelect[6][2];
            auto nowColor = availableColor.begin();
            for (int i = 0; i < 6; ++i) {
                playerView[i] = new QFrame();
                playerView[i]->setObjectName("offlineView");
                leftLayout->addWidget(playerView[i], 1 + (i / 2), i % 2);
                playerSelect[i][1] = new stylizedButton(40, 40, ":/resources/image/icons/human.png", "", "", ":/resources/image/icons/robot.png");
                playerSelect[i][1]->setCheckable(true);
                playerSelect[i][1]->setParent(playerView[i]);
                playerSelect[i][1]->move(196, 16);
                nameInput[i] = new QLineEdit(defaultName[i]);
                nameInput[i]->setFrame(false);
                nameInput[i]->setParent(playerView[i]);
                nameInput[i]->setFixedSize(230, 40);
                nameInput[i]->move(12, 161);
                nameInput[i]->setStyleSheet("background-color:rgba(255,255,255,0);"
                                            "color:white;"
                                            "border-width:0 0 2px 0;"
                                            "border-style: solid;"
                                            "border-color:rgba(255,255,255,50);"
                                            "padding-left:4px");
                pSymbol[i] = new playerSymbol(nowColor->first, 0, 90, 90);
                nowColor->second = true;
                nowColor++;
                if (nowColor == availableColor.end()) nowColor = availableColor.begin();
                pSymbol[i]->setParent(playerView[i]);
                pSymbol[i]->move(80, 50);
                connect(pSymbol[i], &playerSymbol::clicked, [=](bool) {
                    availableColor[pSymbol[i]->getColor()] = false;
                    auto switchColor = availableColor.find(pSymbol[i]->getColor());
                    switchColor++;
                    if (switchColor == availableColor.end()) switchColor = availableColor.begin();
                    while (switchColor->second) {
                        switchColor++;
                        if (switchColor == availableColor.end()) switchColor = availableColor.begin();
                    }
                    pSymbol[i]->setColor(switchColor->first);
                    switchColor->second = true;
                });
            }
        }
        //右侧
        {
            QGridLayout *rightLayout = new QGridLayout;
            rightLayout->setAlignment(Qt::AlignCenter);
            rightLayout->setSpacing(20);
            rightFrame->setLayout(rightLayout);
            rightLayout->setContentsMargins(30,0,30,0);
            QLabel *rightTitle = new QLabel("游戏设置");
            rightTitle->setAlignment(Qt::AlignCenter);
            rightTitle->setFont(QFont("Noto Sans SC", 18, 700));
            rightFrame->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");
            rightTitle->setFixedHeight(32);
            rightLayout->addWidget(rightTitle, 0, 0, 1, 2);
            //玩家数量设置
            {
                auto tableCount = new QLabel("游戏人数");
                rightLayout->addWidget(tableCount, 1, 0, 1, 1);
                playerCount->setValue(6);
                rightLayout->addWidget(playerCount, 1, 1, 1, 1);
                playerCount->setRange(2, 6);
                playerCount->setFixedSize(120, 40);
                connect(playerCount, &QSpinBox::valueChanged, [=](int n) {
                    for (int i = 0; i < n; ++i) {
                        for (auto t: playerView[i]->children()) {
                            if (t->isWidgetType()) {
                                ((QWidget *) t)->show();
                            }
                        }
                    }
                    for (int i = n; i < 6; ++i) {
                        for (auto t: playerView[i]->children()) {
                            if (t->isWidgetType()) {
                                ((QWidget *) t)->hide();
                            }
                        }
                    }
                });
            }
            //初始金钱设置
            {
                auto tableMoney = new QLabel("初始金钱");
                rightLayout->addWidget(tableMoney, 2, 0, 1, 1);
                initMoney->setValue(1500);
                initMoney->setSingleStep(100);
                rightLayout->addWidget(initMoney, 2, 1, 1, 1);
                initMoney->setRange(1000, 3200);
                initMoney->setFixedSize(120, 40);
            }
            {
                auto tableMode = new QLabel("局数限制");
                rightLayout->addWidget(tableMode, 3, 0, 1, 1);
                rightLayout->addWidget(roundLimit, 3, 1, 1, 1);
                roundLimit->setRange(25, 80);
                roundLimit->setFixedSize(120, 40);
                roundLimit->setSingleStep(5);
                roundLimit->setSpecialValueText("无限");
            }
            {
                auto tablePoint = new QLabel("点数系统");
                rightLayout->addWidget(tablePoint,4,0,1,1);
                pointButton->setCheckable(true);
                rightLayout->addWidget(pointButton,4,1,1,1,Qt::AlignCenter);
            }
        }
    }
    {//模式切换按钮
        QFrame *container = new QFrame(this);
        container->setGeometry(340, 80, 180, 760);
        container->setStyleSheet("QFrame{background-color:rgba(255,255,255,60);"
                                 "border-radius:10}");

        stylizedButton *modeBtn = new stylizedButton(160, 160, ":/resources/image/icons/offline.png", "", "", ":/resources/image/icons/online.png");
        modeBtn->setParent(container);
        modeBtn->move(10, 20);
        modeBtn->setCheckable(true);

        QLabel *textMode = new QLabel("本地模式", container);
        textMode->setGeometry(0, 174, 180, 60);
        textMode->setAlignment(Qt::AlignCenter);
        textMode->setFont(QFont("Noto Sans SC", 22, 700));
        textMode->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");

        connect(modeBtn, &stylizedButton::toggled, this, [=](bool) {
            if (modeBtn->isChecked()) {
                switchView(1);
                textMode->setText("联机模式");
            } else {
                switchView(0);
                textMode->setText("本地模式");
            }
        });

        stylizedButton* startButton = new stylizedButton(160,160,":/resources/image/icons/start.png","","","");
        startButton->setParent(container);
        startButton->move(10,550);

        QLabel *textStart = new QLabel("开始", container);
        textStart->setGeometry(0, 690, 180, 60);
        textStart->setAlignment(Qt::AlignCenter);
        textStart->setFont(QFont("Noto Sans SC", 22, 700));
        textStart->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");

        connect(startButton,&stylizedButton::clicked,this,[=](bool){
            int playCnt=playerCount->value();
            QList<Player *> players;
            for (int i = 0; i < playCnt; ++i) {
                Player* p = new Player(pSymbol[i]->getColor(),nameInput[i]->text(),initMoney->value(),1.0,1.0,1.0,1.0);
                players.push_back(p);
            }
            //TODO 初始属性
            emit gameStarted(players,playCnt,initMoney->value(),(roundLimit->value()==25)?0:roundLimit->value(),pointButton->isChecked());
        });
    }
    {
        onlineView = new QFrame(this);
        onlineView->hide();
        onlineView->setGeometry(540, 80, 900, 760);
        onlineView->setObjectName("onlineView");
        onlineView->setStyleSheet("QFrame{background-color:rgba(255,255,255,40);}"
                                  "QFrame#onlineView{border-radius:10}");

        QHBoxLayout *pTopHBox = new QHBoxLayout();
        onlineView->setLayout(pTopHBox);
        QLabel *textMode = new QLabel("Under development...\n联机模式正在开发中");
        textMode->setAlignment(Qt::AlignCenter);
        textMode->setFont(QFont("Noto Sans SC", 26, 700));
        textMode->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");
        pTopHBox->addWidget(textMode);
    }
}

void gameInitial::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap bk("://resources/image/background-noIcon.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), bk);
}
void gameInitial::switchView(int mode) {
    if (mode) {
        offlineView->hide();
        onlineView->show();
    } else {
        onlineView->hide();
        offlineView->show();
    }
}
