#include "headers/playerview.h"
#include "QLabel"

playerView::playerView(){
	this->setFixedSize(320, 320);
	this->setObjectName("playerView");
	this->setStyleSheet("QFrame#playerView{background-color:#2C1F36;"
	                    "border-radius:5}"
	                    "QLabel{color:white}");
	m_layout = new QVBoxLayout;
	this->setLayout(m_layout);
	m_layout->setAlignment(Qt::AlignVCenter);
}

void playerView::setFocus(int _currentPlayer){
	layout()->itemAt(currentFocus)->widget()->setStyleSheet("");
	layout()->itemAt(_currentPlayer)->widget()->setStyleSheet("QFrame#top{background-color:rgba(255,255,255,30);border-radius:5}");
	currentFocus = _currentPlayer;
}

void playerView::setPrison(int _currentPlayer, bool s){
	if(s) {
		QLayoutItem *childFrame = layout()->itemAt(_currentPlayer);
		QLayoutItem *moneyLabel = childFrame->widget()->layout()->itemAt(1);
		moneyLabel->widget()->setProperty("text", m_player[_currentPlayer]->getName() + "  🔒");
	} else {
		QLayoutItem *childFrame = layout()->itemAt(_currentPlayer);
		QLayoutItem *moneyLabel = childFrame->widget()->layout()->itemAt(1);
		moneyLabel->widget()->setProperty("text", m_player[_currentPlayer]->getName());
	}
}

void playerView::setBankrupt(int _currentPlayer){
	QLayoutItem *childFrame = layout()->itemAt(_currentPlayer);
	QLayoutItem *moneyLabel = childFrame->widget()->layout()->itemAt(2);
	moneyLabel->widget()->setProperty("text", "❌");
}

void playerView::init(Player **_nPlayers, int _playerCnt){
	m_player = _nPlayers;
	qDeleteAll(this->findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));
	playerCnt = _playerCnt;
	for(int i = 0; i < playerCnt; ++i) {
		QFrame *childFrame = new QFrame;
		childFrame->setObjectName("top");
		m_layout->addWidget(childFrame);
		auto m_innerLayout = new QHBoxLayout;
		childFrame->setLayout(m_innerLayout);
		m_playerSymbol[i] = new playerSymbol(m_player[i]->symbol.getColor(), 0, 32, 32);
		m_innerLayout->addWidget(m_playerSymbol[i], 1, Qt::AlignBaseline);
		auto nameLabel = new QLabel(m_player[i]->getName());
		nameLabel->setFont(QFont("Noto Sans SC", 14, 700));
		m_innerLayout->addWidget(nameLabel, 1, Qt::AlignBaseline);
		auto money = new QLabel("￥" + QString::number(m_player[i]->Money()));
		money->setFont(QFont("Noto Sans SC", 14, 500));
		m_innerLayout->addWidget(money, 1, Qt::AlignBaseline | Qt::AlignRight);
	}
}

Player **playerView::m_player = nullptr;


void playerView::updateMoney(int i){
	QLayoutItem *childFrame = layout()->itemAt(i);
	QLayoutItem *moneyLabel = childFrame->widget()->layout()->itemAt(2);
	moneyLabel->widget()->setProperty("text", "￥" + QString::number(m_player[i]->Money()));
}
