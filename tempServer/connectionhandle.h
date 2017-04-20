#ifndef CONNECTIONHANDLE_H
#define CONNECTIONHANDLE_H

#include <QObject>
#include <QTcpServer>
#include <QTextStream>
#include <QTcpSocket>


class connectionHandle : public QObject         //Setting class name
{
    Q_OBJECT
public:
    explicit connectionHandle(QObject *parent = 0, int port = 1000);    //Default constructor
    explicit connectionHandle(int port);                                //Constructor allows manual pick of port number
    QTcpServer *server;         //Server object pointer
    QTcpSocket *socket;         //Socket object pointer

    QStringList handle();       //Function checks if there is a pending connection and retrieves data parsing into a QStringList
signals:

public slots:

private:


};

#endif // CONNECTIONHANDLE_H
