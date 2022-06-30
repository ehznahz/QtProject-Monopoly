#ifndef EVENTWATCHER_H
#define EVENTWATCHER_H

#include <QObject>
#include <QPushButton>
#include <QEvent>

class eventWatcher : public QObject{
Q_OBJECT
public:
	eventWatcher(QObject *parent = Q_NULLPTR);
	virtual bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
};

#endif // EVENTWATCHER_H
