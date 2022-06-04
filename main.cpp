#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/resources/fonts/NotoSansSC-Regular.otf");
    QFontDatabase::addApplicationFont(":/resources/fonts/NotoSansSC-Bold.otf");
    QFont font("Noto Sans SC",20);
    font.setHintingPreference(QFont::HintingPreference::PreferNoHinting);
    QApplication::setFont(font);
    MainWindow w;
    w.show();
    return a.exec();
}
