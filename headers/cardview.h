#ifndef QTPROJECT_MONOPOLY_CARDVIEW_H
#define QTPROJECT_MONOPOLY_CARDVIEW_H

#include <QtWidgets>
#include <QList>

class CardLayout : public QLayout{
public:
	CardLayout(int spacing, int _direction) : QLayout(){
		setSpacing(spacing);
		direction = _direction;
	}

	CardLayout(int spacing, QWidget *parent) : QLayout(parent){
		setSpacing(spacing);
	}

	~CardLayout();

	void addItem(QLayoutItem *item) override;
	QSize sizeHint() const override;
	QSize minimumSize() const override;
	int count() const override;
	QLayoutItem *itemAt(int) const override;
	QLayoutItem *takeAt(int) override;
	void setGeometry(const QRect &rect) override;

private:
	int direction;
	QList<QLayoutItem *> m_items;
};

#endif//QTPROJECT_MONOPOLY_CARDVIEW_H
