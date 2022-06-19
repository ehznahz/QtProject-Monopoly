#include "headers/mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont("fonts/NotoSansSC-Regular.otf");
    QFontDatabase::addApplicationFont("fonts/NotoSansSC-Bold.otf");
    QFont font("Noto Sans SC",16,500);
    font.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(font);
    MainWindow w;
    qDebug()<<w.devicePixelRatio();
    qDebug()<<w.devicePixelRatioFScale();
    w.show();
    return a.exec();
}
