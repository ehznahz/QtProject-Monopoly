#ifndef STYLIZEDBUTTON_H
#define STYLIZEDBUTTON_H

#include "QPushButton"
#include "QPixmap"

class stylizedButton : public QPushButton{
Q_OBJECT
public:
	//构造函数 文字生成
	stylizedButton(QString text, int _width, int _height);
	//构造函数 图片生成的按钮
	stylizedButton(int _width, int _height, QString origImg, QString pressedImg = "", QString hoverImg = "", QString checkedImg = "");
	QIcon *origPix = nullptr, *pressedPix = nullptr, *hoverPix = nullptr, *checkedPix = nullptr;
	void initPainter(QPainter *) const;
	void paintEvent(QPaintEvent *);
};

#endif // STYLIZEDBUTTON_H
