#include "conn.h"
#include "login.h"
#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //w.show();

    //login log;
    //log.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    return a.exec();
}
