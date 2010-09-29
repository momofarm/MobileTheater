#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));


    QFont font("mingliu");

    a.setFont(font);

    MainWindow w;
QTextCodec::setCodecForTr( QTextCodec::codecForName( "System" ));
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
