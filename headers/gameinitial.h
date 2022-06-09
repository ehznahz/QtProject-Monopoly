#ifndef GAMEINITIAL_H
#define GAMEINITIAL_H

#include "QWidget"
#include "QFrame"

class gameInitial : public QWidget
{
    Q_OBJECT

    QFrame* onlineView= nullptr;
    QFrame* offlineView= nullptr;

public:
    void switchView(int);
    explicit gameInitial(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*) override;


signals:

};

#endif // GAMEINITIAL_H
