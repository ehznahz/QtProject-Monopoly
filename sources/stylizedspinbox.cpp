#include "headers/stylizedspinbox.h"
#include "QLineEdit"


stylizedspinbox::stylizedspinbox(): QSpinBox() {
    setStyleSheet("QSpinBox{background-color:rgba(255,255,255,40);color:white;border:none;border-radius:5;}"
                  "QSpinBox::up-button{border-image:url(:/resources/image/icons/arrow-up.png);}"
                  "QSpinBox::down-button{border-image:url(:/resources/image/icons/arrow-down.png);}");
    lineEdit()->setReadOnly(true);
    setAlignment(Qt::AlignCenter);
    connect(lineEdit(), &QLineEdit::selectionChanged, lineEdit(), [=]() {
        lineEdit()->setSelection(0,0);
    });
}
