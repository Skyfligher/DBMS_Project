
#include <mainwindow.h>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;   //Creating the mainwindow
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint); //Sets mainwindow to frameless mode, asthetics


    return a.exec(); //exits main loop as the mainwindow is now setup
}
