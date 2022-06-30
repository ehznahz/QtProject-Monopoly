#ifndef QTPROJECT_MONOPOLY_PLAYERVIEW_H
#define QTPROJECT_MONOPOLY_PLAYERVIEW_H

#include "QWidget"
#include "QFrame"
#include "headers/player.h"
#include "headers/playersymbol.h"
#include "QVBoxLayout"

class playerView :public QFrame{
    Q_OBJECT
    static Player** m_player;
    playerSymbol* m_playerSymbol[6];
    QVBoxLayout* m_layout;
    int playerCnt;
    int currentFocus = 0;
public:
    playerView();
    void init(Player** _nPlayers,int playerCnt);
    void setFocus(int _currentPlayer);
    void setPrison(int _currentPlayer,bool s);
    void setBankrupt(int _currentPlayer);
    void updateMoney(int i);
};


#endif//QTPROJECT_MONOPOLY_PLAYERVIEW_H