#include "headers/playersymbol.h"
#include "QPainter"
#include "QPixmap"
#include "QTransform"
#include "QGraphicsDropShadowEffect"

playerSymbol::playerSymbol(int _color, int _direction, int _width, int _height){
	color = _color;
	direction = _direction;
	setFixedSize(_width, _height);
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
	effect->setColor(QColor(0x130f1d));
	effect->setBlurRadius(_width / 2);
	effect->setOffset(0, 0);
	this->setGraphicsEffect(effect);
}

void playerSymbol::paintEvent(QPaintEvent *qPaintEvent){
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	QWidget::paintEvent(qPaintEvent);
	QBrush brush;
	QPen pen(color);
	pen.setWidth(0);
	painter.setPen(pen);
	brush.setColor(color);
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);
	painter.drawEllipse(2, 2, this->width() - 4, this->height() - 4);
	QTransform tr;
	tr.rotate(direction * 90);
	QPixmap pix(":/resources/image/icons/eyes.png");
	painter.drawPixmap(2, 2, this->width() - 4, this->height() - 4, pix.transformed(tr, Qt::SmoothTransformation));
}

void playerSymbol::setFixedSize(int w, int h){
	QWidget::setFixedSize(w, h);
	setMask(QRegion(0, 0, w, h, QRegion::Ellipse));
}

void playerSymbol::setColor(int _c){
	color = _c;
	this->update();
}

void playerSymbol::setDirection(int _d){
	direction = _d;
	this->update();
}

int playerSymbol::getDirection(){
	return direction;
}

int playerSymbol::getColor(){
	return color;
}
