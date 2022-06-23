#include "headers/map.h"
#include <cstdlib>

Map::Map() {
    //地图初始化
    //TODO 地图填写
    block[0] = Block("   GO!   \n         ", "Pass Go! \nGet $200 ", "START", -1, 0, 0, 0);
    block[1] = Block("         \n         ", "         \n   $60   ", "Property", 1, 60, 50, 2);
    block[2] = Block("Community\n  Chest  ", "         \n         ", "Community Chest", -1, 0, 0, 0);
    block[3] = Block("         \n         ", "         \n   $60   ", "Property", 1, 60, 50, 4);
    block[4] = Block("         \n         ", "         \nPay $200 ", "Tax", -1, 0, 0, 200);
    block[5] = Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0);
    block[6] = Block(" Chance  \n         ", "         \n  $100   ", "Property", 2, 100, 50, 6);
    block[7] = Block("         \n         ", "         \n         ", "Chance", -1, 0, 0, 0);
    block[8] = Block("         \n         ", "         \n  $100   ", "Property", 2, 60, 50, 6);
    block[9] = Block("         \n         ", "         \n  $120   ", "Property", 2, 60, 50, 8);
    block[10] = Block("         \n         ", "   Just  \nVisiting ", "Jail", -1, 0, 0, 0);
    block[11] = Block("         \n         ", "         \n  $140   ", "Property", 3, 140, 100, 10);
    block[12] = Block("         \n         ", "         \n  $150   ", "Utility", -1, 150, 0, 0);
    block[13] = Block("         \n         ", "         \n  $140   ", "Property", 3, 140, 100, 10);
    block[14] = Block("         \n         ", "         \n  $160   ", "Property", 3, 160, 100, 12);
    block[15] = Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0);
    block[16] = Block("         \n         ", "         \n  $180   ", "Property", 4, 180, 100, 14);
    block[17] = Block("Community\n  Chest  ", "         \n         ", "Community Chest", -1, 0, 0, 0);
    block[18] = Block("         \n         ", "         \n  $180   ", "Property", 4, 180, 100, 14);
    block[19] = Block("         \n         ", "         \n  $200   ", "Property", 4, 200, 100, 16);
    block[20] = Block("         \n         ", "   Just  \nVisiting ", "Free Parking", -1, 0, 0, 0);
    block[21] = Block("         \n         ", "         \n  $220   ", "Property", 5, 220, 150, 18);
    block[22] = Block(" Chance  \n         ", "         \n         ", "Chance", -1, 0, 0, 0);
    block[23] = Block("         \n         ", "         \n  $220   ", "Property", 5, 220, 150, 18);
    block[24] = Block("         \n         ", "         \n  $240   ", "Property", 5, 240, 150, 20);
    block[25] = Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0);
    block[26] = Block("         \n         ", "         \n  $260   ", "Property", 6, 260, 150, 22);
    block[27] = Block("         \n         ", "         \n  $260   ", "Property", 6, 260, 150, 22);
    block[28] = Block("         \n         ", "         \n         ", "Utility", -1, 0, 0, 0);
    block[29] = Block("         \n         ", "         \n  $280   ", "Property", 6, 280, 150, 22);
    block[20] = Block("         \n         ", "         \n         ", "Go To Jail", -1, 0, 0, 0);
    block[31] = Block("         \n         ", "         \n  $300   ", "Property", 7, 300, 200, 26);
    block[32] = Block("         \n         ", "         \n  $300   ", "Property", 7, 300, 200, 26);
    block[33] = Block("Community\n  Chest  ", "         \n         ", "Community Chest", -1, 0, 0, 0);
    block[34] = Block("         \n         ", "         \n  $320   ", "Property", 7, 320, 200, 28);
    block[35] = Block("         \n         ", "         \n  $200   ", "Railroad", -1, 200, 0, 0);
    block[36] = Block(" Chance  \n         ", "         \n         ", "Chance", -1, 0, 0, 0);
    block[37] = Block("         \n         ", "         \n  $350   ", "Property", 8, 350, 200, 35);
    block[38] = Block("         \n         ", "         \nPay $100 ", "Tax", -1, 0, 0, 100);
    block[39] = Block("         \n         ", "         \n  $400   ", "Property", 8, 400, 200, 50);
}

void Map::Move(int __player, int __step) {
    player[__player].Move(__step);
    int loc = player[__player].Location();
    if(loc < __step) player[__player].Earn(200);
    //判断行动
    if(block[loc].Type() == "START") {
        player[__player].Earn(200);
    }
    else if(block[loc].Type() == "Jail") {
    }
    else if(block[loc].Type() == "Free Parking") {
    }
    else if(block[loc].Type() == "Go To Jail") {
        player[__player].Move(20);
        player[__player].Imprison();
    }
    else if(block[loc].Type() == "Tax") {
        player[__player].Earn(-block[loc].Price2());
        if(player[__player].Money() < 0) Map::SellOrNot(__player);
    }
    else if(block[loc].Type() == "Property") {
        if(block[loc].Owner() == -1) {
            Map::BuyOrNot(__player, loc);
            if(player[__player].Money() < 0) Map::SellOrNot(__player);
        }
        else if(block[loc].Owner() != __player) {
            player[__player].Earn(-int(block[loc].Price2() * player[__player].RentRate()));
            if(player[__player].Money() < 0) Map::SellOrNot(__player);
        }
    }
    else if(block[loc].Type() == "Railroad") {
        if(block[loc].Owner() == -1) {
            Map::BuyOrNot(__player, loc);
            if(player[__player].Money() < 0) Map::SellOrNot(__player);
        }
        else if(block[loc].Owner() != __player) {
            int cost = 25;
            for(int i = (loc + 10) % 40; i != loc; i = (i + 10) % 40) if(block[i].Owner() == block[loc].Owner()) cost <<= 1;
            player[__player].Earn(-int(cost * player[__player].RentRate()));
            if(player[__player].Money() < 0) Map::SellOrNot(__player);
        }
    }
    else if(block[loc].Type() == "Utility") {
        if(block[loc].Owner() == -1) {
            Map::BuyOrNot(__player, loc);
            if(player[__player].Money() < 0) Map::SellOrNot(__player);
        }
        else if(block[loc].Owner() != __player) {
            int cost = __step;
            if(block[40 - loc].Owner() == block[loc].Owner()) cost *= 10;
            else cost *= 4;
            player[__player].Earn(-int(cost * player[__player].RentRate()));
            if(player[__player].Money() < 0) Map::SellOrNot(__player);
        }
    }
    else if(block[loc].Type() == "Community Chest") {
        //TODO
    }
    else if(block[loc].Type() == "Chance") {
        //TODO
    }
}

void Map::Roll(int __player) {
    int px = rand() % 6 + 1, py = rand() % 6 + 1;
    Move(__player, px + py);
}

void Map::Update() {
    for(int i = 0; i < 40; ++i) if(block[i].Color() > 0 && block[i].Owner() > 0) {
        bool flag = true;
        for(int j = 0; j < 40; ++j) if(block[i].Color() == block[j].Color() && block[i].Owner() != block[j].Owner()) flag = false;
        block[i].ChangeUnited(flag);
    }
}

void Map::BuyOrNot(int __player, int __block) {
    //TODO
}

void Map::SellOrNot(int __player) {
    //TODO
}

void Map::Trade(int __player1, int __player2) {
    //TODO
}

void Map::Bankrupt(int __player1, int __player2) {
    for(int i = 0; i < 40; ++i) if(block[i].Owner() == __player1) {
        block[i].Buy(__player2);
        if(__player2 == -1) for(block[i].Redeem(); block[i].House() > 0; block[i].Sell());
    }
    if(__player2 != -1) player[__player2].Earn(player[__player1].Money());
    player[__player1].Bankrupt();
    Update();
}

void Map::Buy(int __player, int __block) {
    player[__player].Earn(-int(block[__block].Price0() * player[__player].BuildRate()));
    player[__player].Buy(__block);
    block[__block].Buy(__player);
    Update();
}

void Map::Mortgage(int __player, int __block) {
    player[__player].Earn(int(block[__block].Price0() * player[__player].BuildRate() * 0.5));
    block[__block].Mortgage();
}

void Map::Redeem(int __player, int __block) {
    player[__player].Earn(-int(block[__block].Price0() * player[__player].BuildRate() * 0.55));
    block[__block].Redeem();
}

void Map::Sell(int __player, int __block) {
    player[__player].Earn(int(block[__block].Price1() * player[__player].BuildRate() * 0.5));
    block[__block].Sell();
}

void Map::Build(int __player, int __block) {
    player[__player].Earn(-int(block[__block].Price1() * player[__player].BuildRate()));
    block[__block].Build();
}

void Map::Game() {
    //TODO 游戏主体
    for(; ; ) {

    }
}
