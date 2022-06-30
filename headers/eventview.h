#ifndef QTPROJECT_MONOPOLY_EVENTVIEW_H
#define QTPROJECT_MONOPOLY_EVENTVIEW_H

#include "QWidget"
#include "QFrame"
#include "QVBoxLayout"
class eventView:public QFrame{
    Q_OBJECT
    QVBoxLayout* m_layout;
    int vol=0;
public:
    eventView();
    void clear();
    void addEvent(const QString& event,int flag);
};


#endif//QTPROJECT_MONOPOLY_EVENTVIEW_H
