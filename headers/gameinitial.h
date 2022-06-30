#ifndef GAMEINITIAL_H
#define GAMEINITIAL_H

#include "QWidget"
#include "QFrame"
#include "headers/player.h"

class gameInitial : public QWidget{
Q_OBJECT

	QFrame *onlineView = nullptr;
	QFrame *offlineView = nullptr;

public:
	void switchView(int);
	explicit gameInitial(QWidget *parent = nullptr);
	void paintEvent(QPaintEvent *) override;


signals:
	void gameStarted(QList<Player *> _player, int playerCount, int roundLimit, bool pointEnabled);
	void returnMainPage();
};

#endif // GAMEINITIAL_H
