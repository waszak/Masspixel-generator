#include "stdafx.h"
#include "mainwindow.h"
#include <QtGui/QApplication>

extern int ConsoleMode(int argc, char* argv[]); // console_renderer.cpp

int main(int argc, char *argv[])
{
    if (argc > 1) {
        return ConsoleMode(argc, argv);
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
