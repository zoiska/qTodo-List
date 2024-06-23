#include "mainwindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    mainwindow w;
    w.showMaximized();
    return QApplication::exec();
}
