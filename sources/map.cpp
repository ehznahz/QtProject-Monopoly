#include "headers/map.h"
#include "QGridLayout"
#include "QPalette"
#include "headers/cardview.h"

#include "headers/stylizedbutton.h"
#include "QLabel"

Map::Map(){
	this->setFixedSize(860, 860);
	QPalette qPalette;
	qPalette.setColor(QPalette::Window, QColor(0x18101e));
	this->setPalette(qPalette);
	this->setAutoFillBackground(true);
	//地图初始化
	block[0] = new Block("出发!", "停留于起点，多获得￥200", "START", -1, 0, 0, 0, 0, 0);
	block[1] = new Block("朗润园", "￥60", "Property", 1, 60, 50, 2, 1, 0);
	block[2] = new Block("宝箱", "试试你的运气", "Community Chest", -1, 0, 0, 0, 1, 0);
	block[3] = new Block("承泽园", "￥60", "Property", 1, 60, 50, 4, 1, 0);
	block[4] = new Block("动力中心", "缴纳电费：￥200", "Tax", -1, 0, 0, 200, 1, 0);
	block[5] = new Block("北京大学东门站", "￥200", "Railroad", -1, 200, 0, 0, 1, 0);
	block[6] = new Block("李兆基人文学苑", "￥100", "Property", 2, 100, 50, 6, 1, 0);
	block[7] = new Block("机遇", "试试你的运气", "Chance", -1, 0, 0, 0, 1, 0);
	block[8] = new Block("廖凯原楼", "￥100", "Property", 2, 60, 50, 6, 1, 0);
	block[9] = new Block("李兆基楼", " ￥120", "Property", 2, 60, 50, 8, 1, 0);
	block[10] = new Block("小黑屋", "探监", "Jail", -1, 0, 0, 0, 0, 0);
	block[11] = new Block("逸夫楼", "￥140", "Property", 3, 140, 100, 10, 1, 1);
	block[12] = new Block("新太阳学生中心", "￥150", "Utility", -1, 150, 0, 0, 1, 1);
	block[13] = new Block("臭名昭著45乙", "￥140", "Property", 3, 140, 100, 10, 1, 1);
	block[14] = new Block("金碧辉煌35楼", "￥160", "Property", 3, 160, 100, 12, 1, 1);
	block[15] = new Block("人民大学站", "￥200", "Railroad", -1, 200, 0, 0, 1, 1);
	block[16] = new Block("平平无奇28楼", "￥180", "Property", 4, 180, 100, 14, 1, 1);
	block[17] = new Block("宝箱", "试试你的运气", "Community Chest", -1, 0, 0, 0, 1, 1);
	block[18] = new Block("静园", "￥180", "Property", 4, 180, 100, 14, 1, 1);
	block[19] = new Block("理科一号楼", "￥200", "Property", 4, 200, 100, 16, 1, 1);
	block[20] = new Block("度假", "无事发生", "Free Parking", -1, 0, 0, 0, 0, 2);
	block[21] = new Block("理科二号楼", "￥220", "Property", 5, 220, 150, 18, 1, 2);
	block[22] = new Block("机遇", "试试你的运气", "Chance", -1, 0, 0, 0, 1, 2);
	block[23] = new Block("理科三号楼", "￥220", "Property", 5, 220, 150, 18, 1, 2);
	block[24] = new Block("百周年纪念讲堂", "￥240", "Property", 5, 240, 150, 20, 1, 2);
	block[25] = new Block("海淀黄庄站", "￥200", "Railroad", -1, 200, 0, 0, 1, 2);
	block[26] = new Block("微纳电子大厦", "￥260", "Property", 6, 260, 150, 22, 1, 2);
	block[27] = new Block("王克桢楼", "￥260", "Property", 6, 260, 150, 22, 1, 2);
	block[28] = new Block("近邻宝", "￥150", "Utility", -1, 150, 0, 0, 1, 2);
	block[29] = new Block("圆明园校区", "￥280", "Property", 6, 280, 150, 22, 1, 2);
	block[30] = new Block("树洞禁言", "不经过起点，直接进小黑屋", "Go To Jail", -1, 0, 0, 0, 0, 2);
	block[31] = new Block("五四体育场", "￥300", "Property", 7, 300, 200, 26, 1, 3);
	block[32] = new Block("未名湖", "￥300", "Property", 7, 300, 200, 26, 1, 3);
	block[33] = new Block("宝箱", "试试你的运气", "Community Chest", -1, 0, 0, 0, 1, 3);
	block[34] = new Block("博雅塔", "￥320", "Property", 7, 320, 200, 28, 1, 3);
	block[35] = new Block("圆明园站", "￥200", "Railroad", -1, 200, 0, 0, 1, 3);
	block[36] = new Block("机遇", "试试你的运气", "Chance", -1, 0, 0, 0, 1, 3);
	block[37] = new Block("第一体育馆", "￥350", "Property", 8, 350, 200, 35, 1, 3);
	block[38] = new Block("餐饮中心", "缴纳伙食费：￥100 ", "Tax", -1, 0, 0, 100, 1, 3);
	block[39] = new Block("第二体育馆", "￥400", "Property", 8, 400, 200, 50, 1, 3);
	QGridLayout *layout = new QGridLayout;
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);
	for(int i = 0; i < 10; ++i) {
		layout->addWidget(block[i], 0, i, 1, 1);
		block[i]->setLayout(new CardLayout(13, 0));
		block[i]->layout()->setContentsMargins(0, 0, 0, 0);
	}
	for(int i = 0; i < 10; ++i) {
		layout->addWidget(block[10 + i], i, 10, 1, 1);
		block[10 + i]->setLayout(new CardLayout(13, 1));
		block[10 + i]->layout()->setContentsMargins(0, 0, 0, 0);
	}
	for(int i = 0; i < 10; ++i) {
		layout->addWidget(block[20 + i], 10, 10 - i, 1, 1);
		block[20 + i]->setLayout(new CardLayout(13, 0));
		block[20 + i]->layout()->setContentsMargins(0, 0, 0, 0);
	}
	for(int i = 0; i < 10; ++i) {
		layout->addWidget(block[30 + i], 10 - i, 0, 1, 1);
		block[30 + i]->setLayout(new CardLayout(13, 1));
		block[30 + i]->layout()->setContentsMargins(0, 0, 0, 0);
	}
}

void Map::Move(int __player, int __step){
	int origLoc = player[__player]->Location();
	player[__player]->Move(__step);
	int loc = player[__player]->Location();
	MoveSymbol(__player, origLoc, loc);
	if(loc < __step) {
		if(loc != 0)eView->addEvent(player[__player]->getName() + " 经过起点,获得 ￥200", 0);
		player[__player]->Earn(200);
	}
	//判断行动
	if(block[loc]->Type() == "START") {
        eView->addEvent(player[__player]->getName() + " 到达起点,获得 ￥400", 0);
		player[__player]->Earn(200);
	} else if(block[loc]->Type() == "Jail") {
	} else if(block[loc]->Type() == "Free Parking") {
	} else if(block[loc]->Type() == "Go To Jail") {
		if(rand() % 32768 > player[__player]->EscapeRate() * 32768) {
			eView->addEvent(player[__player]->getName() + " 不幸在树洞被禁言两回合", 0);
			player[__player]->Imprison();
			Move(__player, 20);
		} else {
			eView->addEvent(player[__player]->getName() + " 人品大爆发,被枪口抬高两寸,无需禁言", 0);
		}
	} else if(block[loc]->Type() == "Tax") {
		player[__player]->Earn(-block[loc]->Rent());
		eView->addEvent(player[__player]->getName() + " " + block[loc]->Action(), 0);
	} else if(block[loc]->Type() == "Property") {
		if(block[loc]->Owner() == -1) {
			emit BuyOrNot(__player, loc);
		} else if(block[loc]->Owner() != __player) {
			player[__player]->Earn(-int(block[loc]->Rent() * player[__player]->RentRate()));
			player[block[loc]->Owner()]->Earn(int(block[loc]->Rent() * player[__player]->RentRate()));
			eView->addEvent(player[__player]->getName() + " 在 " + block[loc]->getName() + " 向 " + player[block[loc]->Owner()]->getName() + " 支付了 ￥" + QString::number(int(block[loc]->Rent() * player[__player]->RentRate())), 0);
		}
	} else if(block[loc]->Type() == "Railroad") {
		if(block[loc]->Owner() == -1) {
			emit BuyOrNot(__player, loc);
		} else if(block[loc]->Owner() != __player) {
			int cost = 25;
			for(int i = (loc + 10) % 40; i != loc; i = (i + 10) % 40) {
				if(block[i]->Owner() == block[loc]->Owner()) cost <<= 1;
			}
			player[__player]->Earn(-int(cost * player[__player]->RentRate()));
			player[block[loc]->Owner()]->Earn(int(cost * player[__player]->RentRate()));
			eView->addEvent(player[__player]->getName() + " 在 " + block[loc]->getName() + " 向 " + player[block[loc]->Owner()]->getName() + " 支付了 ￥" + QString::number(int(cost * player[__player]->RentRate())), 0);
		}
	} else if(block[loc]->Type() == "Utility") {
		if(block[loc]->Owner() == -1) {
			emit BuyOrNot(__player, loc);
		} else if(block[loc]->Owner() != __player) {
			int cost = __step;
			if(block[40 - loc]->Owner() == block[loc]->Owner()) {cost *= 10;}
			else {cost *= 4;}
			player[__player]->Earn(-int(cost * player[__player]->RentRate()));
			player[block[loc]->Owner()]->Earn(int(cost * player[__player]->RentRate()));
			eView->addEvent(player[__player]->getName() + " 在 " + block[loc]->getName() + " 向 " + player[block[loc]->Owner()]->getName() + " 支付了 ￥" + QString::number(int(cost * player[__player]->RentRate())), 0);
		}
	} else if(block[loc]->Type() == "Community Chest") {
        int key = rand() % 32768 * (2 - player[__player]->LuckyRate());
		if(key < 2048) {
			Move(__player, (-loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 脚一滑,回到了原点", 2);
		} else if(key < 8192) {
			player[__player]->Earn(60);
			eView->addEvent(player[__player]->getName() + " 获得每月餐补 ￥60", 2);
		} else if(key < 14336) {
			int num = 0;
			for(int i = 0; i < playerNumber; ++i) num += player[i]->Alive();
			player[__player]->Earn(10 * num);
			eView->addEvent(player[__player]->getName() + " 过生日,从每个人收取了 ￥10", 2);
		} else if(key < 20480) {
			int num = 0;
			for(int i = 0; i < playerNumber; ++i) num += player[i]->Alive();
			player[__player]->Earn(-20 * num);
			eView->addEvent(player[__player]->getName() + " 请在场的各位喝奶茶,各花费 ￥20", 2);
		} else if(key < 26624) {
			player[__player]->Earn(-100);
			eView->addEvent(player[__player]->getName() + " 手机坏了,维修花费 ￥100", 2);
		} else if(key < 30720) {
			if(rand() % 32768 > player[__player]->EscapeRate() * 32768) {
				Move(__player, (10 - loc + 40) % 40);
				eView->addEvent(player[__player]->getName() + " 不幸在树洞被禁言两回合", 2);
				player[__player]->Imprison();
			} else {
				eView->addEvent(player[__player]->getName() + " 人品大爆发,被枪口抬高两寸,无需禁言", 2);
			}
		} else {
			int price = 0;
			for(int i = 0; i < 40; ++i) if(block[i]->Owner() == __player) price += block[i]->House() * 50;
			player[__player]->Earn(-price);
            eView->addEvent(player[__player]->getName() + " 的房产需要缴纳物业费,每座房产 ￥50", 2);
		}
	} else if(block[loc]->Type() == "Chance") {
		int key = rand() % 32768 * (2 - player[__player]->LuckyRate());
		if(key < 2048) {
			Move(__player, (-loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往起点", 1);
		} else if(key < 4096) {
			Move(__player, (5 - loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往北京大学东门站", 1);
		} else if(key < 6144) {
			Move(__player, (15 - loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往人民大学站", 1);
		} else if(key < 8192) {
			Move(__player, (25 - loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往海淀黄庄站", 1);
		} else if(key < 10240) {
			Move(__player, (35 - loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往圆明园站", 1);
		} else if(key < 14336) {
			Move(__player, 3);
			eView->addEvent(player[__player]->getName() + " 向前三步", 1);
		} else if(key < 18432) {
			Move(__player, -3);
			eView->addEvent(player[__player]->getName() + " 向后三步", 1);
		} else if(key < 22528) {
			Move(__player, (39 - loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往二体", 1);
		} else if(key < 26624) {
			Move(__player, (21 - loc + 40) % 40);
			eView->addEvent(player[__player]->getName() + " 前往理科二号楼", 1);
		} else {
			if(rand() % 32768 > player[__player]->EscapeRate() * 32768) {
				Move(__player, (10 - loc + 40) % 40);
				eView->addEvent(player[__player]->getName() + " 不幸在树洞被禁言两回合", 1);
				player[__player]->Imprison();
			} else {
				eView->addEvent(player[__player]->getName() + " 不幸在树洞被禁言两回合", 1);
			}
		}
	}
}

void Map::Update(){
	for(int i = 0; i < 40; ++i) {
        if(block[i]->Color() > 0 && block[i]->Owner() >= 0) {
			bool flag = true;
			for(int j = 0; j < 40; ++j) {
				if(block[i]->Color() == block[j]->Color() && block[i]->Owner() != block[j]->Owner()) flag = false;
			}
			if(block[i]->United() != flag) block[i]->ChangeUnited();
		}
	}
}

void Map::Bankrupt(int __player){
	for(int i = 0; i < 40; ++i) {
		if(block[i]->Owner() == __player) {
			block[i]->Buy(-1);
			for(block[i]->Redeem(); block[i]->House() > 0; block[i]->Sell());
		}
	}
	player[__player]->Bankrupt();
	Update();
}

void Map::Buy(int __player, int __block){
	player[__player]->Earn(-int(block[__block]->Price0() * player[__player]->BuildRate()));
	player[__player]->Buy(__block);
	block[__block]->Buy(__player);
	Update();
}

void Map::Mortgage(int __player, int __block){
	player[__player]->Earn(int(block[__block]->Price0() * player[__player]->BuildRate() * 0.5));
	block[__block]->Mortgage();
}

void Map::Redeem(int __player, int __block){
	player[__player]->Earn(-int(block[__block]->Price0() * player[__player]->BuildRate() * 0.55));
	block[__block]->Redeem();
}

void Map::Sell(int __player, int __block){
	player[__player]->Earn(int(block[__block]->Price1() * player[__player]->BuildRate() * 0.5));
	block[__block]->Sell();
}

void Map::Build(int __player, int __block){
	player[__player]->Earn(-int(block[__block]->Price1() * player[__player]->BuildRate()));
	block[__block]->Build();
}

void Map::MoveSymbol(int _player, int from, int to){
	block[from]->layout()->removeWidget(&player[_player]->symbol);
	player[_player]->symbol.setDirection(((to / 10) + 1) % 4);
	player[_player]->symbol.setParent(nullptr);
	block[to]->layout()->addWidget(&player[_player]->symbol);
}
