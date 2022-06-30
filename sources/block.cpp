#include "headers/block.h"
#include "QPainter"

Block::Block(QString __name, QString _action, QString _type, int _color, int _price0, int _price1, int _price2, int _sizeType, int _direction){
	name = __name;
	action = _action;
	type = _type;
	color = _color;
	price[0] = _price0;
	price[1] = _price1;
	price[2] = _price2;
	owner = -1;
	mortgaged = false;
	united = false;
	house = 0;
	sizeType = _sizeType;
	if(sizeType) {
		if(_direction % 2) {
			this->setFixedSize(106, 72);
		} else {this->setFixedSize(72, 106);}
	} else {this->setFixedSize(106, 106);}
	direction = _direction;
}

void Block::Buy(int __player){
	owner = __player;
}

void Block::Mortgage(){
	mortgaged = true;
}

void Block::Redeem(){
	mortgaged = false;
}

void Block::Build(){
	++house;
}

void Block::Sell(){
	--house;
}

void Block::ChangeUnited(){
	united ^= 1;
}

QString Block::Name() const{
	return name;
}

QString Block::Action() const{
	return action;
}

QString Block::Type() const{
	return type;
}

int Block::Color() const{
	if(color == -1) return RGBColor[0];
	return RGBColor[color];
}

int Block::Price0() const{
	return price[0];
}

int Block::Price1() const{
	return price[1];
}

int Block::Price2() const{
	return price[2];
}

int Block::Rent() const{
	if(house == 0) return price[2] * (united ? 2 : 1);
	if(house == 1) return price[2] * 4;
	if(house == 2) return price[2] * 12;
	if(house == 3) return price[2] * 28;
	if(house == 4) return price[2] * 34;
	return price[2] * 40;
}

int Block::Owner() const{
	return owner;
}

bool Block::Mortgaged() const{
	return mortgaged;
}

bool Block::United() const{
	return united;
}

int Block::House() const{
	return house;
}

void Block::paintEvent(QPaintEvent *){
	//sizeType 0->四角 106*106 1->四边 106*72
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.setBrush(QBrush(QColor(RGBColor[0]), Qt::SolidPattern));
	painter.drawRoundedRect(0, 0, QWidget::width(), QWidget::height(), 5, 5);
	if(type == "Railroad" || type == "Property" || type == "Utility") {
		painter.setBrush(QBrush(QColor(Color()), Qt::SolidPattern));
		painter.save();
		QFont f("Noto Sans SC", 10, 700);
		painter.setFont(f);
		if(direction == 0) {
			if(type == "Property")painter.drawRoundedRect(0, QWidget::height() - 30, QWidget::width(), 30, 5, 5);
			if(Owner() < 0) {
				painter.setBrush(QBrush(QColor(0x372A40), Qt::SolidPattern));
			} else {
				painter.setBrush(QBrush(QColor(players[Owner()]->symbol.getColor()), Qt::SolidPattern));
			}
			painter.drawRoundedRect(0, 0, QWidget::width(), 30, 5, 5);
			painter.setPen(QColor(255, 255, 255, 255));
			painter.drawText(3, 30, QWidget::width() - 6, QWidget::height() - 60, Qt::AlignCenter | Qt::TextWordWrap, name);
			if(Owner() < 0) {painter.drawText(3, 0, QWidget::width() - 6, 30, Qt::AlignCenter | Qt::TextWordWrap, action);}
			else if(Owner() >= 0 && House() >= 1) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(3, 0, QWidget::width() - 6, 30, Qt::AlignCenter | Qt::TextWordWrap, QString::number(House()));
			} else if(Mortgaged()) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(3, 0, QWidget::width() - 6, 30, Qt::AlignCenter | Qt::TextWordWrap, "抵押中");
			}
			if(type == "Railroad")painter.drawPixmap(21, 72, QPixmap(":/resources/image/map/metro.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		}
		if(direction == 1) {
			if(type == "Property")painter.drawRoundedRect(0, 0, 30, QWidget::height(), 5, 5);
			if(Owner() < 0) {
				painter.setBrush(QBrush(QColor(0x372A40), Qt::SolidPattern));
			} else {
				painter.setBrush(QBrush(QColor(players[Owner()]->symbol.getColor()), Qt::SolidPattern));
			}
			painter.drawRoundedRect(QWidget::width() - 30, 0, 30, QWidget::height(), 5, 5);
			painter.setPen(QColor(255, 255, 255, 255));
			painter.translate(0, QWidget::height());
			painter.rotate(-90);
			if(type == "Railroad")painter.drawPixmap(21, 5, QPixmap(":/resources/image/map/metro.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
			painter.drawText(5, 30, QWidget::height() - 10, QWidget::width() - 60, Qt::AlignCenter | Qt::TextWordWrap, name);
			if(Owner() < 0) {painter.drawText(5, QWidget::width() - 30, QWidget::height() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, action);}
			else if(Owner() >= 0 && House() >= 1) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(5, QWidget::width() - 30, QWidget::height() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, QString::number(House()));
			} else if(Mortgaged()) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(5, QWidget::width() - 30, QWidget::height() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, "抵押中");
			}
		}
		if(direction == 2) {
			if(type == "Property")painter.drawRoundedRect(0, 0, QWidget::width(), 30, 5, 5);
			if(Owner() < 0) {
				painter.setBrush(QBrush(QColor(0x372A40), Qt::SolidPattern));
			} else {
				painter.setBrush(QBrush(QColor(players[Owner()]->symbol.getColor()), Qt::SolidPattern));
			}
			painter.drawRoundedRect(0, QWidget::height() - 30, QWidget::width(), 30, 5, 5);
			painter.setPen(QColor(255, 255, 255, 255));
			painter.drawText(3, 30, QWidget::width() - 6, QWidget::height() - 60, Qt::AlignCenter | Qt::TextWordWrap, name);
			if(Owner() < 0) {painter.drawText(5, QWidget::height() - 30, QWidget::width() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, action);}
			else if(Owner() >= 0 && House() >= 1) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(5, QWidget::height() - 30, QWidget::width() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, QString::number(House()));
			} else if(Mortgaged()) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(5, QWidget::height() - 30, QWidget::width() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, "抵押中");
			}
			if(type == "Railroad")painter.drawPixmap(21, 7, QPixmap(":/resources/image/map/metro.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		}
		if(direction == 3) {
			if(type == "Property")painter.drawRoundedRect(QWidget::width() - 30, 0, 30, QWidget::height(), 5, 5);
			if(Owner() < 0) {
				painter.setBrush(QBrush(QColor(0x372A40), Qt::SolidPattern));
			} else {
				painter.setBrush(QBrush(QColor(players[Owner()]->symbol.getColor()), Qt::SolidPattern));
			}
			painter.drawRoundedRect(0, 0, 30, QWidget::height(), 5, 5);
			painter.setPen(QColor(255, 255, 255, 255));
			painter.translate(QWidget::width(), 0);
			painter.rotate(90);
			if(type == "Railroad")painter.drawPixmap(21, 5, QPixmap(":/resources/image/map/metro.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
			painter.drawText(5, 30, QWidget::height() - 10, QWidget::width() - 60, Qt::AlignCenter | Qt::TextWordWrap, name);
			if(Owner() < 0) {painter.drawText(5, QWidget::width() - 30, QWidget::height() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, action);}
			else if(Owner() >= 0 && House() >= 1) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(5, QWidget::width() - 30, QWidget::height() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, QString::number(House()));
			} else if(Mortgaged()) {
				painter.setPen(QColor(0, 0, 0, 255));
				painter.drawText(5, QWidget::width() - 30, QWidget::height() - 10, 30, Qt::AlignCenter | Qt::TextWordWrap, "抵押中");
			}
		}
		painter.restore();
	}
	if(type == "Community Chest") {
		painter.setFont(QFont("Noto Sans SC", 12, 700));
		if(direction == 1) {
			painter.translate(0, QWidget::height());
			painter.rotate(-90);
		}
		if(direction == 3) {
			painter.translate(QWidget::width(), 0);
			painter.rotate(90);
		}
		painter.drawPixmap(10, 50, QPixmap(":/resources/image/map/chest.png").scaled(72 - 20, 106 - 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		painter.setPen(QColor(0xd69641));
		painter.drawText(10, 10, 72 - 20, 30, Qt::AlignCenter | Qt::TextWordWrap, "宝箱");
	} else if(type == "Chance") {
		painter.setFont(QFont("Noto Sans SC", 12, 700));
		if(direction == 1) {
			painter.translate(0, QWidget::height());
			painter.rotate(-90);
		}
		if(direction == 3) {
			painter.translate(QWidget::width(), 0);
			painter.rotate(90);
		}
		painter.drawPixmap(20, 50, QPixmap(":/resources/image/map/chance.png").scaled(72 - 40, 106 - 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		painter.setPen(QColor(0xefa0bb));
		painter.drawText(10, 10, 72 - 20, 30, Qt::AlignCenter | Qt::TextWordWrap, "机遇");
	}
	if(name == "新太阳学生中心") {
		painter.drawPixmap(7, 23, QPixmap(":/resources/image/map/sun.png").scaled(26, 26, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if(name == "近邻宝") {
		painter.drawPixmap(21, 7, QPixmap(":/resources/image/map/package.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if(name == "动力中心") {
		painter.setFont(QFont("Noto Sans SC", 11, 700));
		painter.setPen(QColor(255, 255, 255, 255));
		painter.drawText(3, 40, QWidget::width() - 6, QWidget::height() - 60, Qt::AlignCenter | Qt::TextWordWrap, name);
		painter.setFont(QFont("Noto Sans SC", 10, 700));
		painter.setPen(QColor(255, 255, 255, 235));
		painter.drawText(3, 64, QWidget::width() - 6, QWidget::height() - 70, Qt::AlignCenter | Qt::TextWordWrap, "￥200");
		painter.drawPixmap(16, 10, QPixmap(":/resources/image/map/power.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if(name == "餐饮中心") {
		painter.translate(QWidget::width(), 0);
		painter.rotate(90);
		painter.setFont(QFont("Noto Sans SC", 11, 700));
		painter.setPen(QColor(255, 255, 255, 255));
		painter.drawText(3, 40, QWidget::height() - 6, QWidget::width() - 60, Qt::AlignCenter | Qt::TextWordWrap, name);
		painter.setFont(QFont("Noto Sans SC", 10, 700));
		painter.setPen(QColor(255, 255, 255, 235));
		painter.drawText(3, 64, QWidget::height() - 6, QWidget::width() - 70, Qt::AlignCenter | Qt::TextWordWrap, "￥100");
		painter.drawPixmap(16, 10, QPixmap(":/resources/image/map/food.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if(type == "Go To Jail") {
		painter.drawPixmap(31, 20, 45, 45, QPixmap(":/resources/image/map/jail.png"));
		painter.setPen(QColor(255, 255, 255, 255));
		painter.setFont(QFont("Noto Sans SC", 12, 700));
		painter.drawText(3, 70, QWidget::width() - 6, 20, Qt::AlignCenter | Qt::TextWordWrap, "去小黑屋");
	}
	if(type == "START") {
		painter.drawPixmap(20, 25, 66, 31, QPixmap(":/resources/image/map/start1.png"));
		painter.drawPixmap(38, 62, 30, 24, QPixmap(":/resources/image/map/start2.png"));
	}
	if(type == "Free Parking") {
		painter.drawPixmap(20, 20, 66, 66, QPixmap(":/resources/image/map/park.png"));
	}
	if(type == "Jail") {
		painter.drawPixmap(30, 10, 46, 46, QPixmap(":/resources/image/map/denied.png"));
		painter.setPen(QColor(255, 255, 255, 255));
		painter.setFont(QFont("Noto Sans SC", 10, 700));
		painter.drawText(3, 56, QWidget::width() - 6, 35, Qt::AlignCenter | Qt::TextWordWrap, "禁言中\n或只是路过");
	}
}

const QString &Block::getName() const{
	return name;
}

Player **Block::players = nullptr;