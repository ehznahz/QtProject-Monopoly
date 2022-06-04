#ifndef STYLIZEDBUTTON_H
#define STYLIZEDBUTTON_H

#include "QPushButton"
class stylizedButton:public QPushButton
{
    Q_OBJECT
public:
    //构造函数 文字生成
    stylizedButton(QString text,int _width,int _height);
    //构造函数 图片生成的按钮
    stylizedButton(QString origImg, QString pressedImg);
    QString origPath;
    QString pressedPath;
};

#endif // STYLIZEDBUTTON_H
