#include "headers/eventwatcher.h"
#include "headers/stylizedbutton.h"

#include "QGraphicsEffect"
#include "QApplication"

eventWatcher::eventWatcher(QObject * parent) :QObject(parent)
{}

bool eventWatcher::eventFilter(QObject * watched, QEvent * event)
{
    stylizedButton * button = qobject_cast<stylizedButton*>(watched);
    if (!button) {
        return false;
    }
    //release
    if (event->type() == QEvent::MouseButtonRelease){
        if(button->isCheckable()&&button->isChecked()&&button->checkedPix==nullptr)return false;
        if(button->pressedPix==nullptr)delete button->graphicsEffect();
        else{
            button->setIcon(*(button->origPix));
        }
    }

    //hover
    if(event->type()==QEvent::Enter){
        if(button->isCheckable()&&button->isChecked()&&button->checkedPix==nullptr)return false;
        //qDebug()<<"Hover In";
        if(button->hoverPix==nullptr){
            QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
            effect->setColor(QColor(150,150,150,100));
            effect->setBlurRadius(12);
            effect->setOffset(0,0);
            button->setGraphicsEffect(effect);
        }
        else{
            button->setIcon(*(button->hoverPix));
        }
    }

    if (event->type() == QEvent::Leave){
        if(button->isCheckable()&&button->isChecked()&&button->checkedPix==nullptr)return false;
        //qDebug()<<"Hover Leave";
        if(button->hoverPix==nullptr)delete button->graphicsEffect();
        else{
            button->setIcon(*(button->origPix));
        }
    }
    return false;
}
