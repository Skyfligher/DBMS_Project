#include "mainwindow.h"
#include <QApplication>
#include <QTcpSocket>
#include <QTextStream>
//#include <QDataStream>

QTextStream cout(stdout);
QTextStream cin(stdin);

QTcpSocket *socket;
//QDataStream *stream;

void createUser(QString Nickname, QString email, QString first, QString last, QString password);

int main(int argc, char *argv[])
{
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1",1000);               //code in progress

    //stream = new QDataStream(socket);

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}

void createUser(QString Nickname, QString email, QString first, QString last, QString password){

    QString temp = "createUser,"+Nickname+","+email+","+first+" "+last+","+password;
    QByteArray array = temp.toLocal8Bit();
    char* buffer = array.data();
    socket->write(buffer);
}
