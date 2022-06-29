#include "headers/cardview.h"

int CardLayout::count() const {
    // QList::size() returns the number of QLayoutItems in m_items
    return m_items.size();
}

QLayoutItem *CardLayout::itemAt(int idx) const {
    // QList::value() performs index checking, and returns nullptr if we are
    // outside the valid range
    return m_items.value(idx);
}

QLayoutItem *CardLayout::takeAt(int idx) {
    // QList::take does not do index checking
    return idx >= 0 && idx < m_items.size() ? m_items.takeAt(idx) : 0;
}

void CardLayout::addItem(QLayoutItem *item) {
    m_items.append(item);
}

CardLayout::~CardLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void CardLayout::setGeometry(const QRect &r) {
    QLayout::setGeometry(r);

    if (m_items.size() == 0)
        return;

    int w = m_items.at(0)->widget()->width() + (m_items.count() - 1) * spacing();
    int h = r.height() - (m_items.count() - 1) * spacing();
    int i = 0;
    while (i < m_items.size()) {
        QLayoutItem *o = m_items.at(i);
        if (direction == 0) {
            QRect geom(r.x() + r.width() / 2 - o->widget()->width() / 2, r.y() + i * spacing(), o->widget()->width(), h);
            o->setGeometry(geom);
        } else {
            qDebug() << o->widget()->height();
            QRect geom(r.x() + r.width() / 2 - w / 2 + i * spacing(), r.y() + r.height() / 2 - o->widget()->height() / 2, o->widget()->width(), o->widget()->height());
            o->setGeometry(geom);
        }
        ++i;
    }
}

QSize CardLayout::sizeHint() const {
    QSize s(0, 0);
    int n = m_items.count();
    //if (n > 0)
    // s = QSize(35, 35);//start with a nice default size
    int i = 0;
    while (i < n) {
        QLayoutItem *o = m_items.at(i);
        s = s.expandedTo(o->sizeHint());
        ++i;
    }
    return s + n * QSize(spacing(), spacing());
}

QSize CardLayout::minimumSize() const {
    QSize s(0, 0);
    int n = m_items.count();
    int i = 0;
    while (i < n) {
        QLayoutItem *o = m_items.at(i);
        s = s.expandedTo(o->minimumSize());
        ++i;
    }
    return s + n * QSize(spacing(), spacing());
}