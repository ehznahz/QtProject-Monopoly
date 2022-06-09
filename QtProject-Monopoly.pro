QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/eventwatcher.cpp \
    sources/gameinitial.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/playersymbol.cpp \
    sources/startmenu.cpp \
    sources/stylizedbutton.cpp

HEADERS += \
    headers/eventwatcher.h \
    headers/gameinitial.h \
    headers/mainwindow.h \
    headers/playersymbol.h \
    headers/startmenu.h \
    headers/stylizedbutton.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    fonts.qrc \
    images.qrc
