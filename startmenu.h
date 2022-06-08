#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

class startMenu : public QWidget
{
    Q_OBJECT
public:
    explicit startMenu(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:
    void beginClicked(bool checked);

};

#endif // STARTMENU_H
