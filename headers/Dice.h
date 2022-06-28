#ifndef QTPROJECT_MONOPOLY_DICE_H
#define QTPROJECT_MONOPOLY_DICE_H

#include "QWidget"
#include "QMovie"
#include "QLabel"
#include "QTimer"

class Dice: public QWidget{
    Q_OBJECT
public:
    Dice();
    int roll();
    int px=1;int py=1;
    void initPainter(QPainter *) const;
    void startAE(){
        m_nIndex=0;
        m_pTimer = new QTimer();
        connect(m_pTimer,SIGNAL(timeout()),this,SLOT(update()));
        m_pTimer->start(20);
    }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QTimer *m_pTimer = nullptr;
    QStringList m_strListImg;
    int m_nIndex = 0;
    void stopAE();
    QStringList dices={
            "",
            ":/resources/image/dice/dice1.png",
            ":/resources/image/dice/dice2.png",
            ":/resources/image/dice/dice3.png",
            ":/resources/image/dice/dice4.png",
            ":/resources/image/dice/dice5.png",
            ":/resources/image/dice/dice6.png"
    };
};


#endif//QTPROJECT_MONOPOLY_DICE_H
