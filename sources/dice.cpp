#include <QPainter>
#include "headers/Dice.h"
#include "headers/stylizedbutton.h"
#include "QEventLoop"
Dice::Dice() {
    this->setFixedSize(200,100);
    stopAE();
    m_strListImg.clear();
    for (int i = 0; i <= 22; ++i) {
        m_strListImg.append(QString(":/resources/image/dice/dice.apng/dice.apng")+QString::number(i)+QString(".png"));
    }
}

int Dice::roll() {
    px=rand()%6+1;
    py=rand()%6+1;
    startAE();
    QEventLoop* qEventLoop=new QEventLoop;
    connect(m_pTimer,&QTimer::destroyed,this,[=](){
        qEventLoop->exit();
    });
    qEventLoop->exec();
    this->update();
    return px*10+py;
}

void Dice::initPainter(QPainter * painter)const{
    QWidget::initPainter(painter);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
}

void Dice::stopAE()
{
    if(m_pTimer== nullptr)return;

    delete m_pTimer;
    m_pTimer= nullptr;
}

void Dice::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(m_nIndex==m_strListImg.size()-1){
        painter.drawImage(QPointF(0, 0), QImage(dices[px]).scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter.drawImage(QPointF(101, 0), QImage(dices[py]).scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        stopAE();
    }
    else if(m_pTimer!= nullptr){
        painter.drawImage(QPointF(0,0),QImage(m_strListImg[m_nIndex]).scaled(100,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        painter.drawImage(QPointF(101,0),QImage(m_strListImg[m_nIndex]).scaled(100,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        m_nIndex++;
    }
    else{
        painter.drawImage(QPointF(0, 0), QImage(dices[1]).scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter.drawImage(QPointF(101, 0), QImage(dices[1]).scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}
