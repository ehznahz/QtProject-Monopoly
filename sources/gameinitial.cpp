#include "headers/gameinitial.h"
#include "QEventLoop"
#include "QFrame"
#include "QLabel"
#include "QLayout"
#include "QLineEdit"
#include "QPainter"
#include "QTimer"
#include "QWidget"
#include "headers/player.h"
#include "headers/playersymbol.h"
#include "headers/stylizedbutton.h"
#include "headers/stylizedspinbox.h"
#include "map"

std::map<int, bool> availableColor = {{0xff68b4, false},
                                      {0xff00ff, false},
                                      {0x00bfff, false},
                                      {0x3c8371, false},
                                      {0x32cd32, false},
                                      {0xffd700, false},
                                      {0xeee8aa, false},
                                      {0xffa500, false},
                                      {0xc0c0c0, false}};

QString defaultName[6] = {"Alice", "Bob", "Carol", "Dave", "Eve", "Francis"};
double rates[4][4] = {{1.00, 1.02, 1.06, 1.12}, //lucky
                      {1.00, 0.90, 0.81, 0.60},  //build
                      {1.00, 1.15, 1.33, 1.52},  //esc
                      {1.00, 0.90, 0.81, 0.60}};  //rent
int points[4] = {0, 1, 3, 6};

gameInitial::gameInitial(QWidget *parent) : QWidget{parent}{
	setFixedSize(1600, 900);
	playerSymbol *pSymbol[6];
	QLineEdit *nameInput[6];

	stylizedButton *close = new stylizedButton(40, 40, ":/resources/image/icons/close.png");
	close->setParent(this);
	close->move(1500, 50);
	close->show();
	connect(close, &stylizedButton::pressed, this, &gameInitial::returnMainPage);

	stylizedspinbox *playerCount = new stylizedspinbox();
	stylizedspinbox *initMoney = new stylizedspinbox();
	stylizedButton *pointButton = new stylizedButton(28, 28, ":/resources/image/icons/unchecked.png", "", "", ":/resources/image/icons/checked.png");
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
			auto nowColor = availableColor.begin();
			for(int i = 0; i < 6; ++i) {
				playerView[i] = new QFrame();
				playerView[i]->setObjectName("offlineView");
				leftLayout->addWidget(playerView[i], 1 + (i / 2), i % 2);
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
				if(nowColor == availableColor.end()) nowColor = availableColor.begin();
				pSymbol[i]->setParent(playerView[i]);
				pSymbol[i]->move(80, 50);
				connect(pSymbol[i], &playerSymbol::clicked, [=](bool){
					availableColor[pSymbol[i]->getColor()] = false;
					auto switchColor = availableColor.find(pSymbol[i]->getColor());
					switchColor++;
					if(switchColor == availableColor.end()) switchColor = availableColor.begin();
					while(switchColor->second) {
						switchColor++;
						if(switchColor == availableColor.end()) switchColor = availableColor.begin();
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
			rightLayout->setContentsMargins(30, 0, 30, 0);
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
				connect(playerCount, &QSpinBox::valueChanged, [=](int n){
					for(int i = 0; i < n; ++i) {
						for(auto t: playerView[i]->children()) {
							if(t->isWidgetType()) {
								((QWidget *) t)->show();
							}
						}
					}
					for(int i = n; i < 6; ++i) {
						for(auto t: playerView[i]->children()) {
							if(t->isWidgetType()) {
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
				auto tablePoint = new QLabel("点数系统");
				rightLayout->addWidget(tablePoint, 4, 0, 1, 1);
				pointButton->setCheckable(true);
				rightLayout->addWidget(pointButton, 4, 1, 1, 1, Qt::AlignCenter);
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

		connect(modeBtn, &stylizedButton::toggled, this, [=](bool){
			if(modeBtn->isChecked()) {
				switchView(1);
				textMode->setText("联机模式");
			} else {
				switchView(0);
				textMode->setText("本地模式");
			}
		});

		stylizedButton *startButton = new stylizedButton(160, 160, ":/resources/image/icons/start.png", "", "", "");
		startButton->setParent(container);
		startButton->move(10, 550);

		QLabel *textStart = new QLabel("开始", container);
		textStart->setGeometry(0, 690, 180, 60);
		textStart->setAlignment(Qt::AlignCenter);
		textStart->setFont(QFont("Noto Sans SC", 22, 700));
		textStart->setStyleSheet("QLabel{color:white;background-color:rgba(0,0,0,0)}");

		connect(startButton, &stylizedButton::clicked, this, [=](bool){
			int playCnt = playerCount->value();
			QList<Player *> players;
			for(int i = 0; i < playCnt; ++i) {
				Player *p = new Player(pSymbol[i]->getColor(), nameInput[i]->text(), initMoney->value(), 1.0, 1.0, 1.0, 1.0);
				players.push_back(p);
			}
			if(pointButton->isChecked()) {
				this->hide();
				for(int i = 0; i < playCnt; ++i) {
					bool flag = false;
					QWidget *setWidget = new QWidget(this->parentWidget());
					setWidget->setGeometry(0, 0, 1600, 900);
					//setWidget->setWindowModality(Qt::ApplicationModal);
					setWidget->setObjectName("widgetSet");
					setWidget->setStyleSheet("QWidget#widgetSet{border-image:url(:/resources/image/background-noIcon.png) 0 0 0 0 stretch stretch}"
					                         "QLabel{color:white;}");
					setWidget->show();
					QGridLayout *gridLayout = new QGridLayout;
					gridLayout->setVerticalSpacing(10);
					setWidget->setLayout(gridLayout);
					gridLayout->setContentsMargins(300, 100, 300, 100);
					gridLayout->setAlignment(Qt::AlignCenter);
					auto title = new QLabel("玩家 " + QString::number(i) + ": " + players[i]->getName());
					title->setFont(QFont("Noto Sans SC", 20, 700));
					gridLayout->addWidget(title, 0, 0, 1, 1);
					auto titleR = new QLabel("属性设置");
					titleR->setFont(QFont("Noto Sans SC", 20, 700));
					gridLayout->addWidget(titleR, 0, 1, 1, 1, Qt::AlignRight);
					gridLayout->addWidget(new QLabel("幸运"), 1, 0, 1, 1);
					auto spinLucky = new stylizedspinbox(0, 3);
					gridLayout->addWidget(spinLucky, 1, 1, 1, 1);
					gridLayout->addWidget(new QLabel("建筑"), 2, 0, 1, 1);
					auto spinBuild = new stylizedspinbox(0, 3);
					gridLayout->addWidget(spinBuild, 2, 1, 1, 1);
					gridLayout->addWidget(new QLabel("逃脱"), 3, 0, 1, 1);
					auto spinEscape = new stylizedspinbox(0, 3);
					gridLayout->addWidget(spinEscape, 3, 1, 1, 1);
					gridLayout->addWidget(new QLabel("减租"), 4, 0, 1, 1);
					auto spinRent = new stylizedspinbox(0, 3);
					gridLayout->addWidget(spinRent, 4, 1, 1, 1);
					auto tips = new QLabel("每个玩家具有10点的初始点数，每个属性的1-3等级分别消耗1、3、6点数，级别越高属性越强。");
					tips->setFont(QFont("Noto Sans SC", 10, 700));
					gridLayout->addWidget(tips, 5, 0, 1, 2);
					auto warning = new QLabel("总需要的点数不能高于10。");
					warning->setFont(QFont("Noto Sans SC", 10, 700));
					warning->setStyleSheet("color:red");
					gridLayout->addWidget(warning, 6, 0, 1, 2);
					warning->setVisible(false);
					stylizedButton *nextBtn = new stylizedButton("下一步", 500, 50);
					gridLayout->addWidget(nextBtn, 7, 0, 1, 2, Qt::AlignCenter);
					QEventLoop *loop = new QEventLoop;
					connect(nextBtn, &stylizedButton::pressed, this, [=, &flag](){
						if(points[spinLucky->value()] + points[spinEscape->value()] + points[spinBuild->value()] + points[spinRent->value()] > 10) {
							if(!flag) {
								warning->setVisible(true);
							}
							flag = true;
						} else {
							players[i]->setLuckyRate(rates[0][spinLucky->value()]);
							players[i]->setBuildRate(rates[1][spinBuild->value()]);
							players[i]->setEscapeRate(rates[2][spinEscape->value()]);
							players[i]->setRentRate(rates[3][spinRent->value()]);
							loop->exit();
							delete setWidget;
						}
					});
					loop->exec();
				}
			}
			emit gameStarted(players, playCnt, 0, pointButton->isChecked());
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

void gameInitial::paintEvent(QPaintEvent *){
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	QPixmap bk("://resources/image/background-noIcon.png");
	painter.drawPixmap(0, 0, this->width(), this->height(), bk);
}

void gameInitial::switchView(int mode){
	if(mode) {
		offlineView->hide();
		onlineView->show();
	} else {
		onlineView->hide();
		offlineView->show();
	}
}
