#include "headers/eventview.h"
#include "QLabel"
eventView::eventView() {
    this->setFixedSize(320,480);
    this->setObjectName("playerView");
    this->setStyleSheet("QFrame#playerView{background-color:#2C1F36;"
                        "border-radius:5}"
                        "QLabel{color:white}");
    m_layout = new QVBoxLayout;
    this->setLayout(m_layout);
    m_layout->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    auto title = new QLabel("事件");
    title->setFont(QFont("Noto Sans SC",18,700));
    m_layout->addWidget(title,0,Qt::AlignHCenter|Qt::AlignTop);
}
void eventView::clear() {
    qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    auto title = new QLabel("事件");
    vol=0;
    title->setFont(QFont("Noto Sans SC",18,700));
    m_layout->addWidget(title,0,Qt::AlignHCenter|Qt::AlignTop);
}
void eventView::addEvent(const QString& event, int flag) {
    if(vol>=1){
        m_layout->itemAt(1)->widget()->setFont(QFont("Noto Sans SC",10,500));
    }
    if(m_layout->sizeHint().height()>460){
        delete m_layout->takeAt(vol)->widget();
        vol--;
    }
    auto eventLabel = new QLabel(event);
    eventLabel->setWordWrap(true);
    eventLabel->setAlignment(Qt::AlignCenter);
    eventLabel->setFont(QFont("Noto Sans SC",11,700));
    if(flag==1)eventLabel->setStyleSheet("color:#efa0bb");
    else if(flag==2)eventLabel->setStyleSheet("color:#d69641");
    m_layout->insertWidget(1,eventLabel,0,Qt::AlignTop);
    vol++;
}
