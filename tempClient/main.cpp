#include "mainwindow.h"
#include "login.h"
#include "ui_login.h"
#include <QApplication>
#include <QTcpSocket>
#include <QTextStream>
#include <QMessageBox>

QTextStream cout(stdout);
QTextStream cin(stdin);

//QTcpSocket *socket;
//QDataStream *stream;


//void createUser(QString Nickname, QString email, QString first, QString last, QString password);

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();


    return a.exec();
}

/*void createUser(QString Nickname, QString email, QString first, QString last, QString password){

    QString temp = "createUser,"+Nickname+","+email+","+first+" "+last+","+password;
    QByteArray array = temp.toLocal8Bit();
    char* buffer = array.data();
    socket->write(buffer);
}
*/
