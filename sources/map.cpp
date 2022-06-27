#include "headers/map.h"
#include "QGridLayout"
#include <cstdlib>
#include <ctime>

Map::Map() {
    this->setFixedSize(860, 860);
    //地图初始化
    //TODO 地图填写
    block[0] = new Block("   GO!   \n         ", "Pass Go! \nGet $200 ", "START", -1, 0, 0, 0, 0, 0);
    block[1] = new Block("         \n         ", "         \n   $60   ", "Property", 1, 60, 50, 2, 1, 0);
    block[2] = new Block("Community\n  Chest  ", "         \n         ", "Community Chest", -1, 0, 0, 0, 1, 0);
    block[3] = new Block("         \n         ", "         \n   $60   ", "Property", 1, 60, 50, 4, 1, 0);
    block[4] = new Block("         \n         ", "         \nPay $200 ", "Tax", -1, 0, 0, 200, 1, 0);
    block[5] = new Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0, 1, 0);
    block[6] = new Block(" Chance  \n         ", "         \n  $100   ", "Property", 2, 100, 50, 6, 1, 0);
    block[7] = new Block("         \n         ", "         \n         ", "Chance", -1, 0, 0, 0, 1, 0);
    block[8] = new Block("         \n         ", "         \n  $100   ", "Property", 2, 60, 50, 6, 1, 0);
    block[9] = new Block("         \n         ", "         \n  $120   ", "Property", 2, 60, 50, 8, 1, 0);
    block[10] = new Block("         \n         ", "   Just  \nVisiting ", "Jail", -1, 0, 0, 0, 0, 0);
    block[11] = new Block("         \n         ", "         \n  $140   ", "Property", 3, 140, 100, 10, 1, 1);
    block[12] = new Block("         \n         ", "         \n  $150   ", "Utility", -1, 150, 0, 0, 1, 1);
    block[13] = new Block("         \n         ", "         \n  $140   ", "Property", 3, 140, 100, 10, 1, 1);
    block[14] = new Block("         \n         ", "         \n  $160   ", "Property", 3, 160, 100, 12, 1, 1);
    block[15] = new Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0, 1, 1);
    block[16] = new Block("         \n         ", "         \n  $180   ", "Property", 4, 180, 100, 14, 1, 1);
    block[17] = new Block("Community\n  Chest  ", "         \n         ", "Community Chest", -1, 0, 0, 0, 1, 1);
    block[18] = new Block("         \n         ", "         \n  $180   ", "Property", 4, 180, 100, 14, 1, 1);
    block[19] = new Block("         \n         ", "         \n  $200   ", "Property", 4, 200, 100, 16, 1, 1);
    block[20] = new Block("         \n         ", "   Just  \nVisiting ", "Free Parking", -1, 0, 0, 0, 0, 2);
    block[21] = new Block("         \n         ", "         \n  $220   ", "Property", 5, 220, 150, 18, 1, 2);
    block[22] = new Block(" Chance  \n         ", "         \n         ", "Chance", -1, 0, 0, 0, 1, 2);
    block[23] = new Block("         \n         ", "         \n  $220   ", "Property", 5, 220, 150, 18, 1, 2);
    block[24] = new Block("         \n         ", "         \n  $240   ", "Property", 5, 240, 150, 20, 1, 2);
    block[25] = new Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0, 1, 2);
    block[26] = new Block("         \n         ", "         \n  $260   ", "Property", 6, 260, 150, 22, 1, 2);
    block[27] = new Block("         \n         ", "         \n  $260   ", "Property", 6, 260, 150, 22, 1, 2);
    block[28] = new Block("         \n         ", "         \n         ", "Utility", -1, 0, 0, 0, 1, 2);
    block[29] = new Block("         \n         ", "         \n  $280   ", "Property", 6, 280, 150, 22, 1, 2);
    block[30] = new Block("         \n         ", "         \n         ", "Go To Jail", -1, 0, 0, 0, 0, 2);
    block[31] = new Block("         \n         ", "         \n  $300   ", "Property", 7, 300, 200, 26, 1, 3);
    block[32] = new Block("         \n         ", "         \n  $300   ", "Property", 7, 300, 200, 26, 1, 3);
    block[33] = new Block("Community\n  Chest  ", "         \n         ", "Community Chest", -1, 0, 0, 0, 1, 3);
    block[34] = new Block("         \n         ", "         \n  $320   ", "Property", 7, 320, 200, 28, 1, 3);
    block[35] = new Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0, 1, 3);
    block[36] = new Block(" Chance  \n         ", "         \n         ", "Chance", -1, 0, 0, 0, 1, 3);
    block[37] = new Block("         \n         ", "         \n  $350   ", "Property", 8, 350, 200, 35, 1, 3);
    block[38] = new Block("         \n         ", "         \nPay $100 ", "Tax", -1, 0, 0, 100, 1, 3);
    block[39] = new Block("         \n         ", "         \n  $400   ", "Property", 8, 400, 200, 50, 1, 3);
    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
    for (int i = 0; i <= 9; ++i) {
        layout->addWidget(block[i], 0, i, 1, 1);
    }
    for (int i = 0; i <= 9; ++i) {
        layout->addWidget(block[10 + i], i, 10, 1, 1);
    }
    for (int i = 0; i <= 9; ++i) {
        layout->addWidget(block[20 + i], 10, 10 - i, 1, 1);
    }
    for (int i = 0; i <= 9; ++i) {
        layout->addWidget(block[30 + i], 10 - i, 0, 1, 1);
    }
}

void Map::Move(int __player, int __step) {
    player[__player]->Move(__step);
    int loc = player[__player]->Location();
    if (loc < __step) player[__player]->Earn(200);
    //判断行动
    if (block[loc]->Type() == "START") {
        player[__player]->Earn(200);
    } else if (block[loc]->Type() == "Jail") {
    } else if (block[loc]->Type() == "Free Parking") {
    } else if (block[loc]->Type() == "Go To Jail") {
        player[__player]->Move(20);
        player[__player]->Imprison();
    } else if (block[loc]->Type() == "Tax") {
        player[__player]->Earn(-block[loc]->Price2());
        if (player[__player]->Money() < 0) Map::SellOrNot(__player);
    } else if (block[loc]->Type() == "Property") {
        if (block[loc]->Owner() == -1) {
            Map::BuyOrNot(__player, loc);
            if (player[__player]->Money() < 0) Map::SellOrNot(__player);
        } else if (block[loc]->Owner() != __player) {
            player[__player]->Earn(-int(block[loc]->Price2() * player[__player]->RentRate()));
            if (player[__player]->Money() < 0) Map::SellOrNot(__player);
        }
    } else if (block[loc]->Type() == "Railroad") {
        if (block[loc]->Owner() == -1) {
            Map::BuyOrNot(__player, loc);
            if (player[__player]->Money() < 0) Map::SellOrNot(__player);
        } else if (block[loc]->Owner() != __player) {
            int cost = 25;
            for (int i = (loc + 10) % 40; i != loc; i = (i + 10) % 40)
                if (block[i]->Owner() == block[loc]->Owner()) cost <<= 1;
            player[__player]->Earn(-int(cost * player[__player]->RentRate()));
            if (player[__player]->Money() < 0) Map::SellOrNot(__player);
        }
    } else if (block[loc]->Type() == "Utility") {
        if (block[loc]->Owner() == -1) {
            Map::BuyOrNot(__player, loc);
            if (player[__player]->Money() < 0) Map::SellOrNot(__player);
        } else if (block[loc]->Owner() != __player) {
            int cost = __step;
            if (block[40 - loc]->Owner() == block[loc]->Owner()) cost *= 10;
            else
                cost *= 4;
            player[__player]->Earn(-int(cost * player[__player]->RentRate()));
            if (player[__player]->Money() < 0) Map::SellOrNot(__player);
        }
    } else if (block[loc]->Type() == "Community Chest") {
        //TODO
    } else if (block[loc]->Type() == "Chance") {
        //TODO
    }
}

void Map::Update() {
    for (int i = 0; i < 40; ++i)
        if (block[i]->Color() > 0 && block[i]->Owner() > 0) {
            bool flag = true;
            for (int j = 0; j < 40; ++j)
                if (block[i]->Color() == block[j]->Color() && block[i]->Owner() != block[j]->Owner()) flag = false;
            if(block[i]->United() != flag) block[i]->ChangeUnited();
        }
}

void Map::BuyOrNot(int __player, int __block) {
    //TODO
}

void Map::BankruptOrNot(int __player) {
    //TODO
}

void Map::SellOrNot(int __player) {
    //TODO
}

void Map::Trade(int __player1, int __player2) {
    //TODO
}

void Map::Bankrupt(int __player1, int __player2) {
    for (int i = 0; i < 40; ++i)
        if (block[i]->Owner() == __player1) {
            block[i]->Buy(__player2);
            if (__player2 == -1)
                for (block[i]->Redeem(); block[i]->House() > 0; block[i]->Sell())
                    ;
        }
    if (__player2 != -1) player[__player2]->Earn(player[__player1]->Money());
    player[__player1]->Bankrupt();
    Update();
}

void Map::Buy(int __player, int __block) {
    player[__player]->Earn(-int(block[__block]->Price0() * player[__player]->BuildRate()));
    player[__player]->Buy(__block);
    block[__block]->Buy(__player);
    Update();
}

void Map::Mortgage(int __player, int __block) {
    player[__player]->Earn(int(block[__block]->Price0() * player[__player]->BuildRate() * 0.5));
    block[__block]->Mortgage();
}

void Map::Redeem(int __player, int __block) {
    player[__player]->Earn(-int(block[__block]->Price0() * player[__player]->BuildRate() * 0.55));
    block[__block]->Redeem();
}

void Map::Sell(int __player, int __block) {
    player[__player]->Earn(int(block[__block]->Price1() * player[__player]->BuildRate() * 0.5));
    block[__block]->Sell();
}

void Map::Build(int __player, int __block) {
    player[__player]->Earn(-int(block[__block]->Price1() * player[__player]->BuildRate()));
    block[__block]->Build();
}
