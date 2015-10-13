#include <QApplication>
#include <QTextCodec>

#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Set proper coding
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow win;

    return app.exec();
}
