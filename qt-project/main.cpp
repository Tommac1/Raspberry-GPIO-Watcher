#include "mainwindow.h"

#include <QApplication>
#include <QtCore>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);

    return a.exec();
}

