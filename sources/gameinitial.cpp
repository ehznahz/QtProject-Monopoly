#include "QLineEdit"
#include "QLayout"
#include "QPainter"
#include "QLabel"
#include "headers/gameinitial.h"
#include "headers/stylizedbutton.h"
#include "QWidget"
#include "QFrame"
#include "headers/playersymbol.h"
#include "map"

std::map<int,bool> availableColor = {
        {0x9a2b2e,false},
        {0xfbc85f,false},
        {0xf96815,false},
        {0xc0428a,false},
        {0x207349,false},
        {0x96d8de,false},
        {0x325b74,false},
        {0x726a4e,false},
        {0x788f74,false},
        {0x76c1b2,false},
        {0xf3774d,false},
        {0xf8de8d,false},
        {0xc5aecf,false}
};
QString defaultName[6]={"Alice","Bob","Carol","Dave","Excited","Francis"};

gameInitial::gameInitial(QWidget *parent) : QWidget{parent} {
    setFixedSize(1600, 900);
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
    }
    {
        offlineView = new QFrame(this);
        offlineView->setGeometry(540,80,900,760);
        offlineView->setObjectName("offlineView");
        offlineView->setStyleSheet("QFrame#offlineView{background-color:rgba(255,255,255,30);"
                                   "border-radius:10}");
        QHBoxLayout *pTopHBox =new QHBoxLayout();
        offlineView->setLayout(pTopHBox);
        QFrame *leftFrame = new QFrame();
        QFrame *rightFrame = new QFrame();
        QFrame *qLine=new QFrame();
        qLine->setFrameShape(QFrame::VLine);
        qLine->setObjectName("vLine");
        qLine->setStyleSheet("QFrame#vLine{background-color:rgba(255,255,255,30);"
                             "border-radius:3;"
                             "margin-top:10px;"
                             "margin-bottom:10px}");
        //qLine->setFrameShadow(QFrame::Raised);
        pTopHBox->addWidget(leftFrame);
        pTopHBox->addWidget(qLine);
        pTopHBox->addWidget(rightFrame);
        pTopHBox->setStretch(0,5);
        pTopHBox->setStretch(2,3);
        //左侧
        QLabel *leftText = new QLabel("角色设置");
        leftText->setAlignment(Qt::AlignCenter);
        leftText->setFont(QFont("Noto Sans SC", 18, 700));
        leftText->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");
        leftText->setFixedHeight(32);
        QGridLayout* leftLayout=new QGridLayout();
        leftFrame->setLayout(leftLayout);
        leftLayout->setSpacing(18);
        leftLayout->addWidget(leftText,0,0,1,2);
        QFrame* playerView[6];
        stylizedButton* playerSelect[6][2];
        QLineEdit* nameInput[6];
        auto nowColor = availableColor.begin();
        for (int i = 0; i < 6; ++i) {
            playerView[i]=new QFrame();
            playerView[i]->setObjectName("offlineView");
            leftLayout->addWidget(playerView[i],1+(i/2),i%2);
            playerSelect[i][1]=new stylizedButton(40,40,":/resources/image/icons/human.png","","",":/resources/image/icons/robot.png");
            playerSelect[i][1]->setCheckable(true);
            playerSelect[i][1]->setParent(playerView[i]);
            playerSelect[i][1]->move(196,16);
            nameInput[i]=new QLineEdit(defaultName[i]);
            nameInput[i]->setFrame(false);
            nameInput[i]->setParent(playerView[i]);
            nameInput[i]->setFixedSize(230,40);
            nameInput[i]->move(12,161);
            nameInput[i]->setStyleSheet("background-color:rgba(255,255,255,0);"
                                        "color:white;"
                                        "border-width:0 0 2px 0;"
                                        "border-style: solid;"
                                        "border-color:rgba(255,255,255,50);"
                                        "padding-left:4px"
                                        );
            playerSymbol* p = new playerSymbol(nowColor->first,0,90,90);
            nowColor->second= true;
            nowColor++;
            if(nowColor==availableColor.end())nowColor=availableColor.begin();
            p->setParent(playerView[i]);
            p->move(80,50);
            connect(p,&playerSymbol::clicked,[=](bool){
                availableColor[p->getColor()]= false;
                auto switchColor = availableColor.find(p->getColor());
                switchColor++;
                if(switchColor==availableColor.end())switchColor=availableColor.begin();
                while (switchColor->second){
                    switchColor++;
                    if(switchColor==availableColor.end())switchColor=availableColor.begin();
                }
                p->setColor(switchColor->first);
                switchColor->second=true;
            });
        }
    }
    {
        onlineView = new QFrame(this);
        onlineView->hide();
        onlineView->setGeometry(540,80,900,760);
        onlineView->setObjectName("onlineView");
        onlineView->setStyleSheet("QFrame{background-color:rgba(255,255,255,40);}"
                                   "QFrame#onlineView{border-radius:10}");

        QHBoxLayout *pTopHBox =new QHBoxLayout();
        onlineView->setLayout(pTopHBox);
        QLabel *textMode = new QLabel("Under development...\n联机模式正在开发中");
        textMode->setAlignment(Qt::AlignCenter);
        textMode->setFont(QFont("Noto Sans SC", 26, 700));
        textMode->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");
        pTopHBox->addWidget(textMode);

    }

}

void gameInitial::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap bk("://resources/image/background-noIcon.png");
    painter.drawPixmap(0,0,this->width(),this->height(),bk);
}
void gameInitial::switchView(int mode) {
    if(mode){
        offlineView->hide();
        onlineView->show();
    }
    else{
        onlineView->hide();
        offlineView->show();
    }
}
